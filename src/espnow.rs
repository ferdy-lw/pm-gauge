use std::{
    ffi::CStr,
    net::Ipv4Addr,
    ptr,
    sync::{
        LazyLock, Mutex, RwLock,
        mpsc::{self, Receiver, SyncSender, TryRecvError},
    },
    thread,
    time::Duration,
};

use esp_idf_svc::{
    espnow::{self, BROADCAST, EspNow, ReceiveInfo},
    sys::{
        EspError, MALLOC_CAP_INTERNAL, MALLOC_CAP_SPIRAM, TaskStatus_t, heap_caps_print_heap_info,
        uxTaskGetNumberOfTasks, uxTaskGetSystemState, wifi_interface_t_WIFI_IF_AP,
    },
};
use log::{error, info};

use crate::MacAddr;
use crate::ui::Info;

const ESPNOW_CHANNEL: u8 = 1;
type ChannelData = (MacAddr, heapless::Vec<u8, 250>);

/// Details about the elm device.
pub struct PeerInfo {
    pub mac: MacAddr,
    pub ip: Ipv4Addr,
    pub url_post: String,
}

pub static PEER: LazyLock<RwLock<Option<PeerInfo>>> = LazyLock::new(|| RwLock::new(None));

#[derive(Clone, Copy)]
#[repr(u8)]
enum Command {
    PeerAddr = 1,
    Connect = 2,
    Disconnect = 3,
}

impl PartialEq<u8> for Command {
    fn eq(&self, other: &u8) -> bool {
        *self as u8 == *other
    }
}

// trait IsCommand {
//     fn is_command(&self, command: Command) -> bool;
// }

// impl<T: AsRef<u8>> IsCommand for T {
//     fn is_command(&self, command: Command) -> bool {
//         self == command as u8
//     }
// }

static OBDNOW: Mutex<Option<ObdNow>> = Mutex::new(None);

pub struct ObdNow {
    espnow: EspNow<'static>,
}

impl ObdNow {
    pub fn start(espnow: EspNow<'static>, rx_disc: Receiver<MacAddr>) -> Result<(), EspError> {
        let (tx_now, rx_now) = mpsc::sync_channel::<ChannelData>(2);

        espnow.register_recv_cb(move |info, data| ObdNow::recv_cb(&tx_now, info, data))?;

        info!("ESPNOW starting");
        let _ = thread::Builder::new()
            .name("esp_now".to_string())
            .stack_size(4096)
            .spawn(move || ObdNow::elm327_client_address(rx_now, rx_disc));

        let obdnow = Self { espnow };

        OBDNOW.lock().unwrap().replace(obdnow);

        Ok(())
    }

    pub fn _create_channel() -> (SyncSender<ChannelData>, Receiver<ChannelData>) {
        mpsc::sync_channel::<ChannelData>(2)
    }

    fn recv_cb(tx_now: &SyncSender<ChannelData>, info: &ReceiveInfo, data: &[u8]) {
        info!("EspNow recv cb: info ({info:?}), data ({data:?})");
        let peer = *info.src_addr;

        tx_now
            .send((peer, heapless::Vec::from_slice(data).unwrap()))
            .unwrap();
    }

    fn elm327_client_address(rx_now: Receiver<ChannelData>, rx_disc: Receiver<MacAddr>) {
        info!("Starting client address thread");
        Info::set_info(&Info::NoPeer);

        loop {
            // First check to see if we got an espnow msg from the elm device that tells
            // us it's IP addr, and that it's ready to receive http requests
            match rx_now.try_recv() {
                Ok((peer_mac, data)) => {
                    if let Some(peer_ip) = data.first().and_then(|b| {
                        if Command::PeerAddr == *b && data.len() == 5 {
                            Some(Ipv4Addr::new(data[1], data[2], data[3], data[4]))
                        } else {
                            None
                        }
                    }) {
                        let peer_lock = PEER.write();
                        match peer_lock {
                            Ok(mut peer) => {
                                match &*peer {
                                    None => {
                                        *peer = Some(PeerInfo {
                                            mac: peer_mac,
                                            ip: peer_ip,
                                            url_post: format!("http://{peer_ip}/post"),
                                        });
                                        Info::set_info(&Info::None);
                                        info!("Adding peer {peer_ip}");
                                    }
                                    Some(p) => {
                                        error!(
                                            "Peer already active with mac ({:?}), ip ({}), ignoring new mac ({:?}), new ip ({})",
                                            p.mac, p.ip, peer_mac, peer_ip
                                        );
                                    }
                                };
                            }
                            Err(e) => {
                                error!("Peer lock error {e}");
                            }
                        }
                    } else {
                        error!("Got ESPNOW msg that is not bcast IP: {data:?}");
                    }
                }
                Err(TryRecvError::Empty) => {
                    // Check to see if any AP clients have disconnected, if it's the elm device then
                    // drop the details about it's IP addr so we wont keep sending HTTP requests.
                    // If it reconnects to the AP it should send another espnow msg.
                    match rx_disc.try_recv() {
                        Ok(mac) => {
                            let peer_lock = PEER.write();
                            match peer_lock {
                                Ok(mut peer) => {
                                    match &*peer {
                                        None => {
                                            info!(
                                                "Peer not active, ignoring mac {mac:?} disconnect"
                                            );
                                        }
                                        Some(p) => {
                                            if p.mac == mac {
                                                info!("Dropping peer {}", p.ip);
                                                *peer = None;
                                                Info::set_info(&Info::NoPeer);
                                            } else {
                                                info!(
                                                    "Peer already active with mac ({:?}), ip ({}), ignoring mac ({mac:?}) disconnect",
                                                    p.mac, p.ip
                                                );
                                            }
                                        }
                                    };
                                }
                                Err(e) => {
                                    error!("Peer lock error {e}");
                                }
                            }
                        }
                        Err(TryRecvError::Empty) => {}
                        Err(TryRecvError::Disconnected) => {
                            error!("Wifi sending channel disconnected. Stopping thread");
                            break;
                        }
                    }
                }
                Err(TryRecvError::Disconnected) => {
                    error!("ESPNOW sending channel disconnected. Stopping thread");
                    break;
                }
            }

            thread::sleep(Duration::from_millis(20));
        }
    }

    pub fn send_connect(connect: bool) {
        show_system();

        if let Some(obdnow) = OBDNOW.lock().unwrap().as_ref() {
            let _ = obdnow.espnow.add_peer(espnow::PeerInfo {
                peer_addr: BROADCAST,
                channel: ESPNOW_CHANNEL,
                ifidx: wifi_interface_t_WIFI_IF_AP,
                encrypt: false,
                ..Default::default()
            });

            let data = if connect {
                [Command::Connect as u8]
            } else {
                [Command::Disconnect as u8]
            };

            match obdnow.espnow.send(BROADCAST, &data) {
                Ok(_) => info!("Sent connect: {connect}"),
                Err(e) => error!("Failed to send connect ({connect}), {e:?}"),
            }
        } else {
            error!("ObdNow not setup");
        }
    }
}

pub fn show_system() {
    unsafe { heap_caps_print_heap_info(MALLOC_CAP_INTERNAL) };
    info!("Internal -^");
    unsafe { heap_caps_print_heap_info(MALLOC_CAP_SPIRAM) };
    info!("SPIRAM -^");

    let mut ul_total_run_time: u32 = 4000;

    // Take a snapshot of the number of tasks in case it changes while this
    // function is executing.
    let mut ux_array_size = unsafe { uxTaskGetNumberOfTasks() };

    // Allocate a TaskStatus_t structure for each task.  An array could be
    // allocated statically at compile time.
    // pxTaskStatusArray = pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) );
    let mut px_task_status_array: Vec<TaskStatus_t> = Vec::with_capacity(ux_array_size as usize);
    unsafe { px_task_status_array.set_len(ux_array_size as usize) };

    // Generate raw status information about each task.
    ux_array_size = unsafe {
        uxTaskGetSystemState(
            px_task_status_array.as_mut_ptr(),
            ux_array_size,
            ptr::null_mut(),
            // &ul_total_run_time as *const _ as *mut _,
        )
    };

    // For percentage calculations.
    ul_total_run_time /= 100;

    // Avoid divide by zero errors.
    if ul_total_run_time > 0 {
        // For each populated position in the pxTaskStatusArray array,
        // format the raw data as human readable ASCII data
        for x in 0..ux_array_size as usize {
            // What percentage of the total run time has the task used?
            // This will always be rounded down to the nearest integer.
            // ulTotalRunTimeDiv100 has already been divided by 100.
            let ul_stats_as_percentage =
                px_task_status_array[x].ulRunTimeCounter / ul_total_run_time;

            if ul_stats_as_percentage > 0 {
                // sprintf( pcWriteBuffer, \"%s\\t\\t%lu\\t\\t%lu%%\\r\\n\", pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].ulRunTimeCounter, ulStatsAsPercentage );
                info!(
                    "{}\t\t{}\t\t{}%\t\t{}",
                    unsafe { CStr::from_ptr(px_task_status_array[x].pcTaskName) }
                        .to_str()
                        .unwrap()
                        .to_owned(),
                    px_task_status_array[x].ulRunTimeCounter,
                    px_task_status_array[x].usStackHighWaterMark,
                    ul_stats_as_percentage
                );
            } else {
                // If the percentage is zero here then the task has
                // consumed less than 1% of the total run time.
                // sprintf( pcWriteBuffer, \"%s\\t\\t%lu\\t\\t<1%%\\r\\n\", px_task_status_array_ub[ x ].pcTaskName, px_task_status_array_ub[ x ].ulRunTimeCounter );
                info!(
                    "{}\t\t\t{}\t{}\t{}%\t<1%",
                    unsafe { CStr::from_ptr(px_task_status_array[x].pcTaskName) }
                        .to_str()
                        .unwrap()
                        .to_owned(),
                    px_task_status_array[x].ulRunTimeCounter,
                    px_task_status_array[x].usStackHighWaterMark,
                    ul_stats_as_percentage
                );
            }
        }
    }
}

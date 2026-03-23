#![allow(unexpected_cfgs)]

use std::{sync::mpsc, thread, time::Duration};

use esp_idf_svc::{
    espnow::EspNow,
    eventloop::EspSystemEventLoop,
    hal::peripherals::Peripherals,
    netif::IpEvent,
    nvs::EspDefaultNvsPartition,
    sys::lcd_bindings::{
        lvgl_port_lock, lvgl_port_unlock, ui_init, ui_tick, waveshare_esp32_s3_rgb_lcd_init,
    },
    wifi::{AccessPointConfiguration, AuthMethod, BlockingWifi, Configuration, EspWifi, WifiEvent},
};
use log::{error, info};

mod command;
mod elm327;
mod error;
mod espnow;
mod http;
mod ui;
use ui::create_trans_chart;

use crate::{espnow::ObdNow, ui::update_trans_chart};

type MacAddr = [u8; 6];
const SSID: &str = "OBD-ESPWIFI";
const PASSWORD: &str = "123456789";

fn main() -> anyhow::Result<()> {
    esp_idf_svc::sys::link_patches();
    esp_idf_svc::log::EspLogger::initialize_default();

    // esp_idf_svc::log::set_target_level("*", log::LevelFilter::Debug).unwrap();

    log::info!("Hello, world!");

    let peripherals = Peripherals::take()?;
    let sys_loop = EspSystemEventLoop::take()?;
    let nvs = EspDefaultNvsPartition::take()?;

    //------
    // WIFI
    //------
    // If the ELM327 reader client disconnects, we stop sending http requests to it
    // and wait for it's espnow notification again
    let (tx_disc, rx_disc) = mpsc::sync_channel::<MacAddr>(2);

    let _sub_ip_assign = sys_loop.subscribe::<IpEvent, _>(move |event| {
        if let IpEvent::ApStaIpAssigned(ip_assignment) = event {
            info!("Got station ip assigned event {ip_assignment:?}");
        }
    })?;

    let _sub_sta_disconnect = sys_loop.subscribe::<WifiEvent, _>(move |event| {
        if let WifiEvent::ApStaDisconnected(disconnect) = event {
            info!("Got station disconnected event {disconnect:?}");

            if let Err(e) = tx_disc.send(disconnect.mac()) {
                error!("Failed to channel disc mac {e}");
            }
        }
    })?;

    let mut wifi = BlockingWifi::wrap(
        EspWifi::new(peripherals.modem, sys_loop.clone(), Some(nvs))?,
        sys_loop,
    )?;

    start_wifi_ap(&mut wifi)?;

    //--------
    // ESPNOW
    //--------
    let espnow = EspNow::take()?;

    ObdNow::start(espnow, rx_disc)?;

    // let (tx_now, rx_now) = espnow::create_channel();

    // espnow.register_recv_cb(move |info, data| espnow::recv_cb(&tx_now, info, data))?;
    // // espnow.

    // info!("ESPNOW starting");
    // thread::spawn(move || espnow::elm327_client_address(rx_now, rx_disc));

    //------------------
    // HTTP Error log
    //------------------
    http::http_log()?;

    //------------------
    // OBD Service loop
    //------------------
    http::service_loop()?;

    unsafe {
        waveshare_esp32_s3_rgb_lcd_init(); // calls port init (which creates timer task) and tick init
        log::info!("lcd init");

        if lvgl_port_lock(-1) {
            log::info!("port lock");

            ui_init();
            create_trans_chart();
            log::info!("ui init...");

            lvgl_port_unlock();
        }
    }

    // _trans_values();

    loop {
        unsafe {
            if lvgl_port_lock(-1) {
                ui_tick(); // needed to update the page info if values change. needs to be thread safe

                lvgl_port_unlock();
            }
        }
        thread::sleep(Duration::from_millis(10));
    }
}

fn start_wifi_ap(wifi: &mut BlockingWifi<EspWifi<'_>>) -> anyhow::Result<()> {
    let wifi_configuration = Configuration::AccessPoint(AccessPointConfiguration {
        ssid: SSID.try_into().unwrap(),
        ssid_hidden: true,
        // auth_method: AuthMethod::WPA2Personal,
        auth_method: AuthMethod::None,
        password: PASSWORD.try_into().unwrap(),
        channel: 1,
        max_connections: 2,
        ..Default::default()
    });

    wifi.set_configuration(&wifi_configuration)?;

    wifi.start()?;
    info!("Wifi started");

    wifi.wait_netif_up()?;
    info!("Wifi netif up");

    Ok(())
}

/// Dummy values to exercise the trans chart
fn _trans_values() {
    thread::spawn(|| {
        loop {
            for i in (170..250)
                .chain((180..=250).rev())
                .chain(180..250)
                .chain((175..=250).rev())
            {
                update_trans_chart(i);

                thread::sleep(Duration::from_millis(200));
            }
        }
    });
}

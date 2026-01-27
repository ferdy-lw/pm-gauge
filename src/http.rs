use std::ffi::CString;
use std::{thread, time::Duration};

use embedded_svc::{http::client::Client as HttpClient, io::Write, utils::io};

use esp_idf_svc::http::Method;
use esp_idf_svc::http::client::EspHttpConnection;
use esp_idf_svc::http::server::EspHttpServer;
use esp_idf_svc::sys::{MALLOC_CAP_DEFAULT, heap_caps_get_free_size};
use log::{debug, error, info};

use anyhow::{Context, Result};

use crate::command::{OBDCommand, OBDResponse};
use crate::elm327;
use crate::error::{MSG_LOGGER, ReadObdError};
use crate::espnow::PEER;
use crate::ui::{Info, STATUS};

const SERVICE_STACK_SIZE: usize = 6144;

pub fn service_loop() -> Result<()> {
    info!("Starting service thread");

    thread::Builder::new()
        .stack_size(SERVICE_STACK_SIZE)
        .spawn(|| {
            let mut client = HttpClient::wrap(EspHttpConnection::new(&Default::default()).unwrap());
            let mut new_client = false; // track if we had to create a new client so the info message can be updated

            let mut commands = [
                (OBDCommand::coolant(), 1),
                (OBDCommand::oil(), 1),
                (OBDCommand::atf(), 1),
                (OBDCommand::oil_pressure(), 1),
                (OBDCommand::gear_clutches(), 1),
                (OBDCommand::rpm_tc_slip(), 1),
                // (OBDCommand::engine_speed(), 1),  // Calculated in rpm_tc_slp
                (OBDCommand::ipw_1(), 1),
                // (OBDCommand::maf(), 1),
                // (OBDCommand::vehicle_speed(), 5),
                // (OBDCommand::avg_cons(), 5),
                (OBDCommand::voltage(), 10),
                (OBDCommand::fuel_level(), 30),
                (OBDCommand::fuel_cons(), 120),
            ];

            let mut count: i32 = 0;

            loop {
                for (command, rate) in commands.iter_mut() {
                    if count % *rate != 0 {
                        continue;
                    }

                    let peer_lock = match PEER.read() {
                        Ok(l) => l,
                        Err(poison) => {
                            error!("Poisoned lock, using inner");
                            poison.into_inner()
                        }
                    };

                    if let Some(peer) = &*peer_lock {
                        match do_service(&peer.url_post, &mut client, &command.service) {
                            Ok(obdresponse) => {
                                if let Err(e) = (command.set_ui)(&obdresponse.data) {
                                    error!("Failed to calculate/set display value. {e}");
                                }

                                if new_client {
                                    // the info line was set when we created it. We only want to
                                    // clear the info line once, when we get another good response
                                    Info::set_info(&Info::None);
                                    new_client = false;
                                }
                            }

                            Err(e) => {
                                error!(
                                    "Could not parse response into OBD result ({:?}), {e}",
                                    command.service
                                );

                                MSG_LOGGER.log(format!("Response Error, {e}"));

                                // If we get a client failure it will likely panic on the next use,
                                // create a new client for the next attempt
                                if let Some(&ReadObdError::HttpPostError) = e.downcast_ref() {
                                    client = HttpClient::wrap(
                                        EspHttpConnection::new(&Default::default()).unwrap(),
                                    );
                                    error!("Had to create new client");
                                    Info::set_info(&Info::LostClient);
                                    new_client = true;
                                }
                            }
                        }
                    } else {
                        debug!("No peer, not requesting");
                    }

                    drop(peer_lock);
                    thread::sleep(Duration::from_millis(10));
                }

                count = count.wrapping_add(1);
                // thread::sleep(Duration::from_millis(100));

                if count % 50 == 0 {
                    print_stack_remaining_size(SERVICE_STACK_SIZE);
                }
            }
        })?;

    Ok(())
}

fn do_service(
    url: &str,
    client: &mut HttpClient<EspHttpConnection>,
    service: &[u8],
) -> Result<OBDResponse> {
    match post_request(url, client, service) {
        Ok(response) => {
            elm327::to_values(4, &response) //DA10F1 is 4 bytes of header
        }
        Err(e) => Err(ReadObdError::HttpPostError).with_context(|| format!("Post error ({e:?}")),
    }
}

fn post_request(
    url: &str,
    client: &mut HttpClient<EspHttpConnection>,
    payload: &[u8],
) -> Result<String> {
    // Prepare headers and URL
    let content_length_header = format!("{}", payload.len());
    let headers = [
        ("content-type", "text/plain"),
        ("content-length", &*content_length_header),
    ];

    // Send request
    let mut request = client.post(url, &headers)?;
    request.write_all(payload)?;
    request.flush()?;
    debug!("-> POST {url}");
    let mut response = request.submit()?;

    // Process response
    let status = response.status();
    debug!("<- {status}");
    let mut buf = [0u8; 1024];
    let bytes_read = io::try_read_full(&mut response, &mut buf).map_err(|e| e.0)?;
    debug!("Read {bytes_read} bytes");

    match std::str::from_utf8(&buf[0..bytes_read]) {
        Ok(body_string) => {
            debug!(
                "Response body (truncated to {} bytes): {:?}",
                buf.len(),
                body_string
            );
            Ok(body_string.to_owned())
        }
        Err(e) => Err(e).with_context(|| format!("bytes {:?}", &buf[0..bytes_read]))?,
    }
}

fn print_stack_remaining_size(stack_size: usize) {
    let stack_free =
        unsafe { esp_idf_svc::sys::uxTaskGetStackHighWaterMark(core::ptr::null_mut()) } as usize;
    let used = stack_size - stack_free;
    info!("stack use high water mark {used}/{stack_size}");

    let heap = unsafe { heap_caps_get_free_size(MALLOC_CAP_DEFAULT) };

    STATUS.write().unwrap().replace(
        CString::new(format!(
            "stack use high water mark {used}/{stack_size}\r\nHeap free {heap}\r\n"
        ))
        .unwrap(),
    );
}

pub fn http_log() -> Result<()> {
    info!("Starting http log thread");

    thread::Builder::new()
        .stack_size(SERVICE_STACK_SIZE)
        .spawn(|| {
            let server_configuration = esp_idf_svc::http::server::Configuration {
                max_sessions: 4,
                max_open_sockets: 2,
                ..Default::default()
            };

            let mut server = match EspHttpServer::new(&server_configuration) {
                Ok(s) => s,
                Err(e) => {
                    error!("Failed to create log server, {e}");
                    return;
                }
            };

            if let Err(e) = server.fn_handler::<anyhow::Error, _>("/log", Method::Get, |req| {
                req.into_response(200, Some("OK"), &[("Content-Type", "text/plain")])?
                    .write_all(MSG_LOGGER.get_messages().as_bytes())
                    .map_err(anyhow::Error::from)
            }) {
                error!("Failed to create log server handler, {e}");
                return;
            }

            loop {
                thread::sleep(Duration::from_millis(500));
            }
        })?;

    Ok(())
}

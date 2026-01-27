use std::{
    ffi::{CStr, CString},
    ptr,
    sync::{
        LazyLock, RwLock,
        atomic::{AtomicBool, AtomicI16, AtomicU8, AtomicU16, Ordering},
    },
};

use esp_idf_svc::sys::lcd_bindings::{
    LV_CHART_AXIS_PRIMARY_Y, LV_CHART_TYPE_LINE, LV_CHART_UPDATE_MODE_SHIFT, LV_OPA_20,
    LV_PART_INDICATOR, LV_PART_MAIN, lv_area_t, lv_chart_add_series, lv_chart_axis_t,
    lv_chart_draw_part_type_t_LV_CHART_DRAW_PART_DIV_LINE_INIT, lv_chart_get_series_next,
    lv_chart_get_x_start_point, lv_chart_get_y_array, lv_chart_refresh, lv_chart_series_t,
    lv_chart_set_all_value, lv_chart_set_axis_tick, lv_chart_set_next_value,
    lv_chart_set_point_count, lv_chart_set_range, lv_chart_set_type, lv_chart_set_update_mode,
    lv_chart_t, lv_chart_type_t, lv_chart_update_mode_t, lv_draw_rect, lv_draw_rect_dsc_init,
    lv_draw_rect_dsc_t, lv_event_code_t_LV_EVENT_DRAW_PART_BEGIN, lv_event_get_draw_part_dsc,
    lv_event_get_target, lv_event_t, lv_obj_add_event_cb, lv_obj_get_content_height,
    lv_obj_get_scroll_top, lv_obj_get_style_prop, lv_obj_set_style_width, lv_obj_t,
    lv_palette_main, lv_palette_t_LV_PALETTE_BLUE, lv_palette_t_LV_PALETTE_RED,
    lv_palette_t_LV_PALETTE_YELLOW, lv_style_prop_t_LV_STYLE_BORDER_WIDTH,
    lv_style_prop_t_LV_STYLE_PAD_TOP, lvgl_port_lock, lvgl_port_unlock, objects,
};

pub static COOLANT_TEMP: RwLock<f32> = RwLock::new(0f32);
pub static ENGINE_TEMP: RwLock<f32> = RwLock::new(0f32);
pub static TRANS_TEMP: RwLock<f32> = RwLock::new(0f32);
pub static OIL_PRESS: AtomicU8 = AtomicU8::new(0);
pub static VOLTAGE: RwLock<f32> = RwLock::new(0f32);
pub static FUEL_LEVEL: AtomicU16 = AtomicU16::new(0);
pub static AVG_CONS: AtomicU16 = AtomicU16::new(0);
pub static SLIP: AtomicI16 = AtomicI16::new(0);
pub static CLUTCH: AtomicU8 = AtomicU8::new(0);
pub static GEAR: RwLock<&CStr> = RwLock::new(c"");
pub static OBD_CONNECTED: AtomicBool = AtomicBool::new(false);

static INFO: RwLock<&CStr> = RwLock::new(c"");
pub static STATUS: RwLock<Option<CString>> = RwLock::new(None);

static EMPTY_STR: LazyLock<CString> = LazyLock::new(|| CString::new("").unwrap());

#[derive(PartialEq)]
pub enum Info {
    None,
    NoPeer,
    LostClient,
}

impl Info {
    pub fn set_info(info: &Info) {
        let connected = info == &Info::None;
        OBD_CONNECTED.store(connected, Ordering::Relaxed);

        let info = match info {
            Info::None => c"",
            Info::NoPeer => c"NO OBD",
            Info::LostClient => c"LOST OBD",
        };

        *INFO.write().unwrap() = info;
    }
}

// STATUS
//-------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_status() -> *const ::core::ffi::c_char {
    STATUS
        .read()
        .unwrap()
        .as_ref()
        .unwrap_or(&EMPTY_STR)
        .as_ptr()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_status(_value: *const ::core::ffi::c_char) {
    // NOOP
}

// INFO
//------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_info() -> *const ::core::ffi::c_char {
    (*INFO.read().unwrap()).as_ptr()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_info(_value: *const ::core::ffi::c_char) {
    // NOOP
}

// COOLANT
//---------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_coolant_temp() -> f32 {
    *COOLANT_TEMP.read().unwrap()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_coolant_temp(_value: f32) {
    // NOOP
}

// ENGINE
//--------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_engine_temp() -> f32 {
    *ENGINE_TEMP.read().unwrap()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_engine_temp(_value: f32) {
    // NOOP
}

// TRANS
//-------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_trans_temp() -> f32 {
    *TRANS_TEMP.read().unwrap()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_trans_temp(_value: f32) {
    // NOOP
}

// OIL PRESS
//-----------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_oil_press() -> i32 {
    OIL_PRESS.load(Ordering::Relaxed) as i32
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_oil_press(_value: i32) {
    // NOOP
}

// VOLTAGE
//---------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_voltage() -> f32 {
    *VOLTAGE.read().unwrap()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_voltage(_value: f32) {
    // NOOP
}

// FUEL
//------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_fuel_level() -> i32 {
    FUEL_LEVEL.load(Ordering::Relaxed) as i32
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_fuel_level(_value: i32) {
    // NOOP
}

// CONS
//------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_avg_cons() -> i32 {
    AVG_CONS.load(Ordering::Relaxed) as i32
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_avg_cons(_value: i32) {
    // NOOP
}

// SLIP
// ----
#[unsafe(no_mangle)]
pub extern "C" fn get_var_slip() -> i32 {
    SLIP.load(Ordering::Relaxed) as i32
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_slip(_value: i32) {
    // NOOP
}

// CLUTCH
// ------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_clutch() -> i32 {
    CLUTCH.load(Ordering::Relaxed) as i32
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_clutch(_value: i32) {
    // NOOP
}

// GEAR
// ----
#[unsafe(no_mangle)]
pub extern "C" fn get_var_gear() -> *const ::core::ffi::c_char {
    (*GEAR.read().unwrap()).as_ptr()
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_gear(_value: *const ::core::ffi::c_char) {
    // NOOP
}

pub fn set_gear(gear: u16) {
    let gear = if gear == 1 {
        c"N"
    } else if gear == 2 {
        c"R"
    } else if gear == 4 {
        c"1"
    } else if gear == 8 {
        c"2"
    } else if gear == 16 {
        c"3"
    } else if gear == 32 {
        c"4"
    } else if gear == 128 {
        c"5"
    } else if gear == 256 {
        c"6"
    } else {
        c""
    };

    *GEAR.write().unwrap() = gear;
}

// OBD Connect Btn
//-----------------
#[unsafe(no_mangle)]
pub extern "C" fn get_var_obd_connected() -> bool {
    OBD_CONNECTED.load(Ordering::Relaxed)
}

#[unsafe(no_mangle)]
pub extern "C" fn set_var_obd_connected(_value: bool) {
    // NOOP
}

/// Create the transmission chart. This MUST be called while holding the lv lock
pub unsafe fn create_trans_chart() {
    unsafe {
        let chart = objects.trans_chart;

        lv_obj_set_style_width(chart, 0, LV_PART_INDICATOR);
        lv_chart_set_type(chart, LV_CHART_TYPE_LINE as lv_chart_type_t);
        lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT as lv_chart_update_mode_t);
        lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y as lv_chart_axis_t, 40, 60);
        lv_chart_set_axis_tick(
            chart,
            LV_CHART_AXIS_PRIMARY_Y as lv_chart_axis_t,
            10,
            5,
            5,
            5,
            true,
            50,
        );

        lv_chart_set_point_count(chart, 25);
        let series1 = lv_chart_add_series(
            chart,
            lv_palette_main(lv_palette_t_LV_PALETTE_BLUE),
            LV_CHART_AXIS_PRIMARY_Y as lv_chart_axis_t,
        );

        lv_chart_set_all_value(chart, series1, 50);

        lv_obj_add_event_cb(
            chart,
            Some(trans_chart_draw_event_cb),
            lv_event_code_t_LV_EVENT_DRAW_PART_BEGIN,
            ptr::null_mut(),
        );
    }
}

const HOT_TRANS: i16 = 200;
const WARN_TRANS: i16 = 190;
const TICK_COUNT: i16 = 20;

/// Draw a red rectangle on the chart representing the hot point. The point is found on the tick range and
/// the rectangle bottom will float from the hot point tick, or the entire chart will be covered if the whole
/// range has gone above the hot point
#[unsafe(no_mangle)]
pub unsafe extern "C" fn trans_chart_draw_event_cb(event: *mut lv_event_t) {
    unsafe {
        let chart = lv_event_get_target(event);

        let draw_part_dsc = *lv_event_get_draw_part_dsc(event);

        if draw_part_dsc.type_ == lv_chart_draw_part_type_t_LV_CHART_DRAW_PART_DIV_LINE_INIT {
            let ser = lv_chart_get_series_next(chart, ptr::null());

            let (min, max) = chart_range(chart, ser);

            if max > WARN_TRANS {
                let border_width = lv_obj_get_style_prop(
                    chart,
                    LV_PART_MAIN,
                    lv_style_prop_t_LV_STYLE_BORDER_WIDTH,
                )
                .num as i16;
                let pad_top = lv_obj_get_style_prop(
                    chart,
                    LV_PART_MAIN,
                    lv_style_prop_t_LV_STYLE_PAD_TOP,
                )
                .num as i16;
                let h = (lv_obj_get_content_height(chart) as i32
                    * (*(chart as *mut lv_chart_t)).zoom_y as i32)
                    >> 8;

                let y_ofs = pad_top + border_width - lv_obj_get_scroll_top(chart);

                let y2 = |tick| (y_ofs as i32 + ((h - 1) * tick as i32) / TICK_COUNT as i32) as i16;

                let (warn, hot) = if min >= HOT_TRANS {
                    // all red
                    (
                        None,
                        Some(lv_area_t {
                            x1: (*chart).coords.x1,
                            y1: (*chart).coords.y1 + y_ofs,
                            x2: (*chart).coords.x2,
                            y2: (*chart).coords.y1 + y2(max - min),
                        }),
                    )
                } else {
                    let hot = 0.max(max - HOT_TRANS); // there may not be any red to show
                    let hot = if hot == 0 { 0 } else { y2(hot) };

                    let warn = y2(max - WARN_TRANS.max(min)); // there will always be some yellow because we're not all red

                    let warn = Some(lv_area_t {
                        x1: (*chart).coords.x1,
                        y1: (*chart).coords.y1 + if hot == 0 { y_ofs } else { hot + 1 },
                        x2: (*chart).coords.x2,
                        y2: (*chart).coords.y1 + warn,
                    });

                    let hot = if hot == 0 {
                        None
                    } else {
                        Some(lv_area_t {
                            x1: (*chart).coords.x1,
                            y1: (*chart).coords.y1 + y_ofs,
                            x2: (*chart).coords.x2,
                            y2: (*chart).coords.y1 + hot,
                        })
                    };

                    (warn, hot)
                };

                if let Some(hot_area) = hot {
                    let mut rect_dsc: lv_draw_rect_dsc_t = Default::default();
                    lv_draw_rect_dsc_init(&mut rect_dsc);

                    rect_dsc.bg_opa = LV_OPA_20 as _;
                    rect_dsc.bg_color = lv_palette_main(lv_palette_t_LV_PALETTE_RED);

                    lv_draw_rect(draw_part_dsc.draw_ctx, &rect_dsc, &hot_area);
                };

                if let Some(warn_area) = warn {
                    let mut rect_dsc: lv_draw_rect_dsc_t = Default::default();
                    lv_draw_rect_dsc_init(&mut rect_dsc);

                    rect_dsc.bg_opa = LV_OPA_20 as _;
                    rect_dsc.bg_color = lv_palette_main(lv_palette_t_LV_PALETTE_YELLOW);

                    lv_draw_rect(draw_part_dsc.draw_ctx, &rect_dsc, &warn_area);
                };
            };
        }
    }
}

/// Add a new value into the transmission chart
pub fn update_trans_chart(value: i16) {
    unsafe {
        if lvgl_port_lock(-1) {
            let chart = objects.trans_chart;

            let ser = lv_chart_get_series_next(chart, ptr::null());

            lv_chart_set_next_value(chart, ser, value);

            let range = chart_range(chart, ser);
            lv_chart_set_range(
                chart,
                LV_CHART_AXIS_PRIMARY_Y as lv_chart_axis_t,
                range.0,
                range.1,
            );

            lv_chart_refresh(chart);

            lvgl_port_unlock();
        }
    }
}

unsafe fn chart_range(chart: *mut lv_obj_t, ser: *mut lv_chart_series_t) -> (i16, i16) {
    unsafe {
        let points = lv_chart_get_y_array(chart, ser);
        let oldest_idx = lv_chart_get_x_start_point(chart, ser) as usize;

        let oldest_value = *(points.add(oldest_idx));
        let newest_value = *(points.add(if oldest_idx == 0 { 24 } else { oldest_idx - 1 }));

        let min_max = if oldest_value < newest_value {
            (oldest_value, newest_value)
        } else {
            (newest_value, oldest_value)
        };

        // Range total n Ticks, 4 gaps, 6 minor per gap, 5 major - one tick mark per unit in range
        // If we are out of range make sure the points are still shown
        let margin = 0.max((TICK_COUNT + 1) - (min_max.1 - min_max.0 + 1));
        let top_margin = if margin % 2 == 0 {
            margin / 2
        } else {
            margin / 2 + 1
        };

        (min_max.0 - (margin - top_margin), min_max.1 + top_margin)
    }
}

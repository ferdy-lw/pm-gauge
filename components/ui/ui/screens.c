#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static lv_meter_scale_t * scale0;
static lv_meter_indicator_t * indicator1;
static lv_meter_indicator_t * indicator2;
static lv_meter_indicator_t * indicator3;
static lv_meter_indicator_t * indicator4;
static lv_meter_indicator_t * indicator5;
static lv_meter_indicator_t * indicator6;
static lv_meter_scale_t * scale7;
static lv_meter_indicator_t * indicator8;
static lv_meter_indicator_t * indicator9;
static lv_meter_indicator_t * indicator10;
static lv_meter_indicator_t * indicator11;
static lv_meter_scale_t * scale12;
static lv_meter_indicator_t * indicator13;
static lv_meter_scale_t * scale14;
static lv_meter_indicator_t * indicator15;
static lv_meter_indicator_t * indicator16;

static void event_handler_cb_temps_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_status_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_status_status_text(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 5, 3, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_status_obd_conn_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 6, 0, e);
    }
}

static void event_handler_cb_slip_clutches_slip(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 0, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_lr(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 5, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_24(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 6, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_od(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 7, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_ud(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 8, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_lc(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 9, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_dr(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 10, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_slip_clutches_clutch_cc(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 11, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

void create_screen_temps() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.temps = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 40);
            add_style_tab_panel(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff2f6b1), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // info
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.info = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 400, 40);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfff10b0b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 824, 0);
                    lv_obj_set_size(obj, 100, 40);
                    add_style_tab_active(obj);
                    lv_label_set_text(obj, "Temps");
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 924, 0);
                    lv_obj_set_size(obj, 100, 40);
                    lv_obj_add_event_cb(obj, event_handler_cb_temps_obj1, LV_EVENT_ALL, flowState);
                    add_style_tab_button(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Status");
                        }
                    }
                }
            }
        }
        {
            // trans_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.trans_meter = obj;
            lv_obj_set_pos(obj, 378, 47);
            lv_obj_set_size(obj, 338, 338);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale0 = scale;
                lv_meter_set_scale_ticks(obj, scale, 41, 1, 10, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 10, 3, 10, lv_color_hex(0xff7c7c7c), 15);
                lv_meter_set_scale_range(obj, scale, 40, 220, 300, 120);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 3, lv_color_hex(0xff0000ff), 0);
                    indicator1 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 40);
                    lv_meter_set_indicator_end_value(obj, indicator, 90);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_scale_lines(obj, scale, lv_color_hex(0xff0000ff), lv_color_hex(0xff0000ff), false, 3);
                    indicator2 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 40);
                    lv_meter_set_indicator_end_value(obj, indicator, 90);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 3, lv_color_hex(0xff00ff00), 0);
                    indicator3 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 160);
                    lv_meter_set_indicator_end_value(obj, indicator, 185);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 3, lv_color_hex(0xffff0000), 0);
                    indicator4 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 195);
                    lv_meter_set_indicator_end_value(obj, indicator, 220);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_scale_lines(obj, scale, lv_color_hex(0xffff0000), lv_color_hex(0xffff0000), false, 10);
                    indicator5 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 195);
                    lv_meter_set_indicator_end_value(obj, indicator, 220);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 3, lv_color_hex(0xff7c7c7c), -25);
                    indicator6 = indicator;
                }
            }
            add_style_meter_num(obj);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff747474), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 90, 243);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffbdbaba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Transmission");
                }
                {
                    // trans value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.trans_value = obj;
                    lv_obj_set_pos(obj, 112, 112);
                    lv_obj_set_size(obj, 100, 100);
                    add_style_gauge_num(obj);
                    lv_obj_set_style_pad_top(obj, 31, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_ofs_x(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_ofs_y(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff40795c), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 787, 47);
            lv_obj_set_size(obj, 180, 180);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_slip_clutches(obj, getFlowState(flowState, 9), 3);
        }
        {
            // pressure
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pressure = obj;
            lv_obj_set_pos(obj, 780, 212);
            lv_obj_set_size(obj, 190, 90);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff747474), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, -10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 27, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Oil Pressure");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 68, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_gauge_num(obj);
                    lv_obj_set_style_shadow_width(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xffc2ebf8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc2ebf8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // voltage
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.voltage = obj;
            lv_obj_set_pos(obj, 780, 308);
            lv_obj_set_size(obj, 190, 90);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff747474), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, -10, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 51, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Voltage");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, 37, 6);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_gauge_num(obj);
                    lv_obj_set_style_shadow_width(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xfff6d9b3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff6d9b3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // temp_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temp_meter = obj;
            lv_obj_set_pos(obj, 10, 47);
            lv_obj_set_size(obj, 338, 338);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale7 = scale;
                lv_meter_set_scale_ticks(obj, scale, 29, 0, 15, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 4, 2, 45, lv_color_hex(0xfff0f0f0), 15);
                lv_meter_set_scale_range(obj, scale, 40, 260, 250, 90);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 2, lv_color_hex(0xffff0000), 0);
                    indicator8 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 220);
                    lv_meter_set_indicator_end_value(obj, indicator, 260);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_scale_lines(obj, scale, lv_color_hex(0xffff0000), lv_color_hex(0xffff0000), false, 5);
                    indicator9 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 220);
                    lv_meter_set_indicator_end_value(obj, indicator, 260);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 15, lv_color_hex(0xffe75bf1), -10);
                    indicator10 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 40);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 15, lv_color_hex(0xff6bde88), -28);
                    indicator11 = indicator;
                    lv_meter_set_indicator_start_value(obj, indicator, 40);
                }
            }
            add_style_meter_num(obj);
            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff858585), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // coolant_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.coolant_value = obj;
                    lv_obj_set_pos(obj, 218, 158);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_gauge_num(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 126, 174);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffeb90f1), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Coolant");
                }
                {
                    // engine_value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.engine_value = obj;
                    lv_obj_set_pos(obj, 218, 208);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_gauge_num(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 133, 225);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff98dfaa), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Engine");
                }
            }
        }
        {
            // trans_chart
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.trans_chart = obj;
            lv_obj_set_pos(obj, 317, 405);
            lv_obj_set_size(obj, 653, 180);
        }
        {
            // fuel_cons
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fuel_cons = obj;
            lv_obj_set_pos(obj, 10, 381);
            lv_obj_set_size(obj, 250, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // cons
                    lv_obj_t *obj = lv_meter_create(parent_obj);
                    objects.cons = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 200, 200);
                    {
                        lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                        scale12 = scale;
                        lv_meter_set_scale_ticks(obj, scale, 25, 1, 5, lv_color_hex(0xffa0a0a0));
                        lv_meter_set_scale_major_ticks(obj, scale, 6, 2, 15, lv_color_hex(0xff000000), 12);
                        lv_meter_set_scale_range(obj, scale, 0, 35, 215, 90);
                        {
                            lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 15, lv_color_hex(0xff6d6ddf), 0);
                            indicator13 = indicator;
                            lv_meter_set_indicator_start_value(obj, indicator, 0);
                        }
                    }
                    add_style_meter_num(obj);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff858585), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            objects.obj9 = obj;
                            lv_obj_set_pos(obj, 44, 62);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_img_set_src(obj, &img_mpg);
                            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff6d6ddf), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 59, 87);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // cons_whole
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.cons_whole = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, ".");
                                }
                                {
                                    // cons_frac
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.cons_frac = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj10 = obj;
                            lv_obj_set_pos(obj, 72, 115);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff6d6ddf), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "mpg");
                        }
                    }
                }
                {
                    // fuel
                    lv_obj_t *obj = lv_meter_create(parent_obj);
                    objects.fuel = obj;
                    lv_obj_set_pos(obj, 121, 40);
                    lv_obj_set_size(obj, 170, 170);
                    {
                        lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                        scale14 = scale;
                        lv_meter_set_scale_ticks(obj, scale, 25, 1, 5, lv_color_hex(0xffa0a0a0));
                        lv_meter_set_scale_major_ticks(obj, scale, 6, 2, 15, lv_color_hex(0xff000000), 10);
                        lv_meter_set_scale_range(obj, scale, 0, 24, 180, 90);
                        {
                            lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 15, lv_color_hex(0xff6bde88), 0);
                            indicator15 = indicator;
                            lv_meter_set_indicator_start_value(obj, indicator, 0);
                        }
                        {
                            lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 15, lv_color_hex(0xffff0000), 0);
                            indicator16 = indicator;
                            lv_meter_set_indicator_start_value(obj, indicator, 0);
                        }
                    }
                    add_style_meter_num(obj);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff858585), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_ofs_x(obj, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_ofs_y(obj, -2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, -4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fuel_ico
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            objects.fuel_ico = obj;
                            lv_obj_set_pos(obj, 74, 40);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_img_set_src(obj, &img_fuel);
                            add_style_fuel_ico(obj);
                            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff5bf181), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 39, 71);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // fuel_whole
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.fuel_whole = obj;
                                    lv_obj_set_pos(obj, 41, 66);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 80, 56);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, ".");
                                }
                                {
                                    // fuel_frac
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.fuel_frac = obj;
                                    lv_obj_set_pos(obj, 85, 69);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_robo_med_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj11 = obj;
                            lv_obj_set_pos(obj, 72, 99);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff5bf181), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "gal");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj12 = obj;
                    lv_obj_set_pos(obj, 207, 28);
                    lv_obj_set_size(obj, 48, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj13 = obj;
                    lv_obj_set_pos(obj, 207, 186);
                    lv_obj_set_size(obj, 44, 31);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_temps();
}

void tick_screen_temps() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.info);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.info;
            lv_label_set_text(objects.info, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.trans_meter)->indicator_ll;
        int index = 5;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 6, 3, "Failed to evaluate Value in Meter widget");
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.trans_meter;
                lv_meter_set_indicator_value(objects.trans_meter, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.trans_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.trans_value;
            lv_label_set_text(objects.trans_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_slip_clutches(getFlowState(flowState, 9), 3);
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj5;
            lv_label_set_text(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temp_meter)->indicator_ll;
        int index = 2;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 16, 3, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temp_meter;
                lv_meter_set_indicator_end_value(objects.temp_meter, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temp_meter)->indicator_ll;
        int index = 3;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 16, 4, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temp_meter;
                lv_meter_set_indicator_end_value(objects.temp_meter, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.coolant_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.coolant_value;
            lv_label_set_text(objects.coolant_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.engine_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.engine_value;
            lv_label_set_text(objects.engine_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.cons)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 23, 3, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.cons;
                lv_meter_set_indicator_end_value(objects.cons, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.cons_whole);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.cons_whole;
            lv_label_set_text(objects.cons_whole, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.cons_frac);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.cons_frac;
            lv_label_set_text(objects.cons_frac, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.fuel)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 30, 3, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.fuel;
                lv_meter_set_indicator_end_value(objects.fuel, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.fuel)->indicator_ll;
        int index = 1;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 30, 4, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.fuel;
                lv_meter_set_indicator_end_value(objects.fuel, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.fuel_whole);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.fuel_whole;
            lv_label_set_text(objects.fuel_whole, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.fuel_frac);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.fuel_frac;
            lv_label_set_text(objects.fuel_frac, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_status() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.status = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 40);
            add_style_tab_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 824, 0);
                    lv_obj_set_size(obj, 100, 40);
                    lv_obj_add_event_cb(obj, event_handler_cb_status_obj2, LV_EVENT_ALL, flowState);
                    add_style_tab_button(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Temps");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 924, 0);
            lv_obj_set_size(obj, 100, 40);
            add_style_tab_active(obj);
            lv_label_set_text(obj, "Status");
        }
        {
            // status_text
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.status_text = obj;
            lv_obj_set_pos(obj, 0, 61);
            lv_obj_set_size(obj, 1024, 117);
            lv_textarea_set_max_length(obj, 1024);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_status_status_text, LV_EVENT_ALL, flowState);
        }
        {
            // obd_conn_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obd_conn_btn = obj;
            lv_obj_set_pos(obj, 88, 203);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_status_obd_conn_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj14 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 16, 216);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "OBD");
        }
    }
    
    tick_screen_status();
}

void tick_screen_status() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.status_text);
        uint32_t max_length = lv_textarea_get_max_length(objects.status_text);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.status_text;
            lv_textarea_set_text(objects.status_text, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj14);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj14;
            lv_label_set_text(objects.obj14, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_slip_clutches(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 178, 178);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // slip
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 178, 178);
                    lv_arc_set_range(obj, 0, 800);
                    lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_slip, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffd7e9db), LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 0, 50);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_robo_med_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // slip_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                            lv_obj_set_pos(obj, 0, 115);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_robo_med_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 14, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // clutch_lr
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 235);
                            lv_arc_set_bg_end_angle(obj, 245);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_lr, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffe06c6c), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_24
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 245);
                            lv_arc_set_bg_end_angle(obj, 255);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_24, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff6ce0d8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_od
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 255);
                            lv_arc_set_bg_end_angle(obj, 265);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_od, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff776ce0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_ud
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 265);
                            lv_arc_set_bg_end_angle(obj, 275);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_ud, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffe06ce0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_lc
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 275);
                            lv_arc_set_bg_end_angle(obj, 285);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_lc, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff6cace0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_dr
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 285);
                            lv_arc_set_bg_end_angle(obj, 295);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_dr, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffdf6a6a), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // clutch_cc
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 150, 150);
                            lv_arc_set_range(obj, 0, 1);
                            lv_arc_set_bg_start_angle(obj, 295);
                            lv_arc_set_bg_end_angle(obj, 305);
                            lv_obj_add_event_cb(obj, event_handler_cb_slip_clutches_clutch_cc, LV_EVENT_ALL, flowState);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_clutch(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff6adf87), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_slip_clutches(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    {
        int32_t new_val = evalIntegerProperty(flowState, 0, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 9]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 9];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 9], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 1]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 1], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 5, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 2]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 2], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 6, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 7, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 4], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 9, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 6]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 6];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 6], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 10, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 7]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 7];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 7], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 11, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 8];
            lv_arc_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 8], new_val);
            tick_value_change_obj = NULL;
        }
    }
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Temps", "Status" };
static const char *object_names[] = { "temps", "status", "obj0", "obj0__slip", "obj0__slip_label", "obj0__clutch_lr", "obj0__clutch_24", "obj0__clutch_od", "obj0__clutch_ud", "obj0__clutch_lc", "obj0__clutch_dr", "obj0__clutch_cc", "obj0__obj0", "obj1", "obj2", "obd_conn_btn", "obj3", "info", "trans_meter", "obj4", "trans_value", "pressure", "obj5", "voltage", "obj6", "temp_meter", "coolant_value", "obj7", "engine_value", "obj8", "trans_chart", "fuel_cons", "cons", "obj9", "cons_whole", "cons_frac", "obj10", "fuel", "fuel_ico", "fuel_whole", "fuel_frac", "obj11", "obj12", "obj13", "status_text", "obj14" };
static const char *style_names[] = { "tab_panel", "tab_button", "tab_active", "hot_temp", "gauge_num", "low_fuel", "low_fuel_meter", "meter_num", "low_fuel_ico", "fuel_ico", "clutch" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_temps,
    tick_screen_status,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_temps();
    create_screen_status();
}


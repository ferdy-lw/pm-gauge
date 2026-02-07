#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: tab_panel
//

void init_style_tab_panel_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_bg_color(style, lv_color_hex(0xfff2f6b1));
};

lv_style_t *get_style_tab_panel_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_panel_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_panel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_panel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_panel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_panel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: tab_button
//

void init_style_tab_button_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 0);
    lv_style_set_bg_color(style, lv_color_hex(0xfff2f6b1));
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_color(style, lv_color_hex(0xffffffff));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_side(style, LV_BORDER_SIDE_LEFT);
};

lv_style_t *get_style_tab_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_button_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: tab_active
//

void init_style_tab_active_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xfff5f5f5));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_pad_top(style, 11);
    lv_style_set_pad_bottom(style, 11);
    lv_style_set_pad_left(style, 20);
    lv_style_set_pad_right(style, 20);
    lv_style_set_border_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT);
};

lv_style_t *get_style_tab_active_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_active_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_active(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_active_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_active(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_active_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: hot_temp
//

void init_style_hot_temp_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_hot_temp_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_hot_temp_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_hot_temp(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_hot_temp_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_hot_temp(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_hot_temp_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: gauge_num
//

void init_style_gauge_num_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_pad_top(style, 5);
    lv_style_set_text_font(style, &ui_font_robo_med_44);
};

lv_style_t *get_style_gauge_num_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_gauge_num_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_gauge_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_gauge_num_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_gauge_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_gauge_num_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: low_fuel
//

void init_style_low_fuel_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_low_fuel_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_low_fuel_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_low_fuel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_low_fuel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_low_fuel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_low_fuel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: low_fuel_meter
//

void init_style_low_fuel_meter_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_low_fuel_meter_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_low_fuel_meter_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_low_fuel_meter(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_low_fuel_meter_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_low_fuel_meter(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_low_fuel_meter_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: meter_num
//

void init_style_meter_num_TICKS_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &ui_font_robo_reg_14);
};

lv_style_t *get_style_meter_num_TICKS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_meter_num_TICKS_DEFAULT(style);
    }
    return style;
};

void add_style_meter_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_meter_num_TICKS_DEFAULT(), LV_PART_TICKS | LV_STATE_DEFAULT);
};

void remove_style_meter_num(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_meter_num_TICKS_DEFAULT(), LV_PART_TICKS | LV_STATE_DEFAULT);
};

//
// Style: low_fuel_ico
//

void init_style_low_fuel_ico_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_img_recolor(style, lv_color_hex(0xffff0000));
    lv_style_set_img_recolor_opa(style, 255);
};

lv_style_t *get_style_low_fuel_ico_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_low_fuel_ico_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_low_fuel_ico(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_low_fuel_ico_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_low_fuel_ico(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_low_fuel_ico_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: fuel_ico
//

void init_style_fuel_ico_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_img_recolor_opa(style, 255);
    lv_style_set_img_recolor(style, lv_color_hex(0xff5bf181));
};

lv_style_t *get_style_fuel_ico_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_fuel_ico_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_fuel_ico(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_fuel_ico_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_fuel_ico(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_fuel_ico_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: clutch
//

void init_style_clutch_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_rounded(style, false);
    lv_style_set_arc_width(style, 8);
};

lv_style_t *get_style_clutch_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_clutch_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_clutch_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_width(style, 8);
    lv_style_set_arc_rounded(style, false);
};

lv_style_t *get_style_clutch_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_clutch_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_clutch_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_opa(style, 0);
};

lv_style_t *get_style_clutch_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_clutch_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_clutch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_clutch_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_clutch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_clutch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_clutch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_clutch_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_clutch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_clutch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_tab_panel,
        add_style_tab_button,
        add_style_tab_active,
        add_style_hot_temp,
        add_style_gauge_num,
        add_style_low_fuel,
        add_style_low_fuel_meter,
        add_style_meter_num,
        add_style_low_fuel_ico,
        add_style_fuel_ico,
        add_style_clutch,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_tab_panel,
        remove_style_tab_button,
        remove_style_tab_active,
        remove_style_hot_temp,
        remove_style_gauge_num,
        remove_style_low_fuel,
        remove_style_low_fuel_meter,
        remove_style_meter_num,
        remove_style_low_fuel_ico,
        remove_style_fuel_ico,
        remove_style_clutch,
    };
    remove_style_funcs[styleIndex](obj);
}


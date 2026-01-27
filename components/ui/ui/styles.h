#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: tab_panel
lv_style_t *get_style_tab_panel_MAIN_DEFAULT();
void add_style_tab_panel(lv_obj_t *obj);
void remove_style_tab_panel(lv_obj_t *obj);

// Style: tab_button
lv_style_t *get_style_tab_button_MAIN_DEFAULT();
void add_style_tab_button(lv_obj_t *obj);
void remove_style_tab_button(lv_obj_t *obj);

// Style: tab_active
lv_style_t *get_style_tab_active_MAIN_DEFAULT();
void add_style_tab_active(lv_obj_t *obj);
void remove_style_tab_active(lv_obj_t *obj);

// Style: hot_temp
lv_style_t *get_style_hot_temp_MAIN_DEFAULT();
void add_style_hot_temp(lv_obj_t *obj);
void remove_style_hot_temp(lv_obj_t *obj);

// Style: gauge_num
lv_style_t *get_style_gauge_num_MAIN_DEFAULT();
void add_style_gauge_num(lv_obj_t *obj);
void remove_style_gauge_num(lv_obj_t *obj);

// Style: low_fuel
lv_style_t *get_style_low_fuel_MAIN_DEFAULT();
void add_style_low_fuel(lv_obj_t *obj);
void remove_style_low_fuel(lv_obj_t *obj);

// Style: low_fuel_meter
lv_style_t *get_style_low_fuel_meter_MAIN_DEFAULT();
void add_style_low_fuel_meter(lv_obj_t *obj);
void remove_style_low_fuel_meter(lv_obj_t *obj);

// Style: meter_num
lv_style_t *get_style_meter_num_TICKS_DEFAULT();
void add_style_meter_num(lv_obj_t *obj);
void remove_style_meter_num(lv_obj_t *obj);

// Style: low_fuel_ico
lv_style_t *get_style_low_fuel_ico_MAIN_DEFAULT();
void add_style_low_fuel_ico(lv_obj_t *obj);
void remove_style_low_fuel_ico(lv_obj_t *obj);

// Style: fuel_ico
lv_style_t *get_style_fuel_ico_MAIN_DEFAULT();
void add_style_fuel_ico(lv_obj_t *obj);
void remove_style_fuel_ico(lv_obj_t *obj);

// Style: clutch
lv_style_t *get_style_clutch_MAIN_DEFAULT();
void add_style_clutch(lv_obj_t *obj);
void remove_style_clutch(lv_obj_t *obj);

// Style: clutch_on
lv_style_t *get_style_clutch_on_MAIN_DEFAULT();
void add_style_clutch_on(lv_obj_t *obj);
void remove_style_clutch_on(lv_obj_t *obj);

// Style: clutch_off
lv_style_t *get_style_clutch_off_MAIN_DEFAULT();
void add_style_clutch_off(lv_obj_t *obj);
void remove_style_clutch_off(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/
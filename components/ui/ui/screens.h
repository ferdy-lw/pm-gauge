#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *temps;
    lv_obj_t *status;
    lv_obj_t *obj0;
    lv_obj_t *obj0__slip;
    lv_obj_t *obj0__slip_label;
    lv_obj_t *obj0__clutch_lr;
    lv_obj_t *obj0__clutch_24;
    lv_obj_t *obj0__clutch_od;
    lv_obj_t *obj0__clutch_ud;
    lv_obj_t *obj0__clutch_lc;
    lv_obj_t *obj0__clutch_dr;
    lv_obj_t *obj0__clutch_cc;
    lv_obj_t *obj0__obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obd_conn_btn;
    lv_obj_t *obj3;
    lv_obj_t *info;
    lv_obj_t *trans_meter;
    lv_obj_t *obj4;
    lv_obj_t *trans_value;
    lv_obj_t *pressure;
    lv_obj_t *obj5;
    lv_obj_t *voltage;
    lv_obj_t *obj6;
    lv_obj_t *temp_meter;
    lv_obj_t *coolant_value;
    lv_obj_t *obj7;
    lv_obj_t *engine_value;
    lv_obj_t *obj8;
    lv_obj_t *trans_chart;
    lv_obj_t *fuel_cons;
    lv_obj_t *cons;
    lv_obj_t *obj9;
    lv_obj_t *cons_whole;
    lv_obj_t *cons_frac;
    lv_obj_t *obj10;
    lv_obj_t *fuel;
    lv_obj_t *fuel_ico;
    lv_obj_t *fuel_whole;
    lv_obj_t *fuel_frac;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *status_text;
    lv_obj_t *obj14;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_TEMPS = 1,
    SCREEN_ID_STATUS = 2,
};

void create_screen_temps();
void tick_screen_temps();

void create_screen_status();
void tick_screen_status();

void create_user_widget_slip_clutches(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_slip_clutches(void *flowState, int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
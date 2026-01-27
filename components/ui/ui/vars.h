#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern const char *get_var_status();
extern void set_var_status(const char *value);
extern float get_var_coolant_temp();
extern void set_var_coolant_temp(float value);
extern float get_var_engine_temp();
extern void set_var_engine_temp(float value);
extern float get_var_trans_temp();
extern void set_var_trans_temp(float value);
extern const char *get_var_info();
extern void set_var_info(const char *value);
extern int32_t get_var_oil_press();
extern void set_var_oil_press(int32_t value);
extern float get_var_voltage();
extern void set_var_voltage(float value);
extern int32_t get_var_fuel_level();
extern void set_var_fuel_level(int32_t value);
extern int32_t get_var_avg_cons();
extern void set_var_avg_cons(int32_t value);
extern bool get_var_obd_connected();
extern void set_var_obd_connected(bool value);
extern int32_t get_var_clutch();
extern void set_var_clutch(int32_t value);
extern int32_t get_var_slip();
extern void set_var_slip(int32_t value);
extern const char *get_var_gear();
extern void set_var_gear(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/
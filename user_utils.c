#pragma once

#include "os_detection.h"
#include QMK_KEYBOARD_H

#include "user_eeprom.h"
#include "user_init.c"
#include "user_layers.h"

void user_enter_layer(uint8_t layer, uint8_t hue, uint8_t sat, uint8_t val) {
    layer_move(layer);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_PINWHEEL_VAL);
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
    return;
}

void user_exit_layer(void) {
    layer_clear();
    rgblight_reload_from_eeprom();
    return;
};

// this function is only for the keys on the ADJUST layer
void user_react_key_press(uint8_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
    wait_ms(100); // 100 ms
    user_enter_layer(_ADJUST, HSV_ADJUST);
    return;
};

void user_override_toggle_post(bool enable) {
    eeconfig_update_user(user_config.raw);
    user_reload_user_eeprom();
    if (enable) {
        user_react_key_press(HSV_RED); // enable
    } else {
        user_react_key_press(HSV_BLUE); // disable
    }
}

bool user_is_macos(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_MACOS;
    } else {
        return user_config.is_macos;
    }
}

bool user_is_ios(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_IOS;
    } else {
        return user_config.is_ios;
    }
}

bool user_is_linux(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_LINUX;
    } else {
        return user_config.is_linux;
    }
}

bool user_is_windows(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_WINDOWS;
    } else {
        return user_config.is_windows;
    }
}

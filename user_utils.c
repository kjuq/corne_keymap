#pragma once

#include "_wait.h"
#include "eeconfig.h"
#include "os_detection.h"

#include "rgb_matrix.h"
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

bool user_is_macos(void) {
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_MACOS;
    } else {
        return user_config.is_macos;
    }
}

bool user_is_ios(void) {
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_IOS;
    } else {
        return user_config.is_ios;
    }
}

bool user_is_linux(void) {
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_LINUX;
    } else {
        return user_config.is_linux;
    }
}

bool user_is_windows(void) {
    if (user_config.is_auto_detect_os) {
        return detected_host_os() == OS_WINDOWS;
    } else {
        return user_config.is_windows;
    }
}

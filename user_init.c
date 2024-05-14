#pragma once

#include "eeconfig.h"

#include "user_eeprom.h"
#include "user_overrides.h"
#include "user_layers.h"

void user_reload_user_eeprom(void) {
    user_config.raw = eeconfig_read_user();

    reload_overrides();

    if (user_config.fnc_tap) {
        default_layer_or((layer_state_t)1 << _FNC_TAP);
    } else {
        default_layer_or((layer_state_t)1 << _FNC_TAP);
        default_layer_xor((layer_state_t)1 << _FNC_TAP);
    }
    if (user_config.spc_tap) {
        default_layer_or((layer_state_t)1 << _SPC_TAP);
    } else {
        default_layer_or((layer_state_t)1 << _SPC_TAP);
        default_layer_xor((layer_state_t)1 << _SPC_TAP);
    }
};

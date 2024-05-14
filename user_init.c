#pragma once

#include "user_init.h"

#include QMK_KEYBOARD_H

#include "user_eeprom.h"
#include "user_overrides_utils.c"
#include "user_layers.h"
#include "user_utils.c"

void user_init_macos(void) {
    _common_apple();
}

void user_init_ios(void) {
    _common_apple();
}

void user_init_windows(void) {
    _common_win_linux();
}

void user_init_linux(void) {
    _common_win_linux();
}

void user_init_unsure(void) {
    // do nothing
}

void _common_win_linux(void) {
    user_config.raw        = eeconfig_read_user();
    user_config.override_linux_cmd = true;
    eeconfig_update_user(user_config.raw);
}

void _common_apple(void) {
    user_config.raw        = eeconfig_read_user();
    user_config.override_linux_cmd = false;
    eeconfig_update_user(user_config.raw);
}

void user_reload_user_eeprom(void) {
    user_enable_all_overrides();

    user_config.raw = eeconfig_read_user();

    if (!user_config.override_tab) {
        user_switch_override(&tab_key_override, false);
    }
    if (!user_config.override_enter) {
        user_switch_override(&enter_key_override, false);
    }
    if (!user_config.override_backspace) {
        user_switch_override(&bs_key_override, false);
    }
    if (!user_config.override_delete) {
        user_switch_override(&del_key_override, false);
    }
    if (!user_config.override_arrows) {
        user_switch_override(&up_key_override, false);
        user_switch_override(&down_key_override, false);
        user_switch_override(&right_key_override, false);
        user_switch_override(&left_key_override, false);
    }
    if (!user_config.override_ctrl_u) {
        user_switch_override(&ctrl_u_key_override, false);
    }
    if (!user_config.override_cmd_q) {
        user_switch_override(&cmd_q_override, false);
    }

    if (!user_config.override_modded_esc) {
        user_switch_override(&ctrl_tab_override, false);
        user_switch_override(&alt_tab_override, false);
        user_switch_override(&cmd_tab_override, false);
        user_switch_override(&shift_tab_override, false);
    }

    if (user_is_macos() || user_is_ios() || !user_config.override_word_mv) {
        user_switch_override(&w_fwd_win_override, false);
        user_switch_override(&w_bck_win_override, false);
    }

    if (user_is_linux() || user_is_windows() || !user_config.override_word_mv) {
        user_switch_override(&w_fwd_mac_override, false);
        user_switch_override(&w_bck_mac_override, false);
    }

    if (user_is_macos() || user_is_ios() || !user_config.override_word_dl) {
        user_switch_override(&w_del_win_override, false);
    }

    if (user_is_linux() || user_is_windows() || !user_config.override_word_dl) {
        user_switch_override(&w_del_mac_override, false);
    }

    if (user_is_macos() || user_is_ios() || !user_config.override_home) {
        user_switch_override(&home_key_override, false);
    }
    if (user_is_macos() || user_is_ios() || !user_config.override_end) {
        user_switch_override(&end_key_override, false);
    }

    if (!user_config.override_linux_cmd) {
        user_switch_linux_cmd(false);
    }

    if (!user_config.is_jis_mode) {
        user_switch_jis(false);
    }

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

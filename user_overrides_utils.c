#pragma once

#include "user_overrides_utils.h"

#include QMK_KEYBOARD_H

#include "user_overrides.c"
#include "user_eeprom.h"

static bool false_const = false;

void user_switch_override(key_override_t *override, bool enabled) {
    override->enabled = enabled ? NULL : &false_const;
}

void user_switch_jis(bool enabled) {
    user_switch_override(&jis_at_override, enabled);
    user_switch_override(&jis_circ_override, enabled);
    user_switch_override(&jis_ampr_override, enabled);
    user_switch_override(&jis_astr_override, enabled);
    user_switch_override(&jis_lprn_override, enabled);
    user_switch_override(&jis_rprn_override, enabled);
    user_switch_override(&jis_unds_override, enabled);
    user_switch_override(&jis_plus_override, enabled);
    user_switch_override(&jis_lbrc_override, enabled);
    user_switch_override(&jis_lcbr_override, enabled);
    user_switch_override(&jis_rbrc_override, enabled);
    user_switch_override(&jis_rcbr_override, enabled);
    user_switch_override(&jis_bsls_override, enabled);
    user_switch_override(&jis_pipe_override, enabled);
    user_switch_override(&jis_coln_override, enabled);
    user_switch_override(&jis_quot_override, enabled);
    user_switch_override(&jis_dquo_override, enabled);
    user_switch_override(&jis_grv_override, enabled);
    user_switch_override(&jis_tild_override, enabled);
    user_switch_override(&jis_eql_override, enabled);

    user_switch_override(&jis_s_2_override, enabled);
    user_switch_override(&jis_s_6_override, enabled);
    user_switch_override(&jis_s_7_override, enabled);
    user_switch_override(&jis_s_8_override, enabled);
    user_switch_override(&jis_s_9_override, enabled);
    user_switch_override(&jis_s_0_override, enabled);
    user_switch_override(&jis_s_mins_override, enabled);
    user_switch_override(&jis_s_eql_override, enabled);
    user_switch_override(&jis_s_lbrc_override, enabled);
    user_switch_override(&jis_s_rbrc_override, enabled);
    user_switch_override(&jis_s_bsls_override, enabled);
    user_switch_override(&jis_s_scln_override, enabled);
    user_switch_override(&jis_s_quot_override, enabled);
    user_switch_override(&jis_s_grv_override, enabled);
}

void user_switch_linux_cmd(bool enable) {
    user_switch_override(&linux_a_override, enable);
    user_switch_override(&linux_b_override, enable);
    user_switch_override(&linux_c_override, enable);
    user_switch_override(&linux_d_override, enable);
    user_switch_override(&linux_e_override, enable);
    user_switch_override(&linux_f_override, enable);
    user_switch_override(&linux_g_override, enable);
    user_switch_override(&linux_h_override, enable);
    user_switch_override(&linux_i_override, enable);
    user_switch_override(&linux_j_override, enable);
    user_switch_override(&linux_k_override, enable);
    user_switch_override(&linux_l_override, enable);
    user_switch_override(&linux_m_override, enable);
    user_switch_override(&linux_n_override, enable);
    user_switch_override(&linux_o_override, enable);
    user_switch_override(&linux_p_override, enable);
    user_switch_override(&linux_q_override, enable);
    user_switch_override(&linux_r_override, enable);
    user_switch_override(&linux_s_override, enable);
    user_switch_override(&linux_t_override, enable);
    user_switch_override(&linux_u_override, enable);
    user_switch_override(&linux_v_override, enable);
    user_switch_override(&linux_w_override, enable);
    user_switch_override(&linux_x_override, enable);
    user_switch_override(&linux_y_override, enable);
    user_switch_override(&linux_z_override, enable);
    user_switch_override(&linux_com_override, enable);
    user_switch_override(&linux_dot_override, enable);
}

void user_enable_all_overrides(void) {
    for (int i = 0; key_overrides[i] != NULL; i++) {
        key_override_t *ko = (key_override_t *)key_overrides[i];
        ko->enabled        = NULL;
    }
};

void user_disable_all_overrides(void) {
    for (int i = 0; key_overrides[i] != NULL; i++) {
        key_override_t *ko = (key_override_t *)key_overrides[i];
        ko->enabled        = &false_const;
    }
};

void user_enable_word_del_override(void) {
    if (user_config.is_macos) { // If MacOS
        user_switch_override(&w_del_mac_override, true);
        user_switch_override(&w_del_win_override, false);
    } else if (user_config.is_windows) { // If Windows
        user_switch_override(&w_del_mac_override, false);
        user_switch_override(&w_del_win_override, true);
    } else if (user_config.is_linux) { // Linux is not implemented yet. Maybe depends on distributions.
        user_disable_word_del_override();
    }
}

void user_disable_word_del_override(void) {
    user_switch_override(&w_del_mac_override, false);
    user_switch_override(&w_del_win_override, false);
}

void user_toggle_word_del_override(bool enable) {
    if (enable) {
        user_enable_word_del_override();
    } else {
        user_disable_word_del_override();
    }
}

void user_dump_override_state(void) {
    tap_code(KC_LNG2);
    register_code(KC_LSFT);
    tap_code16(KC_LBRC);

    if (user_config.is_macos) {
        SEND_STRING(" macos");
    } else if (user_config.is_windows) {
        SEND_STRING(" win");
    } else if (user_config.is_linux) {
        SEND_STRING(" linux");
    } else if (user_config.is_ios) {
        SEND_STRING(" ios");
    } else {
        SEND_STRING(" unknown");
    }
    SEND_STRING(" \\");

    if (key_override_is_enabled()) {
        if (user_config.override_modded_esc) SEND_STRING(" modesc");
        if (user_config.override_enter) SEND_STRING(" ent");
        if (user_config.override_backspace) SEND_STRING(" bksp");
        if (user_config.override_tab) SEND_STRING(" tab");
        if (user_config.override_arrows) SEND_STRING(" arr");
        if (user_config.override_delete) SEND_STRING(" del");
        if (user_config.override_word_dl_apl) SEND_STRING(" wddlapl");
        if (user_config.override_word_dl_lnx) SEND_STRING(" wddllnx");
        if (user_config.override_word_mv_apl) SEND_STRING(" wdmvapl");
        if (user_config.override_word_mv_lnx) SEND_STRING(" wdmvlnx");
        if (user_config.override_ctrl_u) SEND_STRING(" ctlu");
        if (user_config.override_cmd_q) SEND_STRING(" cmdq");
        if (user_config.spc_tap) SEND_STRING(" spctap");

        SEND_STRING(" \\");

        if (user_config.override_home) SEND_STRING(" home");
        if (user_config.override_end) SEND_STRING(" end");

        SEND_STRING(" \\");

        if (user_config.override_linux_cmd) SEND_STRING(" lnxcmd");

        if (user_config.is_jis_mode) SEND_STRING(" jis");

        if (user_config.fnc_tap) SEND_STRING(" fnctap");
    } else {
        SEND_STRING(" override disabled");
    }

    tap_code(KC_SPC);
    tap_code16(KC_RBRC);
    unregister_code(KC_LSFT);
}

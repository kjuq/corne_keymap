#include QMK_KEYBOARD_H
#include "os_detection.h"

#define HSV_ADJUST HSV_YELLOW

// user defined keycodes
#define CMD_SPC LGUI_T(KC_SPC)
#define ALT_SPC RALT_T(KC_SPC)

#define LOWER MO(_LOWER)
#define RAISE LM(_RAISE, MOD_MASK_SHIFT)

#define FNCTN OSL(_FNCTN)
#define MODS OSL(_MODS)
#define ORS OSL(_ORS)

#define SC_TAB (QK_LCTL | QK_RSFT | KC_TAB)
#define SA_TAB (QK_RALT | QK_RSFT | KC_TAB)

typedef union {
	uint32_t raw;
	struct {
		bool override_tab : 1;
		bool override_enter : 1;
		bool override_backspace : 1;
		bool override_delete : 1;
		bool override_arrows : 1;
		bool override_home : 1;
		bool override_end : 1;
		bool override_ctrl_k : 1;
		bool override_ctrl_o : 1;
		bool override_ctrl_u : 1;
		bool override_word_mv : 1;
		bool override_word_dl : 1;
		bool override_cmd_q : 1;
		bool override_modded_esc : 1;
		bool override_linux_cmd : 1;
		bool override_linux_special_keys : 1;
		bool is_jis_mode : 1;
		bool is_auto_detect_os : 1;
		bool is_macos : 1;
		bool is_windows : 1;
		bool is_linux : 1;
		bool is_ios : 1;
		bool spc_tap : 1;
	};
} user_config_t;
user_config_t user_config;

enum planck_keycodes {
	COLEMAK = SAFE_RANGE,
	ADJUST,
	ADJUST2,
	MOD_CAG,
	MOUSE,
	EXT_LYR,
	KO_TB,
	KO_EN,
	KO_BS,
	KO_DL,
	KO_AR,
	KO_HM,
	KO_ED,
	KO_CTLK,
	KO_WD,
	KO_WDDL,
	KO_CTLU,
	KO_CMDV,
	KO_CMDD,
	KO_CMDQ,
	KO_MTAB,
	KO_LXCM,
	KO_LSPK,
	KO_JIS,
	KO_PRNT,
	MT_SPC,
	HOLDLST,
	DTCT_OS,
	CYCL_OS,
	RGB_RDP,
};

enum planck_layers {
	_COLEMAK,
	_SPC_TAP,
	_LOWER,
	_RAISE,
	_FNCTN,
	_MODS,
	_ORS,
	_ADJUST,
	_ADJUST2,
	_MOUSE,
};

static bool false_const = false;

// variables for key_overrides
// JIS: https://github.com/koktoh/jtu_custom_keycodes
// HACK: I have no idea why MOD_MASK_SHIFT is needed for @, ^, and :.

key_override_t jis_s_2_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_LBRC);    // KC_AT @
key_override_t jis_s_6_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_EQL);     // KC_CIRC ^
key_override_t jis_s_7_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_CIRC);    // KC_AMPR &
key_override_t jis_s_8_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_DQUO);    // KC_ASTR *
key_override_t jis_s_9_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_ASTR);    // KC_LPRN (
key_override_t jis_s_0_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, LSFT(KC_9)); // KC_RPRN )

key_override_t jis_s_mins_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, LSFT(KC_INT1)); // KC_UNDS _
key_override_t jis_s_eql_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_COLN);         // KC_PLUS +
key_override_t jis_s_lbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RCBR);       // KC_LCBR {
key_override_t jis_s_rbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, LSFT(KC_NUHS)); // KC_RCBR }
key_override_t jis_s_bsls_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, LSFT(KC_INT3)); // KC_PIPE |
key_override_t jis_s_scln_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT);       // KC_COLN :
key_override_t jis_s_quot_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_AT);         // KC_DQUO "
key_override_t jis_s_grv_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_PLUS);         // KC_TILD ~

key_override_t jis_at_override = ko_make_basic(MOD_MASK_SHIFT, KC_AT, KC_LBRC);    // S(KC_2),KC_AT @
key_override_t jis_circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_CIRC, KC_EQL); // S(KC_6) KC_CIRC ^
key_override_t jis_ampr_override = ko_make_basic(0, KC_AMPR, KC_CIRC);             // S(KC_7) KC_AMPR &
key_override_t jis_astr_override = ko_make_basic(0, KC_ASTR, KC_DQUO);             // S(KC_8) KC_ASTR *
key_override_t jis_lprn_override = ko_make_basic(0, KC_LPRN, KC_ASTR);             // S(KC_9) KC_LPRN (
key_override_t jis_rprn_override = ko_make_basic(0, KC_RPRN, LSFT(KC_9));          // S(KC_0) KC_RPRN )
key_override_t jis_unds_override = ko_make_basic(0, KC_UNDS, LSFT(KC_INT1));       // S(KC_MINUS) KC_UNDS _
key_override_t jis_plus_override = ko_make_basic(0, KC_PLUS, KC_COLN);             // S(KC_EQUAL) KC_PLUS +
key_override_t jis_lbrc_override = ko_make_basic(0, KC_LBRC, KC_RBRC);
key_override_t jis_lcbr_override = ko_make_basic(0, KC_LCBR, KC_RCBR); // S(KC_LBRC) KC_LCBR {
key_override_t jis_rbrc_override = ko_make_basic(0, KC_RBRC, KC_NUHS);
key_override_t jis_rcbr_override = ko_make_basic(0, KC_RCBR, LSFT(KC_NUHS)); // S(KC_RBRC) KC_RCBR }
key_override_t jis_bsls_override = ko_make_basic(0, KC_BSLS, KC_INT3);
key_override_t jis_pipe_override = ko_make_basic(0, KC_PIPE, LSFT(KC_INT3));        // S(KC_BSLS) KC_PIPE |
key_override_t jis_coln_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_QUOT); // S(KC_SCLN) KC_COLN :
key_override_t jis_quot_override = ko_make_basic(0, KC_QUOT, KC_AMPR);
key_override_t jis_dquo_override = ko_make_basic(0, KC_DQUO, KC_AT); // S(KC_QUOT) KC_DQUO "
key_override_t jis_grv_override = ko_make_basic(0, KC_GRV, KC_LCBR);
key_override_t jis_tild_override = ko_make_basic(0, KC_TILD, KC_PLUS); // S(KC_GRV) KC_TILD ~
key_override_t jis_eql_override = ko_make_basic(0, KC_EQL, KC_UNDS);

key_override_t right_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_F, KC_RIGHT);
key_override_t left_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_B, KC_LEFT);
key_override_t up_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_P, KC_UP);
key_override_t down_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_N, KC_DOWN);
key_override_t home_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_A, KC_HOME);
key_override_t end_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_E, KC_END);
key_override_t enter_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_M, KC_ENT);
key_override_t tab_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_I, KC_TAB);
key_override_t bs_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_H, KC_BSPC);
key_override_t del_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_D, KC_DEL);
key_override_t w_fwd_mac_override = ko_make_basic(MOD_BIT(KC_RALT), KC_F, RALT(KC_RGHT));
key_override_t w_bck_mac_override = ko_make_basic(MOD_BIT(KC_RALT), KC_B, RALT(KC_LEFT));
key_override_t w_fwd_win_override = ko_make_basic(MOD_BIT(KC_RALT), KC_F, RCTL(KC_RGHT));
key_override_t w_bck_win_override = ko_make_basic(MOD_BIT(KC_RALT), KC_B, RCTL(KC_LEFT));
key_override_t w_del_mac_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_W, RALT(KC_BSPC));
key_override_t w_del_win_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_W, LCTL(KC_BSPC));
key_override_t cmd_q_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_Q, LGUI(KC_GRV)); // overridden by linux cmd
key_override_t ctrl_tab_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_ESC, LCTL(KC_TAB));
key_override_t alt_tab_override = ko_make_basic(MOD_BIT(KC_RALT), KC_ESC, RALT(KC_TAB));
key_override_t cmd_tab_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_ESC, LGUI(KC_TAB));
key_override_t shift_tab_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_ESC, LSFT(KC_TAB));
key_override_t ctrl_u_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_U, LSFT(RCTL(KC_BSPC)));
key_override_t ctrl_k_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_K, LSFT(RCTL(KC_DEL)));

key_override_t linux_a_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_A, LCTL(KC_A));
key_override_t linux_b_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_B, LCTL(KC_B));
key_override_t linux_c_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_C, LCTL(KC_C));
key_override_t linux_d_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_D, LCTL(KC_D));
key_override_t linux_e_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_E, LCTL(KC_E));
key_override_t linux_f_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_F, LCTL(KC_F));
key_override_t linux_g_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_G, LCTL(KC_G));
key_override_t linux_h_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_H, LCTL(KC_H));
key_override_t linux_i_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_I, LCTL(KC_I));
key_override_t linux_j_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_J, LCTL(KC_J));
key_override_t linux_k_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_K, LCTL(KC_K));
key_override_t linux_l_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_L, LCTL(KC_L));
key_override_t linux_m_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_M, LCTL(KC_M));
key_override_t linux_n_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_N, LCTL(KC_N));
key_override_t linux_o_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_O, LCTL(KC_O));
key_override_t linux_p_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_P, LCTL(KC_P));
key_override_t linux_q_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_Q, LCTL(KC_Q));
key_override_t linux_r_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_R, LCTL(KC_R));
key_override_t linux_s_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_S, LCTL(KC_S));
key_override_t linux_t_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_T, LCTL(KC_T));
key_override_t linux_u_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_U, LCTL(KC_U));
key_override_t linux_v_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_V, LCTL(KC_V));
key_override_t linux_w_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_W, LCTL(KC_W));
key_override_t linux_x_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_X, LCTL(KC_X));
key_override_t linux_y_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_Y, LCTL(KC_Y));
key_override_t linux_z_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_Z, LCTL(KC_Z));
key_override_t linux_com_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_COMM, LCTL(KC_COMM));
key_override_t linux_dot_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_DOT, LCTL(KC_DOT));

const key_override_t **key_overrides = (const key_override_t *[]){
    &linux_a_override,
    &linux_b_override,
    &linux_c_override,
    &linux_d_override,
    &linux_e_override,
    &linux_f_override,
    &linux_g_override,
    &linux_h_override,
    &linux_i_override,
    &linux_j_override,
    &linux_k_override,
    &linux_l_override,
    &linux_m_override,
    &linux_n_override,
    &linux_o_override,
    &linux_p_override,
    &linux_q_override,
    &linux_r_override,
    &linux_s_override,
    &linux_t_override,
    &linux_u_override,
    &linux_v_override,
    &linux_w_override,
    &linux_x_override,
    &linux_y_override,
    &linux_z_override,
    &linux_com_override,
    &linux_dot_override,

    &enter_key_override,
    &tab_key_override,
    &right_key_override,
    &left_key_override,
    &up_key_override,
    &down_key_override,
    &bs_key_override,
    &del_key_override,
    &home_key_override,
    &end_key_override,
    &ctrl_u_key_override,
    &ctrl_k_key_override,
    &cmd_q_override,
    &w_fwd_mac_override,
    &w_bck_mac_override,
    &w_del_mac_override,
    &w_fwd_win_override,
    &w_bck_win_override,
    &w_del_win_override,
    &ctrl_tab_override,
    &alt_tab_override,
    &cmd_tab_override,
    &shift_tab_override,

    &jis_s_2_override,
    &jis_s_6_override,
    &jis_s_7_override,
    &jis_s_8_override,
    &jis_s_9_override,
    &jis_s_0_override,
    &jis_s_mins_override,
    &jis_s_eql_override,
    &jis_s_lbrc_override,
    &jis_s_rbrc_override,
    &jis_s_bsls_override,
    &jis_s_scln_override,
    &jis_s_quot_override,
    &jis_s_grv_override,

    &jis_at_override,
    &jis_circ_override,
    &jis_ampr_override,
    &jis_astr_override,
    &jis_lprn_override,
    &jis_rprn_override,
    &jis_unds_override,
    &jis_plus_override,
    &jis_lbrc_override,
    &jis_lcbr_override,
    &jis_rbrc_override,
    &jis_rcbr_override,
    &jis_bsls_override,
    &jis_pipe_override,
    &jis_coln_override,
    &jis_quot_override,
    &jis_dquo_override,
    &jis_grv_override,
    &jis_tild_override,
    &jis_eql_override,

    NULL,
};

// #include "process_key_override.h"

// Prototype declaration
void kjuq_switch_jis(bool);
void kjuq_switch_linux_cmd(bool);
void kjuq_enable_all_overrides(void);
void kjuq_disable_all_overrides(void);
void kjuq_enable_word_del_override(void);
void kjuq_disable_word_del_override(void);
void kjuq_toggle_word_del_override(bool);
void kjuq_dump_override_state(void);
void kjuq_reload_overrides(void);

// ------
void kjuq_enter_layer(uint8_t, uint8_t, uint8_t, uint8_t);
void kjuq_exit_layer(void);
bool kjuq_is_macos(void);
bool kjuq_is_ios(void);
bool kjuq_is_linux(void);
bool kjuq_is_windows(void);
void kjuq_switch_override(key_override_t *, bool);
void kjuq_switch_linux_special_keys(bool);
// ------

void kjuq_reload_overrides() {
	kjuq_enable_all_overrides();

	if (!user_config.override_tab) {
		kjuq_switch_override(&tab_key_override, false);
	}
	if (!user_config.override_enter) {
		kjuq_switch_override(&enter_key_override, false);
	}
	if (!user_config.override_backspace) {
		kjuq_switch_override(&bs_key_override, false);
	}
	if (!user_config.override_delete) {
		kjuq_switch_override(&del_key_override, false);
	}
	if (!user_config.override_arrows) {
		kjuq_switch_override(&up_key_override, false);
		kjuq_switch_override(&down_key_override, false);
		kjuq_switch_override(&right_key_override, false);
		kjuq_switch_override(&left_key_override, false);
	}

	if (!user_config.override_modded_esc) {
		kjuq_switch_override(&ctrl_tab_override, false);
		kjuq_switch_override(&alt_tab_override, false);
		kjuq_switch_override(&cmd_tab_override, false);
		kjuq_switch_override(&shift_tab_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_home) {
		kjuq_switch_override(&home_key_override, false);
	}
	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_end) {
		kjuq_switch_override(&end_key_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios()) {
		ctrl_u_key_override.replacement = LCMD(KC_BSPC);
	} else if (kjuq_is_linux() || kjuq_is_windows()) {
		ctrl_u_key_override.replacement = LSFT(RCTL(KC_BSPC));
	}
	if (!user_config.override_ctrl_u) {
		kjuq_switch_override(&ctrl_u_key_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_ctrl_k) {
		kjuq_switch_override(&ctrl_k_key_override, false);
	}

	if (kjuq_is_linux() || kjuq_is_windows() || !user_config.override_cmd_q) {
		kjuq_switch_override(&cmd_q_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_word_mv) {
		kjuq_switch_override(&w_fwd_win_override, false);
		kjuq_switch_override(&w_bck_win_override, false);
	}

	if (kjuq_is_linux() || kjuq_is_windows() || !user_config.override_word_mv) {
		kjuq_switch_override(&w_fwd_mac_override, false);
		kjuq_switch_override(&w_bck_mac_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_word_dl) {
		kjuq_switch_override(&w_del_win_override, false);
	}

	if (kjuq_is_linux() || kjuq_is_windows() || !user_config.override_word_dl) {
		kjuq_switch_override(&w_del_mac_override, false);
	}

	if (kjuq_is_macos() || kjuq_is_ios() || !user_config.override_linux_cmd) {
		kjuq_switch_linux_cmd(false);
	}

	kjuq_switch_linux_special_keys(user_config.override_linux_special_keys);

	if (!user_config.is_jis_mode) {
		kjuq_switch_jis(false);
	}
}

void kjuq_reload_user_eeprom(void) {
	user_config.raw = eeconfig_read_user();
	kjuq_reload_overrides();
	if (user_config.spc_tap) {
		default_layer_or((layer_state_t)1 << _SPC_TAP);
	} else {
		default_layer_or((layer_state_t)1 << _SPC_TAP);
		default_layer_xor((layer_state_t)1 << _SPC_TAP);
	}
};

void kjuq_enter_layer(uint8_t layer, uint8_t hue, uint8_t sat, uint8_t val) {
	layer_move(layer);
	rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_PINWHEEL_VAL);
	rgb_matrix_sethsv_noeeprom(hue, sat, val);
	return;
}

void kjuq_exit_layer(void) {
	layer_clear();
	rgblight_reload_from_eeprom();
	return;
};

bool kjuq_is_macos(void) {
	if (user_config.is_auto_detect_os) {
		return (detected_host_os() == OS_MACOS);
	} else {
		return (user_config.is_macos);
	}
}

bool kjuq_is_ios(void) {
	if (user_config.is_auto_detect_os) {
		return (detected_host_os() == OS_IOS);
	} else {
		return (user_config.is_ios);
	}
}

bool kjuq_is_linux(void) {
	if (user_config.is_auto_detect_os) {
		return (detected_host_os() == OS_LINUX);
	} else {
		return (user_config.is_linux);
	}
}

bool kjuq_is_windows(void) {
	if (user_config.is_auto_detect_os) {
		return (detected_host_os() == OS_WINDOWS);
	} else {
		return (user_config.is_windows);
	}
}

void kjuq_switch_override(key_override_t *override, bool enabled) { override->enabled = enabled ? NULL : &false_const; }

void kjuq_switch_jis(bool enabled) {
	kjuq_switch_override(&jis_s_2_override, enabled);
	kjuq_switch_override(&jis_s_6_override, enabled);
	kjuq_switch_override(&jis_s_7_override, enabled);
	kjuq_switch_override(&jis_s_8_override, enabled);
	kjuq_switch_override(&jis_s_9_override, enabled);
	kjuq_switch_override(&jis_s_0_override, enabled);
	kjuq_switch_override(&jis_s_mins_override, enabled);
	kjuq_switch_override(&jis_s_eql_override, enabled);
	kjuq_switch_override(&jis_s_lbrc_override, enabled);
	kjuq_switch_override(&jis_s_rbrc_override, enabled);
	kjuq_switch_override(&jis_s_bsls_override, enabled);
	kjuq_switch_override(&jis_s_scln_override, enabled);
	kjuq_switch_override(&jis_s_quot_override, enabled);
	kjuq_switch_override(&jis_s_grv_override, enabled);

	kjuq_switch_override(&jis_at_override, enabled);
	kjuq_switch_override(&jis_circ_override, enabled);
	kjuq_switch_override(&jis_ampr_override, enabled);
	kjuq_switch_override(&jis_astr_override, enabled);
	kjuq_switch_override(&jis_lprn_override, enabled);
	kjuq_switch_override(&jis_rprn_override, enabled);
	kjuq_switch_override(&jis_unds_override, enabled);
	kjuq_switch_override(&jis_plus_override, enabled);
	kjuq_switch_override(&jis_lbrc_override, enabled);
	kjuq_switch_override(&jis_lcbr_override, enabled);
	kjuq_switch_override(&jis_rbrc_override, enabled);
	kjuq_switch_override(&jis_rcbr_override, enabled);
	kjuq_switch_override(&jis_bsls_override, enabled);
	kjuq_switch_override(&jis_pipe_override, enabled);
	kjuq_switch_override(&jis_coln_override, enabled);
	kjuq_switch_override(&jis_quot_override, enabled);
	kjuq_switch_override(&jis_dquo_override, enabled);
	kjuq_switch_override(&jis_grv_override, enabled);
	kjuq_switch_override(&jis_tild_override, enabled);
	kjuq_switch_override(&jis_eql_override, enabled);
}

void kjuq_switch_linux_special_keys(bool enable) {
	if (enable) {
		linux_c_override.replacement = KC_COPY;
		linux_v_override.replacement = KC_PASTE;
		linux_x_override.replacement = KC_CUT;
	} else {
		linux_c_override.replacement = LCTL(KC_C);
		linux_v_override.replacement = LCTL(KC_V);
		linux_x_override.replacement = LCTL(KC_X);
	}
}

void kjuq_switch_linux_cmd(bool enable) {
	kjuq_switch_override(&linux_a_override, enable);
	kjuq_switch_override(&linux_b_override, enable);
	kjuq_switch_override(&linux_c_override, enable);
	kjuq_switch_override(&linux_d_override, enable);
	kjuq_switch_override(&linux_e_override, enable);
	kjuq_switch_override(&linux_f_override, enable);
	kjuq_switch_override(&linux_g_override, enable);
	kjuq_switch_override(&linux_h_override, enable);
	kjuq_switch_override(&linux_i_override, enable);
	kjuq_switch_override(&linux_j_override, enable);
	kjuq_switch_override(&linux_k_override, enable);
	kjuq_switch_override(&linux_l_override, enable);
	kjuq_switch_override(&linux_m_override, enable);
	kjuq_switch_override(&linux_n_override, enable);
	kjuq_switch_override(&linux_o_override, enable);
	kjuq_switch_override(&linux_p_override, enable);
	kjuq_switch_override(&linux_q_override, enable);
	kjuq_switch_override(&linux_r_override, enable);
	kjuq_switch_override(&linux_s_override, enable);
	kjuq_switch_override(&linux_t_override, enable);
	kjuq_switch_override(&linux_u_override, enable);
	kjuq_switch_override(&linux_v_override, enable);
	kjuq_switch_override(&linux_w_override, enable);
	kjuq_switch_override(&linux_x_override, enable);
	kjuq_switch_override(&linux_y_override, enable);
	kjuq_switch_override(&linux_z_override, enable);
	kjuq_switch_override(&linux_com_override, enable);
	kjuq_switch_override(&linux_dot_override, enable);
}

void kjuq_enable_all_overrides(void) {
	for (int i = 0; key_overrides[i] != NULL; i++) {
		key_override_t *ko = (key_override_t *)key_overrides[i];
		ko->enabled = NULL;
	}
};

void kjuq_disable_all_overrides(void) {
	for (int i = 0; key_overrides[i] != NULL; i++) {
		key_override_t *ko = (key_override_t *)key_overrides[i];
		ko->enabled = &false_const;
	}
};

void kjuq_enable_word_del_override(void) {
	if (user_config.is_macos) { // If MacOS
		kjuq_switch_override(&w_del_mac_override, true);
		kjuq_switch_override(&w_del_win_override, false);
	} else if (user_config.is_windows) { // If Windows
		kjuq_switch_override(&w_del_mac_override, false);
		kjuq_switch_override(&w_del_win_override, true);
	} else if (user_config.is_linux) { // Linux is not implemented yet. Maybe depends on distributions.
		kjuq_disable_word_del_override();
	}
}

void kjuq_disable_word_del_override(void) {
	kjuq_switch_override(&w_del_mac_override, false);
	kjuq_switch_override(&w_del_win_override, false);
}

void kjuq_toggle_word_del_override(bool enable) {
	if (enable) {
		kjuq_enable_word_del_override();
	} else {
		kjuq_disable_word_del_override();
	}
}

void kjuq_dump_override_state(void) {
	tap_code(KC_LNG2); // disable Japanese input
	tap_code(KC_SLSH);
	register_code(KC_LSFT);

	if (!user_config.is_auto_detect_os) {
		SEND_STRING(" manually");
	} else if (kjuq_is_macos()) {
		SEND_STRING(" macos");
	} else if (kjuq_is_windows()) {
		SEND_STRING(" win");
	} else if (kjuq_is_linux()) {
		SEND_STRING(" linux");
	} else if (kjuq_is_ios()) {
		SEND_STRING(" ios");
	} else {
		SEND_STRING(" unknown");
	}
	SEND_STRING(" detected 1"); // 1 is '1'

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
	SEND_STRING(" 1");

	if (key_override_is_enabled()) {
		if (user_config.override_modded_esc) {
			SEND_STRING(" modesc");
		}
		if (user_config.override_enter) {
			SEND_STRING(" ent");
		}
		if (user_config.override_backspace) {
			SEND_STRING(" bksp");
		}
		if (user_config.override_tab) {
			SEND_STRING(" tab");
		}
		if (user_config.override_arrows) {
			SEND_STRING(" arr");
		}
		if (user_config.override_delete) {
			SEND_STRING(" del");
		}
		if (user_config.spc_tap) {
			SEND_STRING(" spctap");
		}

		SEND_STRING(" 1");

		if (user_config.override_home) {
			SEND_STRING(" home");
		}
		if (user_config.override_end) {
			SEND_STRING(" end");
		}
		if (user_config.override_ctrl_u) {
			SEND_STRING(" ctlu");
		}
		if (user_config.override_ctrl_k) {
			SEND_STRING(" ctlk");
		}
		if (user_config.override_cmd_q) {
			SEND_STRING(" cmdq");
		}
		if (user_config.override_word_dl) {
			SEND_STRING(" wddl");
		}
		if (user_config.override_word_mv) {
			SEND_STRING(" wdmv");
		}

		SEND_STRING(" 1");

		if (user_config.is_auto_detect_os) {
			SEND_STRING(" detectos");
		}
		if (user_config.override_linux_cmd) {
			SEND_STRING(" lnxcmd");
		}
		if (user_config.override_linux_special_keys) {
			SEND_STRING(" lnxspclks");
		}
		if (user_config.is_jis_mode) {
			SEND_STRING(" jis");
		}
	} else {
		SEND_STRING(" override disabled");
	}

	unregister_code(KC_LSFT);
	tap_code(KC_SPC);
	tap_code(KC_SLSH);
}

// clang-format off
/* *INDENT-OFF* */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT_split_3x5_3_ex2( // {{{
		KC_ESC,  KC_W,    KC_F,    KC_P,    KC_B,    KC_PGUP,         KC_TAB,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_Q,
		KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_PGDN,         KC_ENT,  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
		KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                              KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
		                           LOWER,   KC_LCTL, KC_SPC,          KC_SPC,  KC_RSFT, RAISE
	), // }}}

	[_SPC_TAP] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, CMD_SPC,         ALT_SPC, _______, _______
	), // }}}

	[_LOWER] = LAYOUT_split_3x5_3_ex2( // {{{
		SC_TAB,  KC_MINS, KC_EQL,  KC_GRV,  XXXXXXX, XXXXXXX,         XXXXXXX, KC_COMM, KC_7,    KC_8,    KC_9,    KC_BSPC,
		MOD_CAG, KC_SLSH, KC_LBRC, KC_RBRC, KC_QUOT, XXXXXXX,         XXXXXXX, KC_0,    KC_4,    KC_5,    KC_6,    FNCTN,
		KC_RCTL, KC_COMM, KC_DOT,  KC_SCLN, KC_BSLS,                           KC_DOT,  KC_1,    KC_2,    KC_3,    KC_LSFT,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_RAISE] = LAYOUT_split_3x5_3_ex2( // {{{
		SA_TAB,  KC_UNDS, KC_PLUS, KC_TILD, XXXXXXX, XXXXXXX,         XXXXXXX, KC_LABK, KC_AMPR, KC_ASTR, KC_LPRN, KC_BSPC,
		XXXXXXX, KC_QUES, KC_LCBR, KC_RCBR, KC_DQUO, XXXXXXX,         XXXXXXX, KC_RPRN, KC_DLR,  KC_PERC, KC_CIRC, MOUSE,
		KC_RCMD, KC_LABK, KC_RABK, KC_COLN, KC_PIPE,                           KC_RABK, KC_EXLM, KC_AT,   KC_HASH, KC_LALT,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_FNCTN] = LAYOUT_split_3x5_3_ex2( // {{{
		XXXXXXX, KC_BRIU, KC_VOLU, KC_PGUP, KC_SCRL, XXXXXXX,         XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   HOLDLST,
		ADJUST,  KC_BRID, KC_VOLD, KC_PGDN, KC_INS,  XXXXXXX,         XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   ORS,
		KC_CAPS, KC_MPLY, KC_MUTE, KC_PSCR, KC_PAUS,                           KC_F10,  KC_F1,   KC_F2,   KC_F3,   MODS,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_MODS] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_ORS] = LAYOUT_split_3x5_3_ex2( // {{{
		XXXXXXX, XXXXXXX, KC_RGHT, KC_UP,   KC_LEFT, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_BSPC, KC_DOWN, KC_END,  KC_TAB,  XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX,                           XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_ADJUST] = LAYOUT_split_3x5_3_ex2( // {{{
		EXT_LYR, KO_WDDL, KO_WD,   XXXXXXX, KO_AR,   XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, KO_CTLU, XXXXXXX, KO_CMDQ,
		KO_HM,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KO_BS,   XXXXXXX, KO_ED,   KO_TB,   ADJUST2,
		XXXXXXX, XXXXXXX, XXXXXXX, KO_DL,   KO_LSPK,                           KO_CTLK, KO_EN,   XXXXXXX, KO_JIS,  KO_PRNT,
			                       KO_MTAB, XXXXXXX, KO_LXCM,         MT_SPC,  XXXXXXX, XXXXXXX
	), // }}}

	[_ADJUST2] = LAYOUT_split_3x5_3_ex2( // {{{
		EXT_LYR, QK_BOOT, DB_TOGG, RGB_TOG, XXXXXXX, XXXXXXX,         XXXXXXX, RGB_SPI, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_RDP,
		CYCL_OS, DTCT_OS, KO_TOGG, EE_CLR,  COLEMAK,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		                           XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_RSFT, XXXXXXX
	), // }}}

	[_MOUSE] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX,
		XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, XXXXXXX,         XXXXXXX, XXXXXXX, KC_BTN1, KC_ACL1, KC_ACL1, KC_LSFT,
		XXXXXXX, KC_WH_L, XXXXXXX, KC_WH_R, KC_BTN4,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

};
// clang-format on
/* *INDENT-ON* */

static uint16_t last_keycode;
static int mouse_acl_pressed = 0;

void oneshot_layer_changed_user(uint8_t layer) {
	if (layer == _MODS || layer == _ORS) {
		kjuq_disable_all_overrides();
	} else { // Exit _MODS and _ORS
		kjuq_reload_user_eeprom();
	}
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case CMD_SPC:
	case ALT_SPC:
		return (125);

	default:
		return (TAPPING_TERM);
	}
	(void)record; // suppress unused parameter warning
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case LOWER:
	case RAISE:
		// Immediately select the hold action when another key is pressed.
		return (true);

	default:
		// Do not select the hold action when another key is pressed.
		return (false);
	}
	(void)record; // suppress unused parameter warning
}

void keyboard_post_init_user(void) {
	// wait_ms(250); // wait to detect OS properly
	kjuq_reload_user_eeprom();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	// Layers
	case COLEMAK:
		if (record->event.pressed) {
			set_single_persistent_default_layer(_COLEMAK);
		}
		return (false);

	case ADJUST:
		if (record->event.pressed) {
			if (IS_LAYER_OFF(_ADJUST)) {
				kjuq_enter_layer(_ADJUST, HSV_ADJUST);
			} else {
				kjuq_exit_layer();
			}
		}
		return (false);

	case ADJUST2:
		if (record->event.pressed) {
			if (IS_LAYER_OFF(_ADJUST2)) {
				layer_move(_ADJUST2);
				rgblight_reload_from_eeprom();
			} else {
				kjuq_exit_layer();
			}
		}
		return (false);

	case RAISE:
		if (record->event.pressed) {
			// do nothing special
		} else {
			layer_off(_MOUSE);
		}
		return (true);

	case MOD_CAG:
		if (record->event.pressed) {
			register_code(KC_RCTL);
			register_code(KC_LALT);
			register_code(KC_RGUI);
		} else {
			unregister_code(KC_RCTL);
			unregister_code(KC_LALT);
			unregister_code(KC_RGUI);
		}
		return (false);

	// MOUSE
	case MOUSE:
		if (record->event.pressed) {
			layer_on(_MOUSE);
			unregister_code(KC_LSFT);
		}
		return (false);

	case KC_ACL1:
		if (record->event.pressed) {
			if (mouse_acl_pressed == 1) {
				register_code(KC_ACL0);
			} else {
				register_code(KC_ACL1);
			}
			mouse_acl_pressed++;
		} else {
			if (mouse_acl_pressed == 2) {
				unregister_code(KC_ACL0);
				register_code(KC_ACL1);
			} else {
				unregister_code(KC_ACL1);
			}
			mouse_acl_pressed--;
		}
		return (false);

	// Extra keys
	case EXT_LYR:
		if (record->event.pressed) {
			kjuq_exit_layer();
		}
		return (false);

	case HOLDLST:
		if (record->event.pressed) {
			register_code16(last_keycode);
		}
		return (false);

	// Key override
	case KO_TB:
		if (record->event.pressed) {
			user_config.override_tab = !user_config.override_tab;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_EN:
		if (record->event.pressed) {
			user_config.override_enter = !user_config.override_enter;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_BS:
		if (record->event.pressed) {
			user_config.override_backspace = !user_config.override_backspace;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_DL:
		if (record->event.pressed) {
			user_config.override_delete = !user_config.override_delete;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_AR:
		if (record->event.pressed) {
			user_config.override_arrows = !user_config.override_arrows;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_HM:
		if (record->event.pressed) {
			user_config.override_home = !user_config.override_home;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_ED:
		if (record->event.pressed) {
			user_config.override_end = !user_config.override_end;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_CTLU:
		if (record->event.pressed) {
			user_config.override_ctrl_u = !user_config.override_ctrl_u;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_CTLK:
		if (record->event.pressed) {
			user_config.override_ctrl_k = !user_config.override_ctrl_k;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_CMDQ:
		if (record->event.pressed) {
			user_config.override_cmd_q = !user_config.override_cmd_q;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_MTAB:
		if (record->event.pressed) {
			user_config.override_modded_esc = !user_config.override_modded_esc;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_WD:
		if (record->event.pressed) {
			user_config.override_word_mv = !user_config.override_word_mv;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_WDDL:
		if (record->event.pressed) {
			user_config.override_word_dl = !user_config.override_word_dl;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_LXCM:
		if (record->event.pressed) {
			user_config.override_linux_cmd = !user_config.override_linux_cmd;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_LSPK:
		if (record->event.pressed) {
			user_config.override_linux_special_keys = !user_config.override_linux_special_keys;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_JIS:
		if (record->event.pressed) {
			user_config.is_jis_mode = !user_config.is_jis_mode;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case DTCT_OS:
		if (record->event.pressed) {
			user_config.is_auto_detect_os = !user_config.is_auto_detect_os;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case CYCL_OS:
		if (record->event.pressed) {
			if (user_config.is_linux) {
				user_config.is_linux = 0;
				user_config.is_macos = 1;
				user_config.is_windows = 0;
				user_config.is_ios = 0;
			} else if (user_config.is_macos) {
				user_config.is_linux = 0;
				user_config.is_macos = 0;
				user_config.is_windows = 1;
				user_config.is_ios = 0;
			} else if (user_config.is_windows) {
				user_config.is_linux = 0;
				user_config.is_macos = 0;
				user_config.is_windows = 0;
				user_config.is_ios = 1;
			} else {
				user_config.is_linux = 1;
				user_config.is_macos = 0;
				user_config.is_windows = 0;
				user_config.is_ios = 0;
			}
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case KO_PRNT:
		if (record->event.pressed) {
			kjuq_dump_override_state();
		}
		return (false);

	// Hold tap
	case MT_SPC:
		if (record->event.pressed) {
			user_config.spc_tap = !user_config.spc_tap;
			eeconfig_update_user(user_config.raw);
			kjuq_reload_user_eeprom();
		}
		return (false);

	case RGB_RDP:
		if (record->event.pressed) {
			rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
		}

	default:
		last_keycode = get_last_keycode();
	}

	return (true);
}

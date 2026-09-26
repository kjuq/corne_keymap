#include QMK_KEYBOARD_H
#include "overrides.h"
#include "os_detection.h"

typedef union {
	uint32_t raw;
	struct {
		bool is_jis_mode : 1;
		bool is_auto_detect_os : 1;
		bool is_macos : 1;
		bool is_windows : 1;
		bool is_linux : 1;
		bool is_ios : 1;
		bool override_enabled : 1;
		bool gui_tap : 1;
		bool alt_tap : 1;
		bool left_csg : 1;
		bool pure_gc : 1;
		bool pure_alt : 1;
		bool cmd_like_ctrl : 1;
		bool override_tab : 1;
		bool override_enter : 1;
		bool override_backspace : 1;
		bool override_delete : 1;
		bool override_arrows : 1;
		bool override_home : 1;
		bool override_end : 1;
		bool override_ctrl_k : 1;
		bool override_ctrl_u : 1;
		bool override_word_mv : 1;
		bool override_word_dl : 1;
		bool override_modded_esc : 1;
		bool override_cut : 1;
		bool override_copy : 1;
		bool override_paste : 1;
	};
} user_config_t;

static user_config_t user_config;
static bool false_const = false;

// JIS: https://github.com/koktoh/jtu_custom_keycodes
// HACK: I have no idea why MOD_MASK_SHIFT is needed for @, ^, and :.
key_override_t jis_s_2_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_LBRC);    // KC_AT @
key_override_t jis_s_6_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_EQL);     // KC_CIRC ^
key_override_t jis_s_7_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_CIRC);    // KC_AMPR &
key_override_t jis_s_8_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_DQUO);    // KC_ASTR *
key_override_t jis_s_9_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_ASTR);    // KC_LPRN (
key_override_t jis_s_0_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, RSFT(KC_9)); // KC_RPRN )

key_override_t jis_s_mins_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, RSFT(KC_INT1)); // KC_UNDS _
key_override_t jis_s_eql_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_COLN);         // KC_PLUS +
key_override_t jis_s_lbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RCBR);       // KC_LCBR {
key_override_t jis_s_rbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, RSFT(KC_NUHS)); // KC_RCBR }
key_override_t jis_s_bsls_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, RSFT(KC_INT3)); // KC_PIPE |
key_override_t jis_s_scln_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT);       // KC_COLN :
key_override_t jis_s_quot_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_AT);         // KC_DQUO "
key_override_t jis_s_grv_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_PLUS);         // KC_TILD ~

key_override_t jis_at_override = ko_make_basic(MOD_MASK_SHIFT, KC_AT, KC_LBRC);    // S(KC_2),KC_AT @
key_override_t jis_circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_CIRC, KC_EQL); // S(KC_6) KC_CIRC ^
key_override_t jis_ampr_override = ko_make_basic(0, KC_AMPR, KC_CIRC);             // S(KC_7) KC_AMPR &
key_override_t jis_astr_override = ko_make_basic(0, KC_ASTR, KC_DQUO);             // S(KC_8) KC_ASTR *
key_override_t jis_lprn_override = ko_make_basic(0, KC_LPRN, KC_ASTR);             // S(KC_9) KC_LPRN (
key_override_t jis_rprn_override = ko_make_basic(0, KC_RPRN, RSFT(KC_9));          // S(KC_0) KC_RPRN )
key_override_t jis_unds_override = ko_make_basic(0, KC_UNDS, RSFT(KC_INT1));       // S(KC_MINUS) KC_UNDS _
key_override_t jis_plus_override = ko_make_basic(0, KC_PLUS, KC_COLN);             // S(KC_EQUAL) KC_PLUS +
key_override_t jis_lbrc_override = ko_make_basic(0, KC_LBRC, KC_RBRC);
key_override_t jis_lcbr_override = ko_make_basic(0, KC_LCBR, KC_RCBR); // S(KC_LBRC) KC_LCBR {
key_override_t jis_rbrc_override = ko_make_basic(0, KC_RBRC, KC_NUHS);
key_override_t jis_rcbr_override = ko_make_basic(0, KC_RCBR, RSFT(KC_NUHS)); // S(KC_RBRC) KC_RCBR }
key_override_t jis_bsls_override = ko_make_basic(0, KC_BSLS, KC_INT3);
key_override_t jis_pipe_override = ko_make_basic(0, KC_PIPE, RSFT(KC_INT3));        // S(KC_BSLS) KC_PIPE |
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
key_override_t w_fwd_mac_override = ko_make_basic(MOD_BIT(KC_LALT), KC_F, LALT(KC_RGHT));
key_override_t w_bck_mac_override = ko_make_basic(MOD_BIT(KC_LALT), KC_B, LALT(KC_LEFT));
key_override_t w_fwd_win_override = ko_make_basic(MOD_BIT(KC_LALT), KC_F, RCTL(KC_RGHT));
key_override_t w_bck_win_override = ko_make_basic(MOD_BIT(KC_LALT), KC_B, RCTL(KC_LEFT));
key_override_t w_del_mac_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_W, RALT(KC_BSPC));
key_override_t w_del_win_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_W, LCTL(KC_BSPC));
key_override_t ctrl_tab_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_ESC, LCTL(KC_TAB));
key_override_t alt_tab_override = ko_make_basic(MOD_BIT(KC_LALT), KC_ESC, LALT(KC_TAB));
key_override_t cmd_tab_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_ESC, LGUI(KC_TAB));
key_override_t rctrl_tab_override = ko_make_basic(MOD_BIT(KC_RCTL), KC_ESC, RGUI(KC_TAB));
key_override_t shift_tab_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_ESC, LSFT(KC_TAB));
key_override_t ctrl_u_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_U, RSFT(LCTL(KC_BSPC)));
key_override_t ctrl_k_key_override = ko_make_basic(MOD_BIT(KC_LCTL), KC_K, RSFT(LCTL(KC_DEL)));
key_override_t cut_override = ko_make_basic(MOD_BIT(KC_RCTL), KC_X, KC_CUT);
key_override_t copy_override = ko_make_basic(MOD_BIT(KC_RCTL), KC_C, KC_COPY);
key_override_t paste_override = ko_make_basic(MOD_BIT(KC_RCTL), KC_V, KC_PASTE);

typedef enum {
	KJUQ_OVERRIDE_ENTER,
	KJUQ_OVERRIDE_TAB,
	KJUQ_OVERRIDE_ARROWS,
	KJUQ_OVERRIDE_BACKSPACE,
	KJUQ_OVERRIDE_DELETE,
	KJUQ_OVERRIDE_HOME,
	KJUQ_OVERRIDE_END,
	KJUQ_OVERRIDE_CTRL_U,
	KJUQ_OVERRIDE_CTRL_K,
	KJUQ_OVERRIDE_WORD_MAC,
	KJUQ_OVERRIDE_WORD_WINDOWS,
	KJUQ_OVERRIDE_WORD_DELETE_MAC,
	KJUQ_OVERRIDE_WORD_DELETE_WINDOWS,
	KJUQ_OVERRIDE_MODDED_ESC,
	KJUQ_OVERRIDE_CUT,
	KJUQ_OVERRIDE_COPY,
	KJUQ_OVERRIDE_PASTE,
	KJUQ_OVERRIDE_JIS,
} override_condition_t;

typedef struct {
	key_override_t *override;
	override_condition_t condition;
} override_rule_t;

#define KJUQ_OVERRIDE_RULE(override, condition) {&override, condition},
static const override_rule_t override_rules[] = {KJUQ_OVERRIDE_TABLE(KJUQ_OVERRIDE_RULE)};
#undef KJUQ_OVERRIDE_RULE

static bool kjuq_is_macos(void) {
	return user_config.is_auto_detect_os ? detected_host_os() == OS_MACOS : user_config.is_macos;
}

static bool kjuq_is_ios(void) {
	return user_config.is_auto_detect_os ? detected_host_os() == OS_IOS : user_config.is_ios;
}

static bool kjuq_is_linux(void) {
	return user_config.is_auto_detect_os ? detected_host_os() == OS_LINUX : user_config.is_linux;
}

static bool kjuq_is_windows(void) {
	return user_config.is_auto_detect_os ? detected_host_os() == OS_WINDOWS : user_config.is_windows;
}

static bool kjuq_override_condition_enabled(override_condition_t condition) {
	switch (condition) {
	case KJUQ_OVERRIDE_ENTER:
		return user_config.override_enter;
	case KJUQ_OVERRIDE_TAB:
		return user_config.override_tab;
	case KJUQ_OVERRIDE_ARROWS:
		return user_config.override_arrows;
	case KJUQ_OVERRIDE_BACKSPACE:
		return user_config.override_backspace;
	case KJUQ_OVERRIDE_DELETE:
		return user_config.override_delete;
	case KJUQ_OVERRIDE_HOME:
		return !kjuq_is_macos() && !kjuq_is_ios() && user_config.override_home;
	case KJUQ_OVERRIDE_END:
		return !kjuq_is_macos() && !kjuq_is_ios() && user_config.override_end;
	case KJUQ_OVERRIDE_CTRL_U:
		return user_config.override_ctrl_u;
	case KJUQ_OVERRIDE_CTRL_K:
		return !kjuq_is_macos() && !kjuq_is_ios() && user_config.override_ctrl_k;
	case KJUQ_OVERRIDE_WORD_MAC:
		return !kjuq_is_linux() && !kjuq_is_windows() && user_config.override_word_mv;
	case KJUQ_OVERRIDE_WORD_WINDOWS:
		return !kjuq_is_macos() && !kjuq_is_ios() && user_config.override_word_mv;
	case KJUQ_OVERRIDE_WORD_DELETE_MAC:
		return !kjuq_is_linux() && !kjuq_is_windows() && user_config.override_word_dl;
	case KJUQ_OVERRIDE_WORD_DELETE_WINDOWS:
		return !kjuq_is_macos() && !kjuq_is_ios() && user_config.override_word_dl;
	case KJUQ_OVERRIDE_MODDED_ESC:
		return user_config.override_modded_esc;
	case KJUQ_OVERRIDE_CUT:
		return user_config.override_cut;
	case KJUQ_OVERRIDE_COPY:
		return user_config.override_copy;
	case KJUQ_OVERRIDE_PASTE:
		return user_config.override_paste;
	case KJUQ_OVERRIDE_JIS:
		return user_config.is_jis_mode;
	}

	return false;
}

static void kjuq_switch_override(key_override_t *override, bool enabled) {
	override->enabled = enabled ? NULL : &false_const;
}

static void kjuq_reload_overrides(void) {
	if (user_config.override_enabled) {
		key_override_on();
	} else {
		key_override_off();
	}

	if (kjuq_is_macos() || kjuq_is_ios()) {
		ctrl_u_key_override.replacement = RGUI(KC_BSPC);
	} else if (kjuq_is_linux() || kjuq_is_windows()) {
		ctrl_u_key_override.replacement = RSFT(RCTL(KC_BSPC));
	}

	for (uint8_t i = 0; i < sizeof(override_rules) / sizeof(override_rules[0]); i++) {
		kjuq_switch_override(override_rules[i].override, kjuq_override_condition_enabled(override_rules[i].condition));
	}
}

static bool kjuq_cmd_key_is_suitable(void) { return kjuq_is_macos() || kjuq_is_ios() || !user_config.cmd_like_ctrl; }

void kjuq_reload_user_eeprom(void) {
	user_config.raw = eeconfig_read_user();
	kjuq_reload_overrides();
	if (user_config.gui_tap && kjuq_cmd_key_is_suitable()) {
		default_layer_or((layer_state_t)1 << _GUI_SPC);
	} else {
		default_layer_or((layer_state_t)1 << _GUI_SPC);
		default_layer_xor((layer_state_t)1 << _GUI_SPC);
	}
	if (user_config.pure_gc && kjuq_cmd_key_is_suitable()) {
		default_layer_or((layer_state_t)1 << _GUI);
	} else {
		default_layer_or((layer_state_t)1 << _GUI);
		default_layer_xor((layer_state_t)1 << _GUI);
	}

	if (user_config.gui_tap && !kjuq_cmd_key_is_suitable()) {
		default_layer_or((layer_state_t)1 << _CTL_SPC);
	} else {
		default_layer_or((layer_state_t)1 << _CTL_SPC);
		default_layer_xor((layer_state_t)1 << _CTL_SPC);
	}
	if (user_config.pure_gc && !kjuq_cmd_key_is_suitable()) {
		default_layer_or((layer_state_t)1 << _CTL);
	} else {
		default_layer_or((layer_state_t)1 << _CTL);
		default_layer_xor((layer_state_t)1 << _CTL);
	}

	if (user_config.left_csg) {
		default_layer_or((layer_state_t)1 << _LEFTCSG);
	} else {
		default_layer_or((layer_state_t)1 << _LEFTCSG);
		default_layer_xor((layer_state_t)1 << _LEFTCSG);
	}

	if (user_config.alt_tap) {
		default_layer_or((layer_state_t)1 << _ALT_SPC);
	} else {
		default_layer_or((layer_state_t)1 << _ALT_SPC);
		default_layer_xor((layer_state_t)1 << _ALT_SPC);
	}
	if (user_config.pure_alt) {
		default_layer_or((layer_state_t)1 << _ALT);
	} else {
		default_layer_or((layer_state_t)1 << _ALT);
		default_layer_xor((layer_state_t)1 << _ALT);
	}
}

static void kjuq_dump_override_state(void) {
	SEND_STRING("#{");

	if (user_config.is_auto_detect_os) {
		SEND_STRING(" DETECTOS");
	}
	if (!user_config.is_auto_detect_os) {
		SEND_STRING(" MANUAL_DETECTION");
	} else if (kjuq_is_macos()) {
		SEND_STRING(" MACOS_DETECTED");
	} else if (kjuq_is_windows()) {
		SEND_STRING(" WIN_DETECTED");
	} else if (kjuq_is_linux()) {
		SEND_STRING(" LINUX_DETECTED");
	} else if (kjuq_is_ios()) {
		SEND_STRING(" IOS_DETECTED");
	} else {
		SEND_STRING(" UNKNOWN_DETECTED");
	}

	SEND_STRING(" |");

	if (user_config.is_macos) {
		SEND_STRING(" MACOS");
	} else if (user_config.is_windows) {
		SEND_STRING(" WIN");
	} else if (user_config.is_linux) {
		SEND_STRING(" LINUX");
	} else if (user_config.is_ios) {
		SEND_STRING(" IOS");
	} else {
		SEND_STRING(" UNKNOWN");
	}

	SEND_STRING(" |");

	if (key_override_is_enabled()) {
		if (user_config.override_modded_esc) {
			SEND_STRING(" MODESC");
		}
		if (user_config.left_csg) {
			SEND_STRING(" LEFTCSG");
		}
		if (user_config.pure_gc) {
			SEND_STRING(" PUREGC");
		}
		if (user_config.gui_tap) {
			SEND_STRING(" GUITAP");
		}
		if (user_config.alt_tap) {
			SEND_STRING(" ALTTAP");
		}
		if (user_config.pure_alt) {
			SEND_STRING(" PUREALT");
		}
		if (user_config.cmd_like_ctrl) {
			SEND_STRING(" GUI_CTL");
		}

		SEND_STRING(" |");

		if (user_config.override_enter) {
			SEND_STRING(" ENT");
		}
		if (user_config.override_backspace) {
			SEND_STRING(" BKSP");
		}
		if (user_config.override_tab) {
			SEND_STRING(" TAB");
		}
		if (user_config.override_arrows) {
			SEND_STRING(" ARR");
		}
		if (user_config.override_delete) {
			SEND_STRING(" DEL");
		}
		if (user_config.override_home) {
			SEND_STRING(" HOME");
		}
		if (user_config.override_end) {
			SEND_STRING(" END");
		}

		SEND_STRING(" |");

		if (user_config.override_ctrl_u) {
			SEND_STRING(" CTLU");
		}
		if (user_config.override_ctrl_k) {
			SEND_STRING(" CTLK");
		}
		if (user_config.override_word_dl) {
			SEND_STRING(" WDDL");
		}
		if (user_config.override_word_mv) {
			SEND_STRING(" WDMV");
		}

		SEND_STRING(" |");

		if (user_config.override_cut) {
			SEND_STRING(" CUT");
		}
		if (user_config.override_copy) {
			SEND_STRING(" COPY");
		}
		if (user_config.override_paste) {
			SEND_STRING(" PASTE");
		}

		SEND_STRING(" |");

		if (user_config.is_jis_mode) {
			SEND_STRING(" JIS");
		}
	} else {
		SEND_STRING(" OVERRIDE DISABLED");
	}

	SEND_STRING(" }");
}

typedef enum {
	KJUQ_CONFIG_OVERRIDE_TAB,
	KJUQ_CONFIG_OVERRIDE_ENTER,
	KJUQ_CONFIG_OVERRIDE_BACKSPACE,
	KJUQ_CONFIG_OVERRIDE_DELETE,
	KJUQ_CONFIG_OVERRIDE_ARROWS,
	KJUQ_CONFIG_OVERRIDE_HOME,
	KJUQ_CONFIG_OVERRIDE_END,
	KJUQ_CONFIG_OVERRIDE_CTRL_U,
	KJUQ_CONFIG_OVERRIDE_CTRL_K,
	KJUQ_CONFIG_OVERRIDE_MODDED_ESC,
	KJUQ_CONFIG_OVERRIDE_WORD_MV,
	KJUQ_CONFIG_OVERRIDE_WORD_DL,
	KJUQ_CONFIG_JIS_MODE,
	KJUQ_CONFIG_OVERRIDE_CUT,
	KJUQ_CONFIG_OVERRIDE_COPY,
	KJUQ_CONFIG_OVERRIDE_PASTE,
	KJUQ_CONFIG_AUTO_DETECT_OS,
	KJUQ_CONFIG_OVERRIDE_ENABLED,
	KJUQ_CONFIG_GUI_TAP,
	KJUQ_CONFIG_ALT_TAP,
	KJUQ_CONFIG_LEFT_CSG,
	KJUQ_CONFIG_PURE_GC,
	KJUQ_CONFIG_PURE_ALT,
	KJUQ_CONFIG_CMD_LIKE_CTRL,
} config_flag_t;

typedef struct {
	uint16_t keycode;
	config_flag_t flag;
} config_toggle_t;

static const config_toggle_t config_toggles[] = {
    {KO_TB, KJUQ_CONFIG_OVERRIDE_TAB},       {KO_EN, KJUQ_CONFIG_OVERRIDE_ENTER},
    {KO_BS, KJUQ_CONFIG_OVERRIDE_BACKSPACE}, {KO_DL, KJUQ_CONFIG_OVERRIDE_DELETE},
    {KO_AR, KJUQ_CONFIG_OVERRIDE_ARROWS},    {KO_HM, KJUQ_CONFIG_OVERRIDE_HOME},
    {KO_ED, KJUQ_CONFIG_OVERRIDE_END},       {KO_CTLU, KJUQ_CONFIG_OVERRIDE_CTRL_U},
    {KO_CTLK, KJUQ_CONFIG_OVERRIDE_CTRL_K},  {KO_MTAB, KJUQ_CONFIG_OVERRIDE_MODDED_ESC},
    {KO_WD, KJUQ_CONFIG_OVERRIDE_WORD_MV},   {KO_WDDL, KJUQ_CONFIG_OVERRIDE_WORD_DL},
    {KO_JIS, KJUQ_CONFIG_JIS_MODE},          {KO_CUT, KJUQ_CONFIG_OVERRIDE_CUT},
    {KO_COPY, KJUQ_CONFIG_OVERRIDE_COPY},    {KO_PAST, KJUQ_CONFIG_OVERRIDE_PASTE},
    {DTCT_OS, KJUQ_CONFIG_AUTO_DETECT_OS},   {KO_TOGG, KJUQ_CONFIG_OVERRIDE_ENABLED},
    {MT_GCS, KJUQ_CONFIG_GUI_TAP},           {MT_ALTS, KJUQ_CONFIG_ALT_TAP},
    {LEFTCSG, KJUQ_CONFIG_LEFT_CSG},         {PUREGC, KJUQ_CONFIG_PURE_GC},
    {PUREALT, KJUQ_CONFIG_PURE_ALT},         {GUI_CTL, KJUQ_CONFIG_CMD_LIKE_CTRL},
};

static void kjuq_toggle_config_flag(config_flag_t flag) {
	switch (flag) {
	case KJUQ_CONFIG_OVERRIDE_TAB:
		user_config.override_tab = !user_config.override_tab;
		break;
	case KJUQ_CONFIG_OVERRIDE_ENTER:
		user_config.override_enter = !user_config.override_enter;
		break;
	case KJUQ_CONFIG_OVERRIDE_BACKSPACE:
		user_config.override_backspace = !user_config.override_backspace;
		break;
	case KJUQ_CONFIG_OVERRIDE_DELETE:
		user_config.override_delete = !user_config.override_delete;
		break;
	case KJUQ_CONFIG_OVERRIDE_ARROWS:
		user_config.override_arrows = !user_config.override_arrows;
		break;
	case KJUQ_CONFIG_OVERRIDE_HOME:
		user_config.override_home = !user_config.override_home;
		break;
	case KJUQ_CONFIG_OVERRIDE_END:
		user_config.override_end = !user_config.override_end;
		break;
	case KJUQ_CONFIG_OVERRIDE_CTRL_U:
		user_config.override_ctrl_u = !user_config.override_ctrl_u;
		break;
	case KJUQ_CONFIG_OVERRIDE_CTRL_K:
		user_config.override_ctrl_k = !user_config.override_ctrl_k;
		break;
	case KJUQ_CONFIG_OVERRIDE_MODDED_ESC:
		user_config.override_modded_esc = !user_config.override_modded_esc;
		break;
	case KJUQ_CONFIG_OVERRIDE_WORD_MV:
		user_config.override_word_mv = !user_config.override_word_mv;
		break;
	case KJUQ_CONFIG_OVERRIDE_WORD_DL:
		user_config.override_word_dl = !user_config.override_word_dl;
		break;
	case KJUQ_CONFIG_JIS_MODE:
		user_config.is_jis_mode = !user_config.is_jis_mode;
		break;
	case KJUQ_CONFIG_OVERRIDE_CUT:
		user_config.override_cut = !user_config.override_cut;
		break;
	case KJUQ_CONFIG_OVERRIDE_COPY:
		user_config.override_copy = !user_config.override_copy;
		break;
	case KJUQ_CONFIG_OVERRIDE_PASTE:
		user_config.override_paste = !user_config.override_paste;
		break;
	case KJUQ_CONFIG_AUTO_DETECT_OS:
		user_config.is_auto_detect_os = !user_config.is_auto_detect_os;
		break;
	case KJUQ_CONFIG_OVERRIDE_ENABLED:
		user_config.override_enabled = !user_config.override_enabled;
		break;
	case KJUQ_CONFIG_GUI_TAP:
		user_config.gui_tap = !user_config.gui_tap;
		break;
	case KJUQ_CONFIG_ALT_TAP:
		user_config.alt_tap = !user_config.alt_tap;
		break;
	case KJUQ_CONFIG_LEFT_CSG:
		user_config.left_csg = !user_config.left_csg;
		break;
	case KJUQ_CONFIG_PURE_GC:
		user_config.pure_gc = !user_config.pure_gc;
		break;
	case KJUQ_CONFIG_PURE_ALT:
		user_config.pure_alt = !user_config.pure_alt;
		break;
	case KJUQ_CONFIG_CMD_LIKE_CTRL:
		user_config.cmd_like_ctrl = !user_config.cmd_like_ctrl;
		break;
	}

	eeconfig_update_user(user_config.raw);
	kjuq_reload_user_eeprom();
}

static void kjuq_cycle_os(void) {
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

bool kjuq_process_override_keycode(uint16_t keycode, keyrecord_t *record) {
	for (uint8_t i = 0; i < sizeof(config_toggles) / sizeof(config_toggles[0]); i++) {
		if (config_toggles[i].keycode == keycode) {
			if (record->event.pressed) {
				kjuq_toggle_config_flag(config_toggles[i].flag);
			}
			return true;
		}
	}

	switch (keycode) {
	case CYCL_OS:
		if (record->event.pressed) {
			kjuq_cycle_os();
		}
		return true;
	case KO_PRNT:
		if (record->event.pressed) {
			kjuq_dump_override_state();
		}
		return true;
	default:
		return false;
	}
}

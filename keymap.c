#include "action_util.h"

#include "keycodes.h"
#include "quantum.h"

#include "user_keycodes.h"
#include "user_layers.h"
#include "user_overrides.c"

#include "user_init.c"
#include "user_utils.c"

#include "user_layouts.c" // necessary; setting layouts

static uint16_t last_keycode;
static int mouse_acl_pressed = 0;

void oneshot_layer_changed_user(uint8_t layer) {
	if (layer == _MODS || layer == _ORS) {
		user_disable_all_overrides();
	} else { // Exit _MODS and _ORS
		user_reload_user_eeprom();
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
	case LWRFNC:
	case RISFNC:
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
	user_reload_user_eeprom();
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
				user_enter_layer(_ADJUST, HSV_ADJUST);
			} else {
				user_exit_layer();
			}
		}
		return (false);

	case ADJUST2:
		if (record->event.pressed) {
			if (IS_LAYER_OFF(_ADJUST2)) {
				layer_move(_ADJUST2);
				rgblight_reload_from_eeprom();
			} else {
				user_exit_layer();
			}
		}
		return (false);

	case RAISE:
	case RISFNC:
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
			user_exit_layer();
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
			user_reload_user_eeprom();
		}
		return (false);

	case KO_EN:
		if (record->event.pressed) {
			user_config.override_enter = !user_config.override_enter;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_BS:
		if (record->event.pressed) {
			user_config.override_backspace = !user_config.override_backspace;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_DL:
		if (record->event.pressed) {
			user_config.override_delete = !user_config.override_delete;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_AR:
		if (record->event.pressed) {
			user_config.override_arrows = !user_config.override_arrows;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_HM:
		if (record->event.pressed) {
			user_config.override_home = !user_config.override_home;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_ED:
		if (record->event.pressed) {
			user_config.override_end = !user_config.override_end;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_CTLU:
		if (record->event.pressed) {
			user_config.override_ctrl_u = !user_config.override_ctrl_u;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_CTLK:
		if (record->event.pressed) {
			user_config.override_ctrl_k = !user_config.override_ctrl_k;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_CMDQ:
		if (record->event.pressed) {
			user_config.override_cmd_q = !user_config.override_cmd_q;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_MTAB:
		if (record->event.pressed) {
			user_config.override_modded_esc = !user_config.override_modded_esc;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_WD:
		if (record->event.pressed) {
			user_config.override_word_mv = !user_config.override_word_mv;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_WDDL:
		if (record->event.pressed) {
			user_config.override_word_dl = !user_config.override_word_dl;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_LXCM:
		if (record->event.pressed) {
			user_config.override_linux_cmd = !user_config.override_linux_cmd;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_LSPK:
		if (record->event.pressed) {
			user_config.override_linux_special_keys = !user_config.override_linux_special_keys;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case KO_JIS:
		if (record->event.pressed) {
			user_config.is_jis_mode = !user_config.is_jis_mode;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
		}
		return (false);

	case DTCT_OS:
		if (record->event.pressed) {
			user_config.is_auto_detect_os = !user_config.is_auto_detect_os;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
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
			user_reload_user_eeprom();
		}
		return (false);

	case KO_PRNT:
		if (record->event.pressed) {
			user_dump_override_state();
		}
		return (false);

	// Hold tap
	case MT_SPC:
		if (record->event.pressed) {
			user_config.spc_tap = !user_config.spc_tap;
			eeconfig_update_user(user_config.raw);
			user_reload_user_eeprom();
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

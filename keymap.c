#include "action_util.h"
#include "print.h"
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "keycodes.h"
#include "os_detection.h"

#include "user_keycodes.h"
#include "user_layers.h"
#include "user_overrides_utils.c"

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
            return 125;
        default:
            return TAPPING_TERM;
    }
    (void)record; // suppress unused parameter warning
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_SPC:
        case ALT_SPC:
            // Do not select the hold action when another key is pressed.
            return false;
        default:
            // Immediately select the hold action when another key is pressed.
            return true;
    }
    (void)record; // suppress unused parameter warning
}

void keyboard_post_init_user(void) {
    wait_ms(500); // wait to detect OS properly

    if (detected_host_os() == OS_MACOS) {
        user_init_macos();
    } else if (detected_host_os() == OS_IOS) {
        user_init_ios();
    } else if (detected_host_os() == OS_LINUX) {
        user_init_linux();
    } else if (detected_host_os() == OS_WINDOWS) {
        user_init_windows();
    } else {
        user_init_unsure();
    }

    user_reload_user_eeprom();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Layers
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                if (IS_LAYER_OFF(_ADJUST)) {
                    user_enter_layer(_ADJUST, HSV_ADJUST);
                } else {
                    user_exit_layer();
                }
            }
            return false;
        case ADJUST2:
            if (record->event.pressed) {
                if (IS_LAYER_OFF(_ADJUST2)) {
                    layer_move(_ADJUST2);
                    rgblight_reload_from_eeprom();
                } else {
                    user_exit_layer();
                }
            }
            return false;
        case RAISE:
        case RISFNC:
            if (record->event.pressed) {
                // do nothing special
            } else {
                layer_off(_MOUSE);
            }
            return true;

        // MOUSE
        case MOUSE:
            if (record->event.pressed) {
                layer_on(_MOUSE);
                unregister_code(KC_LSFT);
            }
            return false;
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
            return false;


        // Extra keys
        case EXT_LYR:
            if (record->event.pressed) {
                user_exit_layer();
            }
            return false;
        case HOLDLST:
            if (record->event.pressed) {
                register_code16(last_keycode);
            }
            return false;

        // Hooks
        case KO_TOGG:
            if (record->event.pressed) {
                user_react_key_press(HSV_ORANGE);
            }
            return true;

        // Key override
        case KO_TB:
            if (record->event.pressed) {
                user_config.override_tab = user_config.override_tab ? false : true;
                user_override_toggle_post(user_config.override_tab);
            }
            return false;
        case KO_EN:
            if (record->event.pressed) {
                user_config.override_enter = user_config.override_enter ? false : true;
                user_override_toggle_post(user_config.override_enter);
            }
            return false;
        case KO_BS:
            if (record->event.pressed) {
                user_config.override_backspace = user_config.override_backspace ? false : true;
                user_override_toggle_post(user_config.override_backspace);
            }
            return false;
        case KO_DL:
            if (record->event.pressed) {
                user_config.override_delete = user_config.override_delete ? false : true;
                user_override_toggle_post(user_config.override_delete);
            }
            return false;
        case KO_AR:
            if (record->event.pressed) {
                user_config.override_arrows = user_config.override_arrows ? false : true;
                user_override_toggle_post(user_config.override_arrows);
            }
            return false;
        case KO_HM:
            if (record->event.pressed) {
                user_config.override_home = user_config.override_home ? false : true;
                user_override_toggle_post(user_config.override_home);
            }
            return false;
        case KO_ED:
            if (record->event.pressed) {
                user_config.override_end = user_config.override_end ? false : true;
                user_override_toggle_post(user_config.override_end);
            }
            return false;
        case KO_CTLU:
            if (record->event.pressed) {
                user_config.override_ctrl_u = user_config.override_ctrl_u ? false : true;
                user_override_toggle_post(user_config.override_ctrl_u);
            }
            return false;

        case KO_CMDQ:
            if (record->event.pressed) {
                user_config.override_cmd_q = user_config.override_cmd_q ? false : true;
                user_override_toggle_post(user_config.override_cmd_q);
            }
            return false;
        case KO_MTAB:
            if (record->event.pressed) {
                user_config.override_modded_esc = user_config.override_modded_esc ? false : true;
                user_override_toggle_post(user_config.override_modded_esc);
            }
            return false;
        case KO_WD:
            if (record->event.pressed) {
                bool cur_status;
                if (user_is_apple()) {
                    cur_status                       = user_config.override_word_mv_apl;
                    user_config.override_word_mv_apl = cur_status ? false : true;
                } else {
                    cur_status                       = user_config.override_word_mv_lnx;
                    user_config.override_word_mv_lnx = cur_status ? false : true;
                }
                user_override_toggle_post(cur_status);
            }
            return false;
        case KO_WDDL:
            if (record->event.pressed) {
                bool cur_status;
                if (user_is_apple()) {
                    cur_status                       = user_config.override_word_dl_apl;
                    user_config.override_word_dl_apl = cur_status ? false : true;
                } else {
                    cur_status                       = user_config.override_word_dl_lnx;
                    user_config.override_word_dl_lnx = cur_status ? false : true;
                }
                user_override_toggle_post(cur_status);
            }
            return false;
        case KO_LXCM:
            if (record->event.pressed) {
                user_config.override_linux_cmd = user_config.override_linux_cmd ? false : true;
                user_override_toggle_post(user_config.override_linux_cmd);
            }
            return false;

        case KO_JIS:
            if (record->event.pressed) {
                user_config.is_jis_mode = user_config.is_jis_mode ? false : true;
                user_override_toggle_post(user_config.is_jis_mode);
            }
            return false;

        case KO_PRNT:
            if (record->event.pressed) {
                user_dump_override_state();
            }
            return false;

        // Hold tap
        case LT_FNC:
            if (record->event.pressed) {
                user_config.fnc_tap = user_config.fnc_tap ? false : true;
                user_override_toggle_post(user_config.fnc_tap);
            }
            return false;

        case MT_SPC:
            if (record->event.pressed) {
                user_config.spc_tap = user_config.spc_tap ? false : true;
                user_override_toggle_post(user_config.spc_tap);
            }
            return false;
        case RGB_RDP:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
            }
        default:
            last_keycode = get_last_keycode();
    }

    return true;
}

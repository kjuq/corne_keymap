#include QMK_KEYBOARD_H
#include "overrides.h"

#define HSV_ADJUST HSV_YELLOW

// user defined keycodes
#define GUI_SPC LGUI_T(KC_SPC)
#define CTL_SPC RCTL_T(KC_SPC)
#define ALT_SPC LALT_T(KC_SPC)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
// #define RAISE LM(_RAISE, MOD_MASK_SHIFT)

#define ORS OSL(_ORS)

#define SC_TAB (QK_RCTL | QK_RSFT | KC_TAB)
#define SA_TAB (QK_RALT | QK_RSFT | KC_TAB)

#define S_PGDN RSFT(KC_PGDN)
#define S_PGUP RSFT(KC_PGUP)

#define KJUQ_KEY_OVERRIDE(override, condition) &override,
const key_override_t *key_overrides[] = {KJUQ_OVERRIDE_TABLE(KJUQ_KEY_OVERRIDE) NULL};
#undef KJUQ_KEY_OVERRIDE

// clang-format off
/* *INDENT-OFF* */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT_split_3x5_3_ex2( // {{{
		KC_ESC,  KC_W,    KC_F,    KC_P,    KC_B,    KC_LEFT,         KC_UP,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_ENT,
		KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_RGHT,         KC_DOWN, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
		KC_LGUI, KC_X,    KC_C,    KC_D,    KC_V,                              KC_K,    KC_M,    KC_Z,    KC_Q,    MOD_CSG,
		                           LOWER,   KC_LCTL, KC_SPC,          KC_SPC,  KC_LSFT, RAISE
	), // }}}

	[_ALT_SPC] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, _______,         ALT_SPC, _______, _______
	), // }}}

	[_ALT] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, _______,         KC_LALT, _______, _______
	), // }}}

	[_GUI_SPC] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, GUI_SPC,         _______, _______, _______
	), // }}}

	[_CTL_SPC] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, CTL_SPC,         _______, _______, _______
	), // }}}

	[_GUI] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, KC_LGUI,         _______, _______, _______
	), // }}}

	[_CTL] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
		                           _______, _______, KC_RCTL,         _______, _______, _______
	), // }}}

	[_LEFTCSG] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
		MOD_CSG, _______, _______, _______, _______,                           _______, _______, _______, _______, KC_LGUI,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_LOWER] = LAYOUT_split_3x5_3_ex2( // {{{
		SC_TAB,  KC_MINS, KC_EQL,  KC_GRV,  XXXXXXX, XXXXXXX,         XXXXXXX, KC_PGDN, KC_7,    KC_8,    KC_9,    KC_BSPC,
		MOD_CAG, KC_SLSH, KC_LBRC, KC_RBRC, KC_QUOT, XXXXXXX,         XXXXXXX, KC_0,    KC_4,    KC_5,    KC_6,    FNCTN,
		KC_RCTL, KC_SCLN, KC_COMM, KC_DOT,  KC_BSLS,                           KC_PGUP, KC_1,    KC_2,    KC_3,    KC_RALT,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_RAISE] = LAYOUT_split_3x5_3_ex2( // {{{
		SA_TAB,  KC_UNDS, KC_PLUS, KC_TILD, XXXXXXX, XXXXXXX,         XXXXXXX, S_PGDN,  KC_AMPR, KC_ASTR, KC_LPRN, KC_BSPC,
		XXXXXXX, KC_QUES, KC_LCBR, KC_RCBR, KC_DQUO, XXXXXXX,         XXXXXXX, KC_RPRN, KC_DLR,  KC_PERC, KC_CIRC, MOUSE,
		KC_RSFT, KC_COLN, KC_LABK, KC_RABK, KC_PIPE,                           S_PGUP,  KC_EXLM, KC_AT,   KC_HASH, KC_RGUI,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_FNCTN] = LAYOUT_split_3x5_3_ex2( // {{{
		XXXXXXX, KC_INS,  KC_VOLU, KC_BRIU, KC_SCRL, XXXXXXX,         XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   HOLDLST,
		ADJUST,  KC_PSCR, KC_VOLD, KC_BRID, KC_CAPS, XXXXXXX,         XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX,
		XXXXXXX, XXXXXXX, KC_MUTE, KC_MPLY, KC_PAUS,                           KC_F10,  KC_F1,   KC_F2,   KC_F3,   ORS,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

	[_ORS] = LAYOUT_split_3x5_3_ex2( // {{{
		EXT_LYR, XXXXXXX, KC_RGHT, KC_UP,   KC_LEFT, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_BSPC, KC_DOWN, KC_END,  KC_TAB,  XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX,                           XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX,
		                           _______, KC_LCTL, KC_LGUI,         KC_LALT, KC_LSFT, _______
	), // }}}

	[_ADJUST] = LAYOUT_split_3x5_3_ex2( // {{{
		EXT_LYR, KO_WDDL, KO_WD,   XXXXXXX, KO_AR,   XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, KO_CTLU, XXXXXXX, XXXXXXX,
		KO_HM,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KO_BS,   KO_TOGG, KO_ED,   KO_TB,   ADJUST2,
		LEFTCSG, KO_CUT,  KO_COPY, KO_DL,   KO_PAST,                           KO_CTLK, KO_EN,   XXXXXXX, KO_JIS,  KO_PRNT,
			                       GUI_CTL, PUREGC,  MT_GCS,          MT_ALTS, PUREALT, KO_MTAB
	), // }}}

	[_ADJUST2] = LAYOUT_split_3x5_3_ex2( // {{{
		EXT_LYR, QK_BOOT, QK_RBT,  DB_TOGG, RM_TOGG, XXXXXXX,         XXXXXXX, RM_SPDU, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,
		EE_CLR,  XXXXXXX, DTCT_OS, CYCL_OS, COLEMAK, XXXXXXX,         XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_RDP,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		                           XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_RSFT, XXXXXXX
	), // }}}

	[_MOUSE] = LAYOUT_split_3x5_3_ex2( // {{{
		_______, MS_WHLU, MS_UP,   MS_WHLD, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, MS_BTN3, MS_BTN2, XXXXXXX, XXXXXXX,
		XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN5, XXXXXXX,         XXXXXXX, XXXXXXX, MS_BTN1, MS_ACL1, MS_ACL1, KC_LSFT,
		XXXXXXX, MS_WHLL, XXXXXXX, MS_WHLR, MS_BTN4,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,
		                           _______, _______, _______,         _______, _______, _______
	), // }}}

};
// clang-format on
/* *INDENT-ON* */

void kjuq_enter_layer(uint8_t layer, uint8_t hue, uint8_t sat, uint8_t val) {
	layer_move(layer);
	rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_PINWHEEL_VAL);
	rgb_matrix_sethsv_noeeprom(hue, sat, val);
}

void kjuq_exit_layer(void) {
	layer_clear();
	rgblight_reload_from_eeprom();
}

static uint16_t last_keycode;
static int mouse_acl_pressed = 0;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case GUI_SPC:
	case CTL_SPC:
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
	// wait to detect OS properly. The duration depends on devices. `process_detected_host_os_user` not worked
	wait_ms(500);
	kjuq_reload_user_eeprom();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (kjuq_process_override_keycode(keycode, record)) {
		return false;
	}

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

	case LOWER:
		if (!record->event.pressed) {
			layer_off(_FNCTN);
		}
		return (true);

	case MOD_CAG:
		if (record->event.pressed) {
			register_code(KC_RCTL);
			register_code(KC_RALT);
			register_code(KC_RGUI);
		} else {
			unregister_code(KC_RCTL);
			unregister_code(KC_RALT);
			unregister_code(KC_RGUI);
		}
		return (false);

	case MOD_CSG:
		if (record->event.pressed) {
			register_code(KC_RCTL);
			register_code(KC_RSFT);
			register_code(KC_RGUI);
		} else {
			unregister_code(KC_RCTL);
			unregister_code(KC_RSFT);
			unregister_code(KC_RGUI);
		}
		return (false);

	// MOUSE
	case MOUSE:
		if (record->event.pressed) {
			layer_on(_MOUSE);
			// unregister_code(KC_LSFT);
		}
		return (false);

	case FNCTN:
		if (record->event.pressed) {
			layer_on(_FNCTN);
		}
		return (false);

	case MS_ACL1:
		if (record->event.pressed) {
			if (mouse_acl_pressed == 1) {
				register_code(MS_ACL0);
			} else {
				register_code(MS_ACL1);
			}
			mouse_acl_pressed++;
		} else {
			if (mouse_acl_pressed == 2) {
				unregister_code(MS_ACL0);
				register_code(MS_ACL1);
			} else {
				unregister_code(MS_ACL1);
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

	case RGB_RDP:
		if (record->event.pressed) {
			rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
		}

	default:
		last_keycode = get_last_keycode();
	}

	return (true);
}

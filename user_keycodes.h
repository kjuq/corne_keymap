#pragma once

#include "quantum_keycodes.h"

// user defined keycodes
#define CMD_SPC LGUI_T(KC_SPC)
#define ALT_SPC RALT_T(KC_SPC)

#define LOWER MO(_LOWER)
#define RAISE LM(_RAISE, MOD_MASK_SHIFT)

#define LWRFNC LT(_LOWER, KC_F18)
#define RISFNC LT(_RAISE, KC_F19)

#define FNCTN OSL(_FNCTN)
#define MODS OSL(_MODS)
#define ORS OSL(_ORS)

#define SC_TAB (QK_LCTL | QK_RSFT | KC_TAB)
#define SA_TAB (QK_RALT | QK_RSFT | KC_TAB)
#define EISU KC_LNG2
#define KANA KC_LNG1

// Home Row Mod
#define CM_ESC LT(_HRMOD, KC_ESC)
#define CM_W LT(_SPACES, KC_W)
#define CM_F LT(_SPACES, KC_F)
#define CM_P LT(_SPACES, KC_P)
#define CM_B LT(_HRMOD, KC_B)
#define CM_J LT(_HRMOD, KC_J)
#define CM_L LT(_SPACES, KC_L)
#define CM_U LT(_SPACES, KC_U)
#define CM_Y LT(_SPACES, KC_Y)
#define CM_Q LT(_HRMOD, KC_Q)

#define CM_A MT(MOD_LGUI, KC_A)
#define CM_R MT(MOD_RALT, KC_R)
#define CM_S MT(MOD_RSFT, KC_S)
#define CM_T MT(MOD_LCTL, KC_T)
#define CM_G LT(_HRMOD, KC_G)
#define CM_H LT(_HRMOD, KC_H)
#define CM_N MT(MOD_LCTL, KC_N)
#define CM_E MT(MOD_RSFT, KC_E)
#define CM_I MT(MOD_RALT, KC_I)
#define CM_O MT(MOD_LGUI, KC_O)

#define CM_Z LT(_MOUSE, KC_Z)
#define CM_X LT(_FNCTN, KC_X)
#define CM_C LT(_RAISE, KC_C)
#define CM_D LT(_LOWER, KC_D)
#define CM_V LT(_HRMOD, KC_V)
#define CM_K LT(_HRMOD, KC_K)
#define CM_M LT(_LOWER, KC_M)
#define CM_COMM LT(_RAISE, KC_COMM)
#define CM_DOT LT(_FNCTN, KC_DOT)
#define CM_SPC LT(_MOUSE, KC_SPC)

enum planck_keycodes {
	COLEMAK = SAFE_RANGE,
	QWERTY,
	LNG_TAP,
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
	KO_CTLO,
	KO_WD,
	KO_WDDL,
	KO_CTLU,
	KO_CMDV,
	KO_CMDD,
	KO_CMDQ,
	KO_MTAB,
	KO_LXCM,
	KO_JIS,
	KO_PRNT,
	MT_HRM,
	MT_SPC,
	ERGOLFT,
	ERGORIT,
	HOLDLST,
	DTCT_OS,
	CYCL_OS,
	RGB_RDP,
};

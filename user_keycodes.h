#pragma once

#include "quantum_keycodes.h"

// user defined keycodes
#define CMD_SPC LGUI_T(KC_SPC)
#define ALT_SPC RALT_T(KC_SPC)

#define LOWER MO(_LOWER)
#define LWRFNC LT(_LOWER, KC_F18)
#define RAISE LM(_RAISE, MOD_MASK_SHIFT)
#define RISFNC LT(_RAISE, KC_F19)
#define FNCTN OSL(_FNCTN)
#define MODS OSL(_MODS)
#define ORS OSL(_ORS)

#define MOD_CAG LM(0, MOD_MASK_CAG)

#define SC_TAB (QK_LCTL | QK_RSFT | KC_TAB)
#define SA_TAB (QK_RALT | QK_RSFT | KC_TAB)
#define EISU KC_LNG2
#define KANA KC_LNG1

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    LNG_TAP,
    ADJUST,
    ADJUST2,
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
    LT_FNC,
    MT_SPC,
    HOLDLST,
    RGB_RDP,
};

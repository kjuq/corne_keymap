#pragma once

#include QMK_KEYBOARD_H

#include "user_layers.h"
#include "user_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_COLEMAK] = LAYOUT_split_3x5_3_ex2( // {{{
        KC_ESC,  KC_W,    KC_F,    KC_P,    KC_B,    KC_F13,          KC_F15,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_Q,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_F14,          KC_F16,  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                              KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
                                   LOWER,   KC_LCTL, KC_SPC,          KC_SPC,  KC_RSFT, RAISE
    ), // }}}

    [_QWERTY] = LAYOUT_split_3x5_3_ex2( // {{{
        KC_ESC,  KC_W,    KC_E,    KC_R,    KC_T,    _______,         _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,         _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_Q,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,    KC_M,    _______, _______, _______,
                                   _______, _______, _______,         _______, _______, _______
    ), // }}}

    [_FNC_TAP] = LAYOUT_split_3x5_3_ex2( // {{{
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
                                   LWRFNC,  _______, _______,         _______, _______, RISFNC
    ), // }}}

    [_SPC_TAP] = LAYOUT_split_3x5_3_ex2( // {{{
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,
                                   _______, _______, CMD_SPC,         ALT_SPC, _______, _______
    ), // }}}

    [_LOWER] = LAYOUT_split_3x5_3_ex2( // {{{
        SC_TAB,  KC_MINS, KC_EQL,  KC_QUOT, XXXXXXX, XXXXXXX,         XXXXXXX, FNCTN,   KC_7,    KC_8,    KC_9,    KC_BSPC,
        MOD_CAG, KC_SLSH, KC_LBRC, KC_RBRC, KC_GRV,  XXXXXXX,         XXXXXXX, KC_0,    KC_4,    KC_5,    KC_6,    XXXXXXX,
        KC_RCTL, KC_COMM, KC_DOT,  KC_SCLN, KC_BSLS,                           XXXXXXX, KC_1,    KC_2,    KC_3,    KC_LSFT,
                                   _______, _______, _______,         _______, _______, _______
    ), // }}}

    [_RAISE] = LAYOUT_split_3x5_3_ex2( // {{{
        SA_TAB,  KC_UNDS, KC_PLUS, KC_DQUO, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_BSPC,
        XXXXXXX, KC_QUES, KC_LCBR, KC_RCBR, KC_TILD, XXXXXXX,         XXXXXXX, KC_RPRN, KC_DLR,  KC_PERC, KC_CIRC, MOUSE,
        KC_RCMD, KC_LABK, KC_RABK, KC_COLN, KC_PIPE,                           XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_LALT,
                                   _______, _______, _______,         _______, _______, _______
    ), // }}}

    [_FNCTN] = LAYOUT_split_3x5_3_ex2( // {{{
        XXXXXXX, KC_BRIU, KC_VOLU, KC_PSCR, ADJUST,  XXXXXXX,         XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX,
        HOLDLST, KC_BRID, KC_VOLD, KC_PGUP, KC_INS,  XXXXXXX,         XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   MODS,
        KC_PAUS, KC_SCRL, KC_MPLY, KC_PGDN, KC_CAPS,                           KC_F10,  KC_F1,   KC_F2,   KC_F3,   ORS,
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
                                   KC_LNG2, _______, _______,         _______, _______, KC_LNG1
    ), // }}}

    [_ADJUST] = LAYOUT_split_3x5_3_ex2( // {{{
        EXT_LYR, KO_WDDL, KO_WD,   XXXXXXX, KO_AR,   XXXXXXX,         XXXXXXX, ADJUST2, XXXXXXX, KO_CTLU, XXXXXXX, KO_CMDQ,
        KO_HM,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KO_BS,   XXXXXXX, KO_ED,   KO_TB,   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KO_DL,   XXXXXXX,                           XXXXXXX, KO_EN,   XXXXXXX, KO_JIS,  KO_PRNT,
                                   XXXXXXX, XXXXXXX, KO_LXCM,         MT_SPC,  KO_MTAB, LT_FNC
    ), // }}}

    [_ADJUST2] = LAYOUT_split_3x5_3_ex2( // {{{
        EXT_LYR, QK_BOOT, DB_TOGG, RGB_TOG, XXXXXXX, XXXXXXX,         XXXXXXX, RGB_SPI, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        XXXXXXX, XXXXXXX, QWERTY,  COLEMAK, XXXXXXX, XXXXXXX,         XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_RDP,
        CYCL_OS, DTCT_OS, KO_TOGG, EE_CLR,  XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_RSFT, XXXXXXX
    ), // }}}

    [_MOUSE] = LAYOUT_split_3x5_3_ex2( // {{{
        _______, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, XXXXXXX,         XXXXXXX, XXXXXXX, KC_BTN1, KC_ACL1, KC_ACL1, KC_LSFT,
        XXXXXXX, KC_WH_L, XXXXXXX, KC_WH_R, KC_BTN4,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,
                                   _______, _______, _______,         _______, _______, _______
    ), // }}}

    // clang-format on

};

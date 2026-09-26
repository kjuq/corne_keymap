#pragma once

enum planck_keycodes {
	COLEMAK = SAFE_RANGE,
	ADJUST,
	ADJUST2,
	MOD_CAG,
	MOD_CSG,
	MOUSE,
	FNCTN,
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
	KO_MTAB,
	KO_JIS,
	KO_PRNT,
	KO_CUT,
	KO_COPY,
	KO_PAST,
	MT_GCS,
	MT_ALTS,
	LEFTCSG,
	PUREGC,
	PUREALT,
	GUI_CTL,
	HOLDLST,
	DTCT_OS,
	CYCL_OS,
	RGB_RDP,
};

enum planck_layers {
	_COLEMAK,
	_ALT_SPC,
	_ALT,
	_GUI_SPC,
	_CTL_SPC,
	_GUI,
	_CTL,
	_LEFTCSG,
	_LOWER,
	_RAISE,
	_FNCTN,
	_ORS,
	_ADJUST,
	_ADJUST2,
	_MOUSE,
};

// QMK includes keymap.c while compiling keymap introspection, so the registry
// is shared here and the key_overrides array is instantiated in keymap.c.
#define KJUQ_OVERRIDE_TABLE(X)                                                                                         \
	X(enter_key_override, KJUQ_OVERRIDE_ENTER)                                                                         \
	X(tab_key_override, KJUQ_OVERRIDE_TAB)                                                                             \
	X(right_key_override, KJUQ_OVERRIDE_ARROWS)                                                                        \
	X(left_key_override, KJUQ_OVERRIDE_ARROWS)                                                                         \
	X(up_key_override, KJUQ_OVERRIDE_ARROWS)                                                                           \
	X(down_key_override, KJUQ_OVERRIDE_ARROWS)                                                                         \
	X(bs_key_override, KJUQ_OVERRIDE_BACKSPACE)                                                                        \
	X(del_key_override, KJUQ_OVERRIDE_DELETE)                                                                          \
	X(home_key_override, KJUQ_OVERRIDE_HOME)                                                                           \
	X(end_key_override, KJUQ_OVERRIDE_END)                                                                             \
	X(ctrl_u_key_override, KJUQ_OVERRIDE_CTRL_U)                                                                       \
	X(ctrl_k_key_override, KJUQ_OVERRIDE_CTRL_K)                                                                       \
	X(w_fwd_mac_override, KJUQ_OVERRIDE_WORD_MAC)                                                                      \
	X(w_bck_mac_override, KJUQ_OVERRIDE_WORD_MAC)                                                                      \
	X(w_del_mac_override, KJUQ_OVERRIDE_WORD_DELETE_MAC)                                                               \
	X(w_fwd_win_override, KJUQ_OVERRIDE_WORD_WINDOWS)                                                                  \
	X(w_bck_win_override, KJUQ_OVERRIDE_WORD_WINDOWS)                                                                  \
	X(w_del_win_override, KJUQ_OVERRIDE_WORD_DELETE_WINDOWS)                                                           \
	X(ctrl_tab_override, KJUQ_OVERRIDE_MODDED_ESC)                                                                     \
	X(alt_tab_override, KJUQ_OVERRIDE_MODDED_ESC)                                                                      \
	X(cmd_tab_override, KJUQ_OVERRIDE_MODDED_ESC)                                                                      \
	X(rctrl_tab_override, KJUQ_OVERRIDE_MODDED_ESC)                                                                    \
	X(shift_tab_override, KJUQ_OVERRIDE_MODDED_ESC)                                                                    \
	X(cut_override, KJUQ_OVERRIDE_CUT)                                                                                 \
	X(copy_override, KJUQ_OVERRIDE_COPY)                                                                               \
	X(paste_override, KJUQ_OVERRIDE_PASTE)                                                                             \
	X(jis_s_2_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_6_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_7_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_8_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_9_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_0_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_s_mins_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_eql_override, KJUQ_OVERRIDE_JIS)                                                                           \
	X(jis_s_lbrc_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_rbrc_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_bsls_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_scln_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_quot_override, KJUQ_OVERRIDE_JIS)                                                                          \
	X(jis_s_grv_override, KJUQ_OVERRIDE_JIS)                                                                           \
	X(jis_at_override, KJUQ_OVERRIDE_JIS)                                                                              \
	X(jis_circ_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_ampr_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_astr_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_lprn_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_rprn_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_unds_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_plus_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_lbrc_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_lcbr_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_rbrc_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_rcbr_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_bsls_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_pipe_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_coln_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_quot_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_dquo_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_grv_override, KJUQ_OVERRIDE_JIS)                                                                             \
	X(jis_tild_override, KJUQ_OVERRIDE_JIS)                                                                            \
	X(jis_eql_override, KJUQ_OVERRIDE_JIS)

#define KJUQ_DECLARE_OVERRIDE(override, condition) extern key_override_t override;
KJUQ_OVERRIDE_TABLE(KJUQ_DECLARE_OVERRIDE)
#undef KJUQ_DECLARE_OVERRIDE

bool kjuq_process_override_keycode(uint16_t keycode, keyrecord_t *record);
void kjuq_reload_user_eeprom(void);

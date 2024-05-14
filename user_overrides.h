#pragma once

#include "process_key_override.h"

void user_switch_override(key_override_t *, bool);
void user_switch_jis(bool);
void user_switch_linux_cmd(bool);
void user_enable_all_overrides(void);
void user_disable_all_overrides(void);
void user_enable_word_del_override(void);
void user_disable_word_del_override(void);
void user_toggle_word_del_override(bool);
void user_dump_override_state(void);
void reload_overrides(void);

void user_switch_override(key_override_t *, bool);

void user_switch_jis(bool);
void user_switch_linux_cmd(bool);

void user_enable_all_overrides(void);
void user_disable_all_overrides(void);

void user_enable_word_del_override(void);
void user_disable_word_del_override(void);
void user_toggle_word_del_override(bool);

void user_dump_override_state(void);

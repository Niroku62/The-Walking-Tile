#ifndef M_INCLUDE_GUARD_OS_TERMINAL_H
#define M_INCLUDE_GUARD_OS_TERMINAL_H

#include <stdbool.h>

void os_terminal_set_mode_immediate(bool to_enable);
bool os_terminal_is_key_pressed();
char os_terminal_get_pressed_key();

#endif

#include "aqo/ansi_codes.h"
#include "aqo/os_is_windows.h"

#if M_OS_IS_WINDOWS
#include "windows.h"
#endif

int ansi_codes_enable() {
#if M_OS_IS_WINDOWS
	HANDLE std_output_ptr = GetStdHandle(STD_OUTPUT_HANDLE);
	if (std_output_ptr == INVALID_HANDLE_VALUE) {
		return 1;
	}

	DWORD console_mode = 0;
	if (GetConsoleMode(std_output_ptr, &console_mode) == 0) {
		return 2;
	}

	console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (SetConsoleMode(std_output_ptr, console_mode) == 0) {
		return 3;
	}
#endif

	return 0;
}

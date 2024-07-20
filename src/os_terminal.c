#include "aqo/os_terminal.h"
#include "aqo/os_is_windows.h"

#include <stdio.h>

#if M_OS_IS_WINDOWS
	#include <conio.h>
	#include <windows.h>
#else
	#include <unistd.h>
	#include <termios.h>
	#include <fcntl.h>
	#include <sys/time.h>
#endif

void os_terminal_set_mode_immediate(bool to_enable) {
#if M_OS_IS_WINDOWS
	HANDLE std_input_ptr = GetStdHandle(STD_INPUT_HANDLE);
	DWORD console_mode;
	GetConsoleMode(std_input_ptr, &console_mode);
	if (to_enable) {
		console_mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
		console_mode |= ENABLE_PROCESSED_INPUT;
	} else {
		console_mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	}
	SetConsoleMode(std_input_ptr, console_mode);
#else
	struct termios terminal_io_system;
	tcgetattr(STDIN_FILENO, &terminal_io_system);
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (to_enable) {
		terminal_io_system.c_lflag &= ~(ICANON | ECHO);
		terminal_io_system.c_cc[VMIN] = 1;
		terminal_io_system.c_cc[VTIME] = 0;
		fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	} else {
		terminal_io_system.c_lflag |= (ICANON | ECHO);
		fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal_io_system);
#endif
}

bool os_terminal_is_key_pressed() {
#if M_OS_IS_WINDOWS
	return _kbhit();
#else
	struct timeval time_value = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &time_value) > 0;
#endif
}

char os_terminal_get_pressed_key() {
#if M_OS_IS_WINDOWS
	return _getch();
#else
	return getchar();
#endif
}

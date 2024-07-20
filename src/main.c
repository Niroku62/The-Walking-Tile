#include <stdio.h>
#include "aqo/ansi_codes.h"
#include "aqo/os_is_windows.h"
#include "aqo/os_terminal.h"

int main() {
	char grid[32][32] = {'.'};
	printf("Hello%c\n",grid[10][20]);
	return 0;
}

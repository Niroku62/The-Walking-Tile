#include <stdio.h>
#include <string.h>
#include "aqo/ansi_codes.h"
#include "aqo/os_is_windows.h"
#include "aqo/os_terminal.h"

#define M_PLAY_FIELD_SIZE 64
#define M_AMOUNT_OF_COLUMNS 8
#define M_KEY_ESCAPE VK_ESCAPE

char play_field_tiles[M_PLAY_FIELD_SIZE];
char user_input;

void print_play_field_tiles() {
	for(int i = 1; i <= M_PLAY_FIELD_SIZE; ++i) {
		printf("%c", play_field_tiles[i - 1]);
		if((i % M_AMOUNT_OF_COLUMNS) == 0) {
			puts("");
		}
	}
}

int x_y_to_grid_position(int x, int y, int armount_of_cloumns) {
	return (y * armount_of_cloumns + x);
}

int main() {
	memset(play_field_tiles, '.', 64);
	play_field_tiles[x_y_to_grid_position(3,3, M_AMOUNT_OF_COLUMNS)] = 'A';
	print_play_field_tiles();
	os_terminal_set_mode_immediate(true);

	for(;;) {
		user_input = os_terminal_get_pressed_key();
		printf("%c\n", user_input);
		
		switch(user_input) {
			case 27:
				printf("bye\n");
				break;
		}

		if(user_input == 27) {
			break;
		}
	}
	return 0;
}

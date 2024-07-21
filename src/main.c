#include <stdio.h>
#include <string.h>
#include "aqo/ansi_codes.h"
#include "aqo/os_is_windows.h"
#include "aqo/os_terminal.h"

#define M_PLAY_FIELD_SIZE 64
#define M_COLUMN_COUNT 8

#define M_KEY_ESCAPE 27
#define M_KEY_UP 'w'

void print_play_field_tiles(char * play_field_tiles) {
	for(int i = 0; i < M_PLAY_FIELD_SIZE; ++i) {
		printf("%c", play_field_tiles[i]);
		if(((i + 1) % M_COLUMN_COUNT) == 0) {
			puts("");
		}
	}
}

int x_y_to_grid_position(int x, int y, int armount_of_cloumns) {
	return (y * armount_of_cloumns + x);
}

int main() {
	printf("%d", ansi_codes_enable());
	printf(BGN_GREEN"Hello\n");
	char user_input;
	char play_field_tiles[M_PLAY_FIELD_SIZE];
	memset(play_field_tiles, '.', 64);
	
	play_field_tiles[x_y_to_grid_position(3,3, M_COLUMN_COUNT)] = 'A';
	print_play_field_tiles(play_field_tiles);
	
	os_terminal_set_mode_immediate(true);

	for(;;) {
		if(!os_terminal_is_key_pressed()) {
			continue;
		}
		user_input = os_terminal_get_pressed_key();
		printf("%c\n", user_input);
		
		switch(user_input) {
			case M_KEY_ESCAPE:
				printf("bye\n");
				break;
			case M_KEY_UP:
				printf("key:%c\n", M_KEY_UP);
				break;
		}
		if(user_input == M_KEY_ESCAPE) {
			break;
		}
		printf("%s", CURSOR_SET(0, 0));
		print_play_field_tiles(play_field_tiles);
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aqo/ansi_codes.h"
#include "aqo/os_is_windows.h"
#include "aqo/os_terminal.h"

// play field
#define M_PLAY_FIELD_SIZE 128
#define M_COLUMN_COUNT 16
#define M_BOULDER_AMOUNT 8

// tiles
#define M_PLAY_TILE '.'
#define M_PLAYER_TILE 'A'
#define M_BOULDER_TILE 'O'

// user input
#define M_KEY_ESCAPE 27
#define M_KEY_UP 'w'
#define M_KEY_LEFT 'a'
#define M_KEY_DOWN 's'
#define M_KEY_RIGHT 'd'

void flushInputBuffer() {
	int c;
	 while ((c = getchar()) != '\n' && c != EOF);
}

int generate_random_int(int min, int max) {
	static int seed = 90;
	seed = (seed + 1013904223) * 1664525;
	return seed % (max - min) + min;
}

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

bool does_player_collide_with_boulder(int player_position, int * boulders, int movement) {
	
	for(int i = 0; i < M_BOULDER_AMOUNT; ++i) {
		if(boulders[i] == player_position + movement) {
			return true;
		}
	}
	return false;
}

void move_player(int * player_position_ptr, int player_input, char * play_field_tiles, int * boulders) {
	switch(player_input) {
		
		case M_KEY_UP:
			if(does_player_collide_with_boulder(*player_position_ptr, boulders, -M_COLUMN_COUNT)) {
				break;
			}
			if((*player_position_ptr - M_COLUMN_COUNT) < 0) {
				break;
			}
			play_field_tiles[*player_position_ptr] = M_PLAY_TILE;
			*player_position_ptr -= M_COLUMN_COUNT;
			play_field_tiles[*player_position_ptr] = M_PLAYER_TILE;
			break;

		case M_KEY_LEFT:
			if(does_player_collide_with_boulder(*player_position_ptr, boulders, -1)) {
				break;
			}
			if((*player_position_ptr - 1) < 0) {
				break;
			}
			if(((*player_position_ptr % M_COLUMN_COUNT) - 1) == -1) {
				break;
			}
			play_field_tiles[*player_position_ptr] = M_PLAY_TILE;
			*player_position_ptr -= 1;
			play_field_tiles[*player_position_ptr] = M_PLAYER_TILE;
			break;

		case M_KEY_DOWN:
			if(does_player_collide_with_boulder(*player_position_ptr, boulders, M_COLUMN_COUNT)) {
				break;
			}
			if((*player_position_ptr + M_COLUMN_COUNT) >= M_PLAY_FIELD_SIZE) {
				break;
			}
			play_field_tiles[*player_position_ptr] = M_PLAY_TILE;
			*player_position_ptr += M_COLUMN_COUNT;
			play_field_tiles[*player_position_ptr] = M_PLAYER_TILE;
			break;

		case M_KEY_RIGHT:
			if(does_player_collide_with_boulder(*player_position_ptr, boulders, 1)) {
				break;
			}
			if((*player_position_ptr + 1) >= M_PLAY_FIELD_SIZE) {
				break;
			}
			if(((*player_position_ptr % M_COLUMN_COUNT) + 1) == M_COLUMN_COUNT) {
				break;
			}
			play_field_tiles[*player_position_ptr] = M_PLAY_TILE;
			*player_position_ptr += 1;
			play_field_tiles[*player_position_ptr] = M_PLAYER_TILE;
			break;
	}
}


void select_level(int user_input, int * current_level_ptr, FILE ** selected_level_ptr_ptr) {
	switch(user_input) {
		case 1:
			*selected_level_ptr_ptr = fopen("./dat/level_1.txt", "r+");
			*current_level_ptr = user_input;
			break;
		case 2:
			*selected_level_ptr_ptr = fopen("./dat/level_2.txt", "r+");
			*current_level_ptr = user_input;
			break;
	}
}

void initialize_boulder_positions(int * boulder_positions) {
	if (sizeof(boulder_positions) == 0) {}
	for(int i = 0; i < 10; ++i) {
		
	}
}

void place_boulders(int * boulders, int amount, char * play_field_tiles) {
	for(int i = 0; i < amount; ++i) {
		boulders[i] = generate_random_int(0, M_PLAY_FIELD_SIZE);
		play_field_tiles[boulders[i]] = M_BOULDER_TILE;
	}
}

void render_level(int player);

int main() {
	os_terminal_set_mode_immediate(false);
	ansi_codes_enable();
	printf("%s%s", CLEAR_SCREEN, CURSOR_HIDE);
	
	//play field stuff
	char clear_buffer[M_PLAY_FIELD_SIZE * 8 + 1];
	clear_buffer[M_PLAY_FIELD_SIZE * 8] = '\0';
	memset(clear_buffer, ' ', M_PLAY_FIELD_SIZE * 8);
	for (int i = 0; i < M_PLAY_FIELD_SIZE * 8; i += M_COLUMN_COUNT * 4) {
		clear_buffer[i] = '\n';
	}
	char play_field_tiles[M_PLAY_FIELD_SIZE];
	memset(play_field_tiles, M_PLAY_TILE, M_PLAY_FIELD_SIZE);

	puts("Select your level!\nEnter the level number and hit enter\n\nLevel 1\nLevel 2\n");
	int user_input;
	int current_level_number;
	scanf("%d", &user_input);
	FILE * selected_level;
	select_level(user_input, &current_level_number, &selected_level);
	if(selected_level == NULL) {
		printf("Level couldnt be opened %s", strerror(errno));
		return 1;
	}
	flushInputBuffer();


	
	int fscanf_number = 0;
	fscanf(selected_level, "%d", &fscanf_number);
	printf("scanf number value is: %d\n", fscanf_number);


	//spawn player
	char player_input;
	int player_position = x_y_to_grid_position(0,0, M_COLUMN_COUNT);
	play_field_tiles[player_position] = M_PLAYER_TILE;
	
	//	int boulder_positions[M_PLAY_FIELD_SIZE];
	
	int boulders[M_PLAY_FIELD_SIZE];
	place_boulders(boulders, M_BOULDER_AMOUNT, play_field_tiles);



	os_terminal_set_mode_immediate(true);
	puts("Press any key to start!");

	for(;;) {
		if(!os_terminal_is_key_pressed()) {
			continue;
		}
		player_input = os_terminal_get_pressed_key();

		move_player(&player_position, player_input, play_field_tiles, boulders);
		
		printf("%s%s%s",CURSOR_SET(0, 0), clear_buffer, CURSOR_SET(0, 0));

		print_play_field_tiles(play_field_tiles);

		if(player_input == M_KEY_ESCAPE) {
			printf("%s%s%s",CURSOR_SET(0, 0), clear_buffer, CURSOR_SET(0, 0));
			printf("Thanks for playing!");
			break;
		}

		printf("Player position: %d", player_position);
	}
	return 0;
}

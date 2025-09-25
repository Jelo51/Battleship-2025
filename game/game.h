#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <time.h>
#include <string.h>

void choose_placement(Board *board);
void place_ships_manually(Board *board);
void place_ships_randomly(Board *board);
Position get_player_input(void);
int attack(Board *board, Position pos, int *miss_counter);
int check_victory(Board *board);
void play_game(Board *board);

Position parse_coordinates(const char *input);
char get_orientation_input(void);

#endif
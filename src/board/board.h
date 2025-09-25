#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

#define N 10

typedef struct {
    int cells[N][N];
} Board;

typedef struct {
    int row;
    int col;
}Position;
void init_board(Board *b);
void place_ships_hardcoded(Board *b);
void print_board(const Board *b);
Position get_player_input(void);
int is_part_of_ship(const Board *b, Position p);
void attack(Board *b, Position p);
int check_victory(const Board *b);

#endif

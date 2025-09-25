#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

#define N 10

typedef struct {
    int cells[N][N];
} Board;

void init_board(Board *b);
void place_ships_hardcoded(Board *b);
void print_board(const Board *b);

#endif

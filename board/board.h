#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define NUM_SHIPS 5
#define MAX_MISSES 20

typedef enum {
    CELL_EMPTY,
    CELL_SHIP,
    CELL_HIT,
    CELL_MISS
} CellType;

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    char name[20];
    int size;
} Boat;

typedef struct {
    CellType cells[BOARD_SIZE][BOARD_SIZE];
} Board;

void init_board(Board *board);
int can_place_ship(Board *board, Position start, int size, char orientation);
void place_ship(Board *board, Position start, int size, char orientation);
void print_board(Board *board, int hide_ships);
Boat get_ship_info(int index);

#endif
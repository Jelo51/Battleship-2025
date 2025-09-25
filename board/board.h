#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>

// Enumération pour les types de cellules
typedef enum {
    CELL_EMPTY,
    CELL_SHIP
} CellType;

// Structure représentant le plateau de jeu
typedef struct {
    CellType cells[10][10];
} Board;

// Prototypes des fonctions
void init_board(Board *board);
void place_ships(Board *board);
void print_board(Board *board);

#endif
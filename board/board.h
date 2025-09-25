#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>

// Enumération pour les types de cellules
typedef enum {
    CELL_EMPTY,     // Case vide
    CELL_SHIP,      // Case avec navire
    CELL_HIT,       // Navire touché
    CELL_MISS       // Tir manqué
} CellType;

// Structure représentant le plateau de jeu
typedef struct {
    CellType cells[10][10];
} Board;

// Structure pour une position sur le plateau
typedef struct {
    int row; // 0-9
    int col; // 0-9
} Position;

// Prototypes des fonctions (Palier 1)
void init_board(Board *board);
void place_ships(Board *board);
void print_board(Board *board);

// Prototypes des fonctions (Palier 2)
Position get_player_input();
void attack(Board *board, Position pos);
int check_victory(Board *board);

#endif
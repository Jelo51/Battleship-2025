#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enumeration pour les types de cellules
typedef enum {
    CELL_EMPTY,     // Case vide
    CELL_SHIP,      // Case avec navire
    CELL_HIT,       // Navire touche
    CELL_MISS       // Tir manque
} CellType;

// Structure representant le plateau de jeu
typedef struct {
    CellType cells[10][10];
} Board;

// Structure pour une position sur le plateau
typedef struct {
    int row; // 0-9
    int col; // 0-9
} Position;

// Structure pour les informations d'un navire
typedef struct {
    char name[20];
    int size;
} Ship;

// Prototypes des fonctions (Palier 1)
void init_board(Board *board);
void place_ships(Board *board);
void print_board(Board *board);

// Prototypes des fonctions (Palier 2)
Position get_player_input();
int attack(Board *board, Position pos);
int check_victory(Board *board);

// Prototypes des fonctions (Palier 3)
void place_ships_manually(Board *board);
int place_ship_randomly(Board *board, int ship_size);
void choose_placement(Board *board);
int can_place_ship(Board *board, Position start, int size, char orientation);
void place_ship(Board *board, Position start, int size, char orientation);
Position get_position_input();
char get_orientation_input();

#endif
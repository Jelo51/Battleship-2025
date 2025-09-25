#include "board.h"

// Initialise toutes les cases du plateau à CELL_EMPTY
void init_board(Board *board) {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            board->cells[i][j] = CELL_EMPTY;
        }
    }
}

// Place les 5 navires en dur sur le plateau
void place_ships(Board *board) {
    int i;
    
    // Porte-avions (5 cases) - horizontal en ligne 0, colonnes 0-4
    for (i = 0; i < 5; i++) {
        board->cells[0][i] = CELL_SHIP;
    }
    
    // Croiseur (4 cases) - horizontal en ligne 2, colonnes 2-5
    for (i = 0; i < 4; i++) {
        board->cells[2][2 + i] = CELL_SHIP;
    }
    
    // Destroyer 1 (3 cases) - vertical en colonne 7, lignes 0-2
    for (i = 0; i < 3; i++) {
        board->cells[i][7] = CELL_SHIP;
    }
    
    // Destroyer 2 (3 cases) - horizontal en ligne 5, colonnes 0-2
    for (i = 0; i < 3; i++) {
        board->cells[5][i] = CELL_SHIP;
    }
    
    // Torpilleur (2 cases) - vertical en colonne 9, lignes 8-9
    for (i = 0; i < 2; i++) {
        board->cells[8 + i][9] = CELL_SHIP;
    }
}

// Affiche le plateau avec les coordonnées
void print_board(Board *board) {
    int i, j;
    
    // Affichage de l'en-tête des colonnes (A à J)
    printf("    A   B   C   D   E   F   G   H   I   J\n");
    
    // Affichage des lignes numérotées de 1 à 10
    for (i = 0; i < 10; i++) {
        // Numéro de ligne avec formatage pour l'alignement
        if (i < 9) {
            printf(" %d  ", i + 1);
        } else {
            printf("%d  ", i + 1);
        }
        
        // Affichage des cellules de la ligne
        for (j = 0; j < 10; j++) {
            if (board->cells[i][j] == CELL_SHIP) {
                printf("O");
            } else {
                printf(".");
            }
            
            // Espacement entre les colonnes
            if (j < 9) {
                printf("   ");
            }
        }
        printf("\n");
    }
}

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

    printf("\n=== BATAILLE NAVALE ===\n");

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
            char symbol;
            switch (board->cells[i][j]) {
                case CELL_EMPTY:
                    symbol = '.';
                    break;
                case CELL_SHIP:
                    symbol = 'O';  // Navire visible (pour les tests)
                    break;
                case CELL_HIT:
                    symbol = 'X';  // Navire touché
                    break;
                case CELL_MISS:
                    symbol = '~';  // Tir manqué
                    break;
                default:
                    symbol = '?';
                    break;
            }
            printf("%c", symbol);

            // Espacement entre les colonnes
            if (j < 9) {
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("\nLégende: . = vide, O = navire, X = touché, ~ = manqué\n");
}

// Lit l'entrée du joueur et la convertit en position
Position get_player_input() {
    Position pos;
    char input[10];

    printf("\nEntrez votre attaque (ex: B5) : ");

    // Lecture de l'entrée
    if (scanf("%9s", input) != 1) {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    // Vérification de la longueur minimale
    if (input[0] == '\0' || input[1] == '\0') {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    // Conversion de la colonne (A-J -> 0-9)
    char col_char = input[0];
    if (col_char >= 'A' && col_char <= 'J') {
        pos.col = col_char - 'A';
    } else if (col_char >= 'a' && col_char <= 'j') {
        pos.col = col_char - 'a';
    } else {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    // Conversion de la ligne (1-10 -> 0-9)
    if (input[1] >= '1' && input[1] <= '9' && input[2] == '\0') {
        // Cas 1-9
        pos.row = input[1] - '1';
    } else if (input[1] == '1' && input[2] == '0' && input[3] == '\0') {
        // Cas 10
        pos.row = 9;
    } else {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    return pos;
}

// Traite l'attaque du joueur
void attack(Board *board, Position pos) {
    // Vérification de la validité de la position
    if (pos.row < 0 || pos.row > 9 || pos.col < 0 || pos.col > 9) {
        printf("Entrée invalide ! Utilisez le format A1-J10.\n");
        return;
    }

    // Traitement selon l'état de la case
    switch (board->cells[pos.row][pos.col]) {
        case CELL_SHIP:
            board->cells[pos.row][pos.col] = CELL_HIT;
            printf("Touché !\n");
            break;

        case CELL_EMPTY:
            board->cells[pos.row][pos.col] = CELL_MISS;
            printf("Manqué !\n");
            break;

        case CELL_HIT:
            printf("️Case déjà attaquée ! (Touché précédemment)\n");
            break;

        case CELL_MISS:
            printf("Case déjà attaquée ! (Manqué précédemment)\n");
            break;

        default:
            printf("Erreur inconnue.\n");
            break;
    }
}

// Vérifie si tous les navires sont coulés
int check_victory(Board *board) {
    int i, j;

    // Parcourt tout le plateau
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            // S'il reste au moins un navire intact, pas de victoire
            if (board->cells[i][j] == CELL_SHIP) {
                return 0;
            }
        }
    }

    // Aucun navire intact trouvé = victoire !
    return 1;
}
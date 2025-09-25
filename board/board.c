#include "board.h"

// Tableau des navires du jeu
static Ship ships[] = {
    {"Porte-avions", 5},
    {"Croiseur", 4},
    {"Destroyer 1", 3},
    {"Destroyer 2", 3},
    {"Torpilleur", 2}
};
static int num_ships = 5;

// ==================== FONCTIONS PALIER 1 ====================

// Initialise toutes les cases du plateau a CELL_EMPTY
void init_board(Board *board) {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            board->cells[i][j] = CELL_EMPTY;
        }
    }
}

// Place les 5 navires en dur sur le plateau (version originale)
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

// Affiche le plateau avec les coordonnees
void print_board(Board *board) {
    int i, j;

    printf("\n=== BATAILLE NAVALE ===\n");

    // Affichage de l'en-tete des colonnes (A a J)
    printf("    A   B   C   D   E   F   G   H   I   J\n");

    // Affichage des lignes numerotees de 1 a 10
    for (i = 0; i < 10; i++) {
        // Numero de ligne avec formatage pour l'alignement
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
                    symbol = 'O';  // Navire visible
                    break;
                case CELL_HIT:
                    symbol = 'X';  // Navire touche
                    break;
                case CELL_MISS:
                    symbol = '~';  // Tir manque
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
    printf("\nLegende: . = vide, O = navire, X = touche, ~ = manque\n");
}

// ==================== FONCTIONS PALIER 2 ====================

// Lit l'entree du joueur et la convertit en position
Position get_player_input() {
    Position pos;
    char input[10];

    printf("\nEntrez votre attaque (ex: B5) : ");

    // Lecture de l'entree
    if (scanf("%9s", input) != 1) {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    // Verification de la longueur minimale
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

// Traite l'attaque du joueur - MODIFIEE pour retourner le resultat
int attack(Board *board, Position pos) {
    // Verification de la validite de la position
    if (pos.row < 0 || pos.row > 9 || pos.col < 0 || pos.col > 9) {
        printf("Entree invalide ! Utilisez le format A1-J10.\n");
        return -1; // Erreur d'entree
    }

    // Traitement selon l'etat de la case
    switch (board->cells[pos.row][pos.col]) {
        case CELL_SHIP:
            board->cells[pos.row][pos.col] = CELL_HIT;
            printf("Touche !\n");
            return 1; // Touche

        case CELL_EMPTY:
            board->cells[pos.row][pos.col] = CELL_MISS;
            printf("Manque !\n");
            return 0; // Manque

        case CELL_HIT:
            printf("Case deja attaquee ! (Touche precedemment)\n");
            return -1; // Deja attaquee

        case CELL_MISS:
            printf("Case deja attaquee ! (Manque precedemment)\n");
            return -1; // Deja attaquee

        default:
            printf("Erreur inconnue.\n");
            return -1; // Erreur
    }
}

// Verifie si tous les navires sont coules
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

    // Aucun navire intact trouve = victoire !
    return 1;
}

// ==================== FONCTIONS PALIER 3 ====================

// Lit une position pour le placement de navires
Position get_position_input() {
    Position pos;
    char input[10];

    printf("Position de depart (ex: B3) : ");

    if (scanf("%9s", input) != 1) {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    if (input[0] == '\0' || input[1] == '\0') {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    // Conversion colonne
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

    // Conversion ligne
    if (input[1] >= '1' && input[1] <= '9' && input[2] == '\0') {
        pos.row = input[1] - '1';
    } else if (input[1] == '1' && input[2] == '0' && input[3] == '\0') {
        pos.row = 9;
    } else {
        pos.row = -1;
        pos.col = -1;
        return pos;
    }

    return pos;
}

// Lit l'orientation du navire
char get_orientation_input() {
    char input[10];

    printf("Orientation (H=horizontal, V=vertical) : ");

    if (scanf("%9s", input) != 1) {
        return '\0';
    }

    if (input[0] == 'H' || input[0] == 'h') {
        return 'H';
    } else if (input[0] == 'V' || input[0] == 'v') {
        return 'V';
    } else {
        return '\0';
    }
}

// Verifie si un navire peut etre place a une position donnee
int can_place_ship(Board *board, Position start, int size, char orientation) {
    int i;

    // Verification des limites
    if (orientation == 'H') {
        // Horizontal : verifier que le navire ne depasse pas a droite
        if (start.col + size > 10) {
            return 0;
        }
        // Verifier qu'aucune case n'est occupee
        for (i = 0; i < size; i++) {
            if (board->cells[start.row][start.col + i] != CELL_EMPTY) {
                return 0;
            }
        }
    } else if (orientation == 'V') {
        // Vertical : verifier que le navire ne depasse pas en bas
        if (start.row + size > 10) {
            return 0;
        }
        // Verifier qu'aucune case n'est occupee
        for (i = 0; i < size; i++) {
            if (board->cells[start.row + i][start.col] != CELL_EMPTY) {
                return 0;
            }
        }
    } else {
        return 0; // Orientation invalide
    }

    return 1; // Placement possible
}

// Place un navire sur le plateau
void place_ship(Board *board, Position start, int size, char orientation) {
    int i;

    if (orientation == 'H') {
        // Placement horizontal
        for (i = 0; i < size; i++) {
            board->cells[start.row][start.col + i] = CELL_SHIP;
        }
    } else if (orientation == 'V') {
        // Placement vertical
        for (i = 0; i < size; i++) {
            board->cells[start.row + i][start.col] = CELL_SHIP;
        }
    }
}

// Placement manuel de tous les navires
void place_ships_manually(Board *board) {
    int i;

    printf("\n=== PLACEMENT MANUEL DES NAVIRES ===\n");
    printf("Placez vos navires sur le plateau :\n");

    for (i = 0; i < num_ships; i++) {
        printf("\n--- Placement du %s (%d cases) ---\n", ships[i].name, ships[i].size);

        while (1) {
            print_board(board);

            Position pos = get_position_input();
            if (pos.row == -1 || pos.col == -1) {
                printf("Position invalide ! Recommencez.\n");
                continue;
            }

            char orientation = get_orientation_input();
            if (orientation == '\0') {
                printf("Orientation invalide ! Utilisez H ou V.\n");
                continue;
            }

            if (can_place_ship(board, pos, ships[i].size, orientation)) {
                place_ship(board, pos, ships[i].size, orientation);
                printf("%s place avec succes !\n", ships[i].name);
                break;
            } else {
                printf("Impossible de placer le navire ici ! Verifiez :\n");
                printf("- Le navire ne sort pas du plateau\n");
                printf("- Aucune case n'est deja occupee\n");
            }
        }
    }

    printf("\nTous les navires ont ete places !\n");
}

// Place un navire aleatoirement sur le plateau
int place_ship_randomly(Board *board, int ship_size) {
    int attempts = 0;
    int max_attempts = 100;

    while (attempts < max_attempts) {
        // Choisir position et orientation aleatoires
        Position pos;
        pos.row = rand() % 10;
        pos.col = rand() % 10;

        char orientation = (rand() % 2 == 0) ? 'H' : 'V';

        // Tenter le placement
        if (can_place_ship(board, pos, ship_size, orientation)) {
            place_ship(board, pos, ship_size, orientation);
            return 1; // Succes
        }

        attempts++;
    }

    return 0; // Echec apres tous les essais
}

// Menu de choix du type de placement
void choose_placement(Board *board) {
    int choice;

    printf("\n=== CHOIX DU PLACEMENT ===\n");
    printf("1 - Placement manuel\n");
    printf("2 - Placement aleatoire\n");
    printf("Votre choix (1 ou 2) : ");

    if (scanf("%d", &choice) != 1) {
        printf("Erreur de saisie. Placement aleatoire par defaut.\n");
        choice = 2;
    }

    if (choice == 1) {
        place_ships_manually(board);
    } else {
        printf("\n=== PLACEMENT ALEATOIRE ===\n");
        printf("Placement automatique des navires en cours...\n");

        // Initialiser le generateur aleatoire
        srand((unsigned int)time(NULL));

        int i;
        for (i = 0; i < num_ships; i++) {
            if (place_ship_randomly(board, ships[i].size)) {
                printf("%s place automatiquement.\n", ships[i].name);
            } else {
                printf("Erreur: impossible de placer %s aleatoirement.\n", ships[i].name);
                printf("Tentative de placement manuel...\n");
                // En cas d'echec, demander placement manuel pour ce navire
                printf("\n--- Placement manuel du %s (%d cases) ---\n", ships[i].name, ships[i].size);

                while (1) {
                    print_board(board);
                    Position pos = get_position_input();
                    if (pos.row == -1 || pos.col == -1) {
                        printf("Position invalide ! Recommencez.\n");
                        continue;
                    }

                    char orientation = get_orientation_input();
                    if (orientation == '\0') {
                        printf("Orientation invalide ! Utilisez H ou V.\n");
                        continue;
                    }

                    if (can_place_ship(board, pos, ships[i].size, orientation)) {
                        place_ship(board, pos, ships[i].size, orientation);
                        printf("%s place manuellement !\n", ships[i].name);
                        break;
                    } else {
                        printf("Placement impossible ici !\n");
                    }
                }
            }
        }

        printf("Tous les navires ont ete places !\n");
    }
}
#include "game.h"

Position parse_coordinates(const char *input) {
    Position pos;
    pos.row = -1;
    pos.col = -1;

    if (strlen(input) < 2) {
        return pos;
    }

    char col_char = input[0];
    if (col_char >= 'A' && col_char <= 'J') {
        pos.col = col_char - 'A';
    } else if (col_char >= 'a' && col_char <= 'j') {
        pos.col = col_char - 'a';
    } else {
        return pos;
    }

    if (input[1] >= '1' && input[1] <= '9' && input[2] == '\0') {
        pos.row = input[1] - '1';
    } else if (input[1] == '1' && input[2] == '0' && input[3] == '\0') {
        pos.row = 9;
    } else {
        pos.row = -1;
        pos.col = -1;
    }

    return pos;
}

char get_orientation_input(void) {
    char input[10];

    printf("Orientation (H=horizontal, V=vertical) : ");
    if (scanf("%9s", input) != 1) {
        return '\0';
    }

    if (input[0] == 'H' || input[0] == 'h') {
        return 'H';
    } else if (input[0] == 'V' || input[0] == 'v') {
        return 'V';
    }

    return '\0';
}

void choose_placement(Board *board) {
    int choice;

    printf("\n=== PLACEMENT DES NAVIRES ===\n");
    printf("1 - Placement manuel\n");
    printf("2 - Placement aleatoire\n");
    printf("Votre choix (1 ou 2) : ");

    if (scanf("%d", &choice) != 1) {
        choice = 2;
    }

    if (choice == 1) {
        place_ships_manually(board);
    } else {
        place_ships_randomly(board);
    }
}

void place_ships_manually(Board *board) {
    int i;
    char input[10];

    printf("\n=== PLACEMENT MANUEL ===\n");

    for (i = 0; i < NUM_SHIPS; i++) {
        Boat current_ship = get_ship_info(i);

        printf("\n--- Placement du %s (%d cases) ---\n",
               current_ship.name, current_ship.size);

        while (1) {
            print_board(board, 0);

            printf("Position de depart (ex: B3) : ");
            if (scanf("%9s", input) != 1) {
                printf("Erreur de saisie.\n");
                continue;
            }

            Position pos = parse_coordinates(input);
            if (pos.row == -1) {
                printf("Position invalide. Utilisez le format A1-J10.\n");
                continue;
            }

            char orientation = get_orientation_input();
            if (orientation == '\0') {
                printf("Orientation invalide. Utilisez H ou V.\n");
                continue;
            }

            if (can_place_ship(board, pos, current_ship.size, orientation)) {
                place_ship(board, pos, current_ship.size, orientation);
                printf("%s place avec succes !\n", current_ship.name);
                break;
            } else {
                printf("Placement impossible ici !\n");
                printf("Verifiez que le navire ne sort pas du plateau\n");
                printf("et qu'aucune case n'est deja occupee.\n");
            }
        }
    }

    printf("\nTous les navires ont ete places !\n");
}

void place_ships_randomly(Board *board) {
    int i, attempts, max_attempts = 1000;

    printf("\n=== PLACEMENT ALEATOIRE ===\n");
    srand((unsigned int)time(NULL));

    for (i = 0; i < NUM_SHIPS; i++) {
        Boat current_ship = get_ship_info(i);
        attempts = 0;

        printf("Placement du %s...", current_ship.name);

        while (attempts < max_attempts) {
            Position pos;
            pos.row = rand() % BOARD_SIZE;
            pos.col = rand() % BOARD_SIZE;

            char orientation = (rand() % 2 == 0) ? 'H' : 'V';

            if (can_place_ship(board, pos, current_ship.size, orientation)) {
                place_ship(board, pos, current_ship.size, orientation);
                printf(" OK\n");
                break;
            }

            attempts++;
        }

        if (attempts >= max_attempts) {
            printf(" ECHEC\n");
            printf("Impossible de placer automatiquement %s.\n", current_ship.name);
            printf("Veuillez relancer le programme.\n");
            exit(1);
        }
    }

    printf("Placement aleatoire termine !\n");
}

Position get_player_input(void) {
    char input[10];

    printf("\nEntrez vos coordonnees d'attaque (ex: B5) : ");
    if (scanf("%9s", input) != 1) {
        Position invalid = {-1, -1};
        return invalid;
    }

    return parse_coordinates(input);
}

int attack(Board *board, Position pos, int *miss_counter) {
    if (pos.row < 0 || pos.row >= BOARD_SIZE ||
        pos.col < 0 || pos.col >= BOARD_SIZE) {
        printf("Coordonnees invalides !\n");
        return -1;
    }

    switch (board->cells[pos.row][pos.col]) {
        case CELL_SHIP:
            board->cells[pos.row][pos.col] = CELL_HIT;
            printf("TOUCHE !\n");
            return 1;

        case CELL_EMPTY:
            board->cells[pos.row][pos.col] = CELL_MISS;
            printf("Dans l'eau...\n");
            (*miss_counter)++;
            return 0;

        case CELL_HIT:
        case CELL_MISS:
            printf("Vous avez deja tire ici !\n");
            return -1;

        default:
            return -1;
    }
}

int check_victory(Board *board) {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->cells[i][j] == CELL_SHIP) {
                return 0;
            }
        }
    }

    return 1;
}

void play_game(Board *board) {
    int miss_counter = 0;
    int total_shots = 0;

    printf("\n=== DEBUT DE LA PARTIE ===\n");
    printf("Les navires sont maintenant caches !\n");
    printf("Vous avez droit a %d tirs rates maximum.\n", MAX_MISSES);

    while (1) {
        print_board(board, 1);
        printf("\nTirs rates : %d/%d | Tirs total : %d\n",
               miss_counter, MAX_MISSES, total_shots);

        Position pos = get_player_input();
        if (pos.row == -1) {
            printf("Coordonnees invalides ! Recommencez.\n");
            continue;
        }

        int result = attack(board, pos, &miss_counter);

        if (result >= 0) {
            total_shots++;
        }

        if (check_victory(board)) {
            print_board(board, 1);
            printf("\n*** VICTOIRE ! ***\n");
            printf("Tous les navires ennemis ont ete coules !\n");
            printf("Statistiques : %d tirs rates, %d tirs total\n",
                   miss_counter, total_shots);
            break;
        }

        if (miss_counter >= MAX_MISSES) {
            print_board(board, 1);
            printf("\n*** VOUS AVEZ PERDU ! ***\n");
            printf("Vous avez depasse la limite de %d tirs rates.\n", MAX_MISSES);
            printf("Il restait encore des navires sur le plateau.\n");
            break;
        }
    }
}

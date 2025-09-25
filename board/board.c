#include "board.h"

static Boat ships[NUM_SHIPS] = {
    {"Porte-avions", 5},
    {"Croiseur", 4},
    {"Destroyer-1", 3},
    {"Destroyer-2", 3},
    {"Torpilleur", 2}
};

void init_board(Board *board) {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board->cells[i][j] = CELL_EMPTY;
        }
    }
}

int can_place_ship(Board *board, Position start, int size, char orientation) {
    int i;

    if (orientation == 'H' || orientation == 'h') {
        if (start.col + size > BOARD_SIZE) {
            return 0;
        }
        for (i = 0; i < size; i++) {
            if (board->cells[start.row][start.col + i] != CELL_EMPTY) {
                return 0;
            }
        }
    } else if (orientation == 'V' || orientation == 'v') {
        if (start.row + size > BOARD_SIZE) {
            return 0;
        }
        for (i = 0; i < size; i++) {
            if (board->cells[start.row + i][start.col] != CELL_EMPTY) {
                return 0;
            }
        }
    } else {
        return 0;
    }

    return 1;
}

void place_ship(Board *board, Position start, int size, char orientation) {
    int i;

    if (orientation == 'H' || orientation == 'h') {
        for (i = 0; i < size; i++) {
            board->cells[start.row][start.col + i] = CELL_SHIP;
        }
    } else if (orientation == 'V' || orientation == 'v') {
        for (i = 0; i < size; i++) {
            board->cells[start.row + i][start.col] = CELL_SHIP;
        }
    }
}

void print_board(Board *board, int hide_ships) {
    int i, j;

    printf("\n    A   B   C   D   E   F   G   H   I   J\n");

    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%2d  ", i + 1);

        for (j = 0; j < BOARD_SIZE; j++) {
            char symbol;

            switch (board->cells[i][j]) {
                case CELL_EMPTY:
                    symbol = '.';
                    break;
                case CELL_SHIP:
                    symbol = hide_ships ? '.' : 'O';
                    break;
                case CELL_HIT:
                    symbol = 'X';
                    break;
                case CELL_MISS:
                    symbol = '~';
                    break;
                default:
                    symbol = '?';
                    break;
            }

            printf("%c", symbol);
            if (j < BOARD_SIZE - 1) {
                printf("   ");
            }
        }
        printf("\n");
    }

    if (hide_ships) {
        printf("\nLegende: . = inconnu, X = touche, ~ = manque\n");
    } else {
        printf("\nLegende: . = vide, O = navire, X = touche, ~ = manque\n");
    }
}

Boat get_ship_info(int index) {
    if (index >= 0 && index < NUM_SHIPS) {
        return ships[index];
    }
    Boat empty = {"", 0};
    return empty;
}
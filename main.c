#include "board/board.h"
#include "game/game.h"

int main(void) {
    Board board;

    printf("=== BATTLESHIP-2025 ===\n");
    printf("Bienvenue dans la bataille navale !\n");

    init_board(&board);

    choose_placement(&board);

    play_game(&board);

    printf("\nMerci d'avoir joue a Battleship-2025 !\n");

    return 0;
}



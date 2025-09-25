#include "board/board.h"

int main() {
    Board board;

    init_board(&board);
    place_ships(&board);
    print_board(&board);

    return 0;
}
//

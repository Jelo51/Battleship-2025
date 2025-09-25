#include <stdio.h>
#include "board/board.h"

int main(void){
    Board b;
    init_board(&b);
    place_ships_hardcoded(&b);
    print_board(&b);
    return 0;
}

#include <stdio.h>
#include "board/board.h"

int main(void){
    Board b;
    init_board(&b);
    place_ships_hardcoded(&b);
    print_board(&b);
    while(1){
        Position p = get_player_input();
        if(p.row < 0) break;
        attack(&b, p);
        print_board(&b);
        if(check_victory(&b)){
            printf("Victory\n");
            break;
        }
    }
    return 0;
}

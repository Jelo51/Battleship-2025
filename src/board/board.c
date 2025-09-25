#include "board.h"
#include <stdio.h>

void init_board(Board *b){
    for(int r=0;r<N;r++) for(int c=0;c<N;c++) b->cells[r][c]=0;
}

void place_ships_hardcoded(Board *b){
    for(int c=0;c<=4;c++) b->cells[0][c]=1;
    for(int r=1;r<=4;r++) b->cells[r][9]=1;
    for(int c=2;c<=4;c++) b->cells[5][c]=1;
    for(int r=7;r<=9;r++) b->cells[r][6]=1;
    for(int c=7;c<=8;c++) b->cells[3][c]=1;
}

void print_board(const Board *b){
    printf("   ");
    for(int c=0;c<N;c++) printf(" %c",'A'+c);
    printf("\n");
    for(int r=0;r<N;r++){
        printf("%2d ", r+1);
        for(int c=0;c<N;c++) printf(" %c", b->cells[r][c] ? 'O' : '.');
        printf("\n");
    }
}

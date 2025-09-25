#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
        for(int c=0;c<N;c++){
            char ch = '.';
            if(b->cells[r][c] == 3) ch = 'X';
            else if(b->cells[r][c] == 2) ch = 'o';
            else ch = '.';
            printf(" %c", ch);
        }
        printf("\n");
    }
}
static void trim_newline(char *s){
    size_t l=strlen(s);
    while(l>0 && (s[l-1]=='\n' || s[l-1]=='\r')){ s[--l]=0; }
}

Position get_player_input(void){
    char buf[64];
    Position p;
    for(;;){
        if(!fgets(buf, sizeof buf, stdin)) { p.row = -1; p.col = -1; return p; }
        trim_newline(buf);
        if(strlen(buf)==0) continue;
        int i=0;
        while(buf[i] && isspace((unsigned char)buf[i])) i++;
        if(!buf[i]) continue;
        char colc = toupper((unsigned char)buf[i]);
        if(colc < 'A' || colc > 'J') continue;
        int col = colc - 'A';
        i++;
        while(buf[i] && isspace((unsigned char)buf[i])) i++;
        int row = atoi(&buf[i]);
        if(row < 1 || row > 10) continue;
        p.row = row - 1;
        p.col = col;
        return p;
    }
}

int is_part_of_ship(const Board *b, Position p){
    if(p.row < 0 || p.row >= N || p.col < 0 || p.col >= N) return 0;
    return b->cells[p.row][p.col] == 1;
}

void attack(Board *b, Position p){
    if(p.row < 0 || p.row >= N || p.col < 0 || p.col >= N){ printf("Out of bounds\n"); return; }
    int v = b->cells[p.row][p.col];
    if(v == 1){
        b->cells[p.row][p.col] = 3;
        printf("Hit\n");
    } else if(v == 0){
        b->cells[p.row][p.col] = 2;
        printf("Miss\n");
    } else if(v == 2 || v == 3){
        printf("Already\n");
    } else {
        printf("Miss\n");
    }
}

int check_victory(const Board *b){
    for(int r=0;r<N;r++) for(int c=0;c<N;c++) if(b->cells[r][c]==1) return 0;
    return 1;
}
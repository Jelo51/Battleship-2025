#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdbio.h>
#include <stdint.h>




typedef struct Position {
    int x;
    int y;
} Position;

typedef enum BoatOrientation {
    BOAT_HORIZONTAL,
    BOAT_VERTICAL
} BoatOrientation;

typedef struct Boat {
    Position position;
    int length;
    int orientation;
    int hit;
    int sunk;
} Boat;

#endif

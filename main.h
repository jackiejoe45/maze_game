#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define MAP_SCALE 4

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];
extern double posX, posY, dirX, dirY, planeX, planeY;
extern const double MOVE_SPEED;
extern const double ROT_SPEED;

void movePlayer(int direction);
void rotateCamera(int direction);
void drawMap(SDL_Renderer *renderer, bool showMap);
int loadMap(const char *filename);

#endif // MAIN_H

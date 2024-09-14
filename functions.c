#include "main.h"

void movePlayer(int direction) {
    double moveX = dirX * MOVE_SPEED;
    double moveY = dirY * MOVE_SPEED;
    
    if (direction == 1 || direction == -1) { // Forward or Backward
        double newPosX = posX + moveX * direction;
        double newPosY = posY + moveY * direction;
        
        if(worldMap[(int)newPosX][(int)posY] == 0) posX = newPosX;
        if(worldMap[(int)posX][(int)newPosY] == 0) posY = newPosY;
    }
    if (direction == 2 || direction == -2) { // Strafe Right or Left
        double strafeX = -dirY * MOVE_SPEED * (direction / 2);
        double strafeY = dirX * MOVE_SPEED * (direction / 2);
        
        double newPosX = posX + strafeX;
        double newPosY = posY + strafeY;
        
        if(worldMap[(int)newPosX][(int)posY] == 0) posX = newPosX;
        if(worldMap[(int)posX][(int)newPosY] == 0) posY = newPosY;
    }
}

void rotateCamera(int direction) {
    double oldDirX = dirX;
    double oldPlaneX = planeX;
    
    if (direction == 1) { // Right rotation
        dirX = dirX * cos(-ROT_SPEED) - dirY * sin(-ROT_SPEED);
        dirY = oldDirX * sin(-ROT_SPEED) + dirY * cos(-ROT_SPEED);
        planeX = planeX * cos(-ROT_SPEED) - planeY * sin(-ROT_SPEED);
        planeY = oldPlaneX * sin(-ROT_SPEED) + planeY * cos(-ROT_SPEED);
    }
    if (direction == -1) { // Left rotation
        dirX = dirX * cos(ROT_SPEED) - dirY * sin(ROT_SPEED);
        dirY = oldDirX * sin(ROT_SPEED) + dirY * cos(ROT_SPEED);
        planeX = planeX * cos(ROT_SPEED) - planeY * sin(ROT_SPEED);
        planeY = oldPlaneX * sin(ROT_SPEED) + planeY * cos(ROT_SPEED);
    }
}

void drawMap(SDL_Renderer *renderer, bool showMap) {
    if (!showMap) return;

    int mapOffsetX = SCREEN_WIDTH - (MAP_WIDTH * MAP_SCALE) - 10;
    int mapOffsetY = 10;

    // Draw map cells
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect mapRect = {
                mapOffsetX + x * MAP_SCALE,
                mapOffsetY + y * MAP_SCALE,
                MAP_SCALE,
                MAP_SCALE
            };
            if (worldMap[x][y] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            SDL_RenderFillRect(renderer, &mapRect);
        }
    }

    // Draw player position
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect playerRect = {
        mapOffsetX + (int)(posX * MAP_SCALE) - 1,
        mapOffsetY + (int)(posY * MAP_SCALE) - 1,
        3,
        3
    };
    SDL_RenderFillRect(renderer, &playerRect);

    // Draw player's line of sight
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
        mapOffsetX + (int)(posX * MAP_SCALE),
        mapOffsetY + (int)(posY * MAP_SCALE),
        mapOffsetX + (int)((posX + dirX) * MAP_SCALE),
        mapOffsetY + (int)((posY + dirY) * MAP_SCALE)
    );
}

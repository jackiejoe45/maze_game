#include "main.h"

void movePlayer(int direction, double speed) {
    double moveX = dirX * speed;
    double moveY = dirY * speed;
    
    if (direction == 1 || direction == -1) { // Forward or Backward
        double newPosX = posX + moveX * direction;
        double newPosY = posY + moveY * direction;
        
        if(worldMap[(int)newPosX][(int)posY] == 0) posX = newPosX;
        if(worldMap[(int)posX][(int)newPosY] == 0) posY = newPosY;
    }
    if (direction == 2 || direction == -2) { // Strafe Right or Left
        double strafeX = -dirY * speed * (direction / 2);
        double strafeY = dirX * speed * (direction / 2);
        
        double newPosX = posX + strafeX;
        double newPosY = posY + strafeY;
        
        if(worldMap[(int)newPosX][(int)posY] == 0) posX = newPosX;
        if(worldMap[(int)posX][(int)newPosY] == 0) posY = newPosY;
    }
}

void rotateCamera(int direction, double speed) {
    double oldDirX = dirX;
    double oldPlaneX = planeX;
    
    if (direction == 1) { // Right rotation
        dirX = dirX * cos(-speed) - dirY * sin(-speed);
        dirY = oldDirX * sin(-speed) + dirY * cos(-speed);
        planeX = planeX * cos(-speed) - planeY * sin(-speed);
        planeY = oldPlaneX * sin(-speed) + planeY * cos(-speed);
    }
    if (direction == -1) { // Left rotation
        dirX = dirX * cos(speed) - dirY * sin(speed);
        dirY = oldDirX * sin(speed) + dirY * cos(speed);
        planeX = planeX * cos(speed) - planeY * sin(speed);
        planeY = oldPlaneX * sin(speed) + planeY * cos(speed);
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

int loadMap(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    char line[MAP_WIDTH + 2];  // +2 for newline and null terminator
    int y = 0;

    while (fgets(line, sizeof(line), file) && y < MAP_HEIGHT) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (line[x] == '#') {
                worldMap[x][y] = 1;  // Wall
            } else if (line[x] == '.') {
                worldMap[x][y] = 0;  // Empty space
            } else {
                printf("Invalid character in map file: %c\n", line[x]);
                fclose(file);
                return 0;
            }
        }
        y++;
    }

    fclose(file);
    return 1;
}
SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_LoadBMP(file);
    if (surface == NULL) {
        printf("Error loading texture file '%s': %s\n", file, SDL_GetError());
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Error creating texture from '%s': %s\n", file, SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    
    SDL_FreeSurface(surface);
    return texture;
}

#include "main.h"

double posX = 4, posY = 4;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;

const double MOVE_SPEED = 0.05;
const double ROT_SPEED = 0.03;

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {0};  // Initialize to 0

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    if (!loadMap(argv[1])) {
        printf("Failed to load map file.\n");
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    bool showMap = true;

    bool moveForward = false, moveBackward = false, strafeLeft = false, strafeRight = false, rotateLeft = false, rotateRight = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w: moveForward = true; break;
                    case SDLK_s: moveBackward = true; break;
                    case SDLK_a: strafeLeft = true; break;
                    case SDLK_d: strafeRight = true; break;
                    case SDLK_LEFT: rotateLeft = true; break;
                    case SDLK_RIGHT: rotateRight = true; break;
                    case SDLK_m: showMap = !showMap; break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_w: moveForward = false; break;
                    case SDLK_s: moveBackward = false; break;
                    case SDLK_a: strafeLeft = false; break;
                    case SDLK_d: strafeRight = false; break;
                    case SDLK_LEFT: rotateLeft = false; break;
                    case SDLK_RIGHT: rotateRight = false; break;
                }
            }
        }

        // Handle multi-directional movement
        if (moveForward && !moveBackward) movePlayer(1);
        if (moveBackward && !moveForward) movePlayer(-1);
        if (strafeRight && !strafeLeft) movePlayer(2);
        if (strafeLeft && !strafeRight) movePlayer(-2);
        if (rotateRight && !rotateLeft) rotateCamera(1);
        if (rotateLeft && !rotateRight) rotateCamera(-1);

        SDL_SetRenderDrawColor(renderer, 86, 171, 0, 255);
        SDL_RenderClear(renderer);

        for(int x = 0; x < SCREEN_WIDTH; x++) {
            double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            
            int mapX = (int)posX;
            int mapY = (int)posY;

            double sideDistX, sideDistY;

            double deltaDistX = fabs(1 / rayDirX);
            double deltaDistY = fabs(1 / rayDirY);
            double perpWallDist;

            int stepX, stepY;
            int hit = 0;
            int side;

            if(rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if(rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            while (hit == 0) {
                if(sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if(worldMap[mapX][mapY] > 0) hit = 1;
            }

            if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if(drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

            if (side == 0) {
                SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);  // Red for EAST-WEST walls
            } else {
                SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);  // Blue for NORTH-SOUTH walls
            }

            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
        }

        drawMap(renderer, showMap);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

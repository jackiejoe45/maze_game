# Maze Game Project
## A portfolio project

This is a simple maze game implemented in C using the SDL2 library. The game features a raycasting engine to render a 3D-like environment from a 2D map.

### Features

- 3D-like rendering using raycasting
- Collision detection with walls
- Mini-map display (toggle with 'M' key)
- Load custom maps from files
- Multi-directional movement and rotation

### Dependencies

- SDL2 library
- C compiler (e.g., gcc)

### How to compile

Run the following command in the project directory:

```
gcc main.c functions.c -o maze_game -lSDL2 -lm
```

### How to run

To run the game, use the following command:

```
./maze_game path/to/map_file.txt
```

Replace `path/to/map_file.txt` with the path to your map file.

### Map file format

The map file should be a text file

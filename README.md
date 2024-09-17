# Maze Game Project

## Introduction

Maze Game is an exciting 3D-like maze exploration game implemented in C using the SDL2 library. This project showcases the power of raycasting techniques to create immersive environments from simple 2D maps.

[Visit the deployed site](https://your-maze-game-url.com) | [Read the project blog article](https://hashnode.com/edit/cm16lbnk8001008jqfc5v2gn9)

**Author:** [Your Name](https://www.linkedin.com/in/abdul-ben-charles)

![Maze Game Screenshot](https://github.com/jackiejoe45/maze_game/blob/main/maze_game_logo.png)
![Maze Game Screenshot](https://github.com/jackiejoe45/maze_game/blob/main/maze_game_gameplay.png)


## Features

- 3D-like rendering using raycasting
- Collision detection with walls
- Mini-map display (toggle with 'M' key)
- Custom map loading from files
- Multi-directional movement and rotation
- Textured walls
- Sky and ground rendering

## Installation

1. Ensure you have the SDL2 library installed on your system.
2. Clone this repository:
   ```
   git clone https://github.com/your-username/maze-game.git
   cd maze-game
   ```
3. Compile the game:
   ```
   gcc main.c functions.c -o maze_game -lSDL2 -lm
   ```

## Usage

Run the game with a map file:

```
./maze_game path/to/map_file.txt
```

Replace `path/to/map_file.txt` with the path to your map file.

### Controls

- W: Move forward
- S: Move backwards
- A: Strafe left
- D: Strafe right
- Left Arrow: Rotate camera left
- Right Arrow: Rotate camera right
- M: Toggle mini-map display

### Map File Format

Create custom maps using the following format:
- Use '#' for walls
- Use '.' for empty spaces
- Ensure the map is rectangular
- Include at least one valid path through the maze

Example:
```
############
#..........#
#.##.#####.#
#.#....#...#
#.#.##.#.#.#
#.#.#....#.#
#...######.#
############
```

### Textures

Place a 64x64 pixel BMP file named "wall_texture.bmp" in the game directory for wall textures.

## Contributing

We welcome contributions to the Maze Game Project! Here's how you can help:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- [SDL2 Library](https://www.libsdl.org/) for providing the graphics framework
- [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) for inspiration and techniques

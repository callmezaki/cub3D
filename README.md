# cub3D

## Description

Cub3D is a project that involves creating a 3D game using the raycasting technique, inspired by the classic game Wolfenstein 3D. This project is part of the 42 curriculum and aims to enhance understanding of graphics programming, game development, and efficient rendering techniques.

## Features

- 3D rendering using raycasting
- Texture mapping
- Basic game mechanics
- Efficient rendering with minimal performance overhead

## Getting Started

### Prerequisites

- GCC or any C compiler
- Make
- MinilibX (provided by the 42 curriculum)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/callmezaki/cub3D.git
   cd cub3D
   ```

2. Compile the project:

   ```bash
   make
   ```

### Usage

Run the game with the following command:

```bash
./cub3D <map_file>
```

- `map_file`: Path to the configuration file that defines the game map.

Example:

```bash
./cub3D maps/map.cub
```

## Project Structure

- `src/`: Contains the source files.
- `maps/`: Contains example map files.
- `textures/`: Contains texture files.
- `Makefile`: Defines the build process for the project.
- `README.md`: Project documentation.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [42 School](https://42.fr/en/homepage/) for providing the project framework.
- The 42 community for their support and collaboration.

*This project was created as part of the 42 curriculum by kqueiroz and loda-sil.*

---

## Description

**cub3D** is a first-person 3D raycasting project written in C with MiniLibX.
It parses a `.cub` configuration file, validates the map and resources, renders
textured walls in real time, and displays a minimap overlay.

The current implementation includes:
- DDA-based raycasting
- Textured wall rendering (`NO`, `SO`, `WE`, `EA`)
- Floor and ceiling RGB colors
- Keyboard movement and camera rotation
- Minimap + player direction indicator
- Map validation (characters, single spawn, closed map)

---

## Build and Run

### Requirements

- GCC or compatible C compiler
- `make`
- Linux with X11 libraries (`libx11`, `libxext`, `zlib`, `libm`)
- MiniLibX Linux version (already vendored in `libs/minilibx`)

### Compile

```bash
make
```

### Run

```bash
./cub3D maps/simple.cub
```

### Clean

```bash
make clean
make fclean
make re
```

### Valgrind target

```bash
make valgrind ARGS="maps/simple.cub"
```

> Note: the Makefile valgrind rule references `valgrind.supp`.

---

## Controls

- `W` / `S`: move forward / backward
- `A` / `D`: strafe
- `Left Arrow` / `Right Arrow`: rotate camera
- `ESC`: exit

---

## `.cub` File Format (as implemented)

A valid file must provide:
1. Texture paths:
   - `NO path_to_north_texture`
   - `SO path_to_south_texture`
   - `WE path_to_west_texture`
   - `EA path_to_east_texture`
2. Colors:
   - `F r,g,b`
   - `C r,g,b`  
   where each color component is in `[0, 255]`.
3. A map block at the end of the file.

Valid map characters:
- `1` wall
- `0` walkable tile
- `N`, `S`, `E`, `W` player spawn (exactly one)
- space (` `) as map padding/outside area

Example:

```text
NO srcs/assets/bricks_1.xpm
SO srcs/assets/bricks_1.xpm
WE srcs/assets/bricks_1.xpm
EA srcs/assets/bricks_1.xpm

F 220,100,0
C 225,30,0

111111
10N001
100001
111111
```

---

## Project Structure

```text
.
├── inc/
│   └── cub3d.h
├── libs/
│   ├── libft/
│   └── minilibx/
├── maps/
│   ├── simple.cub
│   └── valid_map_test.cub
├── srcs/
│   ├── main.c
│   ├── cub3d_utils.c
│   ├── cleanup_game.c
│   ├── controls/
│   │   ├── hooks.c
│   │   ├── movement.c
│   │   └── minimap.c
│   ├── parse/
│   │   ├── parse_file.c
│   │   ├── parse_map.c
│   │   ├── parse_utils.c
│   │   ├── player_spawn.c
│   │   ├── validate_map.c
│   │   └── validate_tex.c
│   └── render/
│       ├── render_3d.c
│       ├── render_walls.c
│       ├── ray_init.c
│       ├── ray_dda.c
│       ├── ray_project.c
│       └── texture_load.c
└── Makefile
```

---

## Rendering Pipeline

```text
.cub file
  -> parse elements (textures/colors)
  -> parse map
  -> validate map and spawn
  -> game loop
  -> movement update
  -> ray init + DDA
  -> wall projection + texture sampling
  -> frame draw + minimap overlay
```

---

## Resources

- [Ray Casting](https://en.wikipedia.org/wiki/Ray_casting)
- [DDA line traversal concept](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [MiniLibX (42 Linux)](https://github.com/42Paris/minilibx-linux)
- [XPM format](https://en.wikipedia.org/wiki/X_PixMap)

---

## AI Usage

AI assistance was used for:
1. debugging and edge-case analysis (raycasting/minimap integration),
2. refactoring for Norminette compliance,
3. improving naming/readability suggestions,
4. README and project documentation updates.

---

## Authors

- **kqueiroz**
- **loda-sil**

---

## License

This project is part of the 42 School educational curriculum.

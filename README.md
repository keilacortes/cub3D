<div align="center">
  <img width="150" height="150" alt="cub3dm" src="https://github.com/user-attachments/assets/4e4ef239-d792-4577-abf4-60c041a861d8" />
</div>

# 👾 Cub3D 👾

> *This project was created as part of the 42 curriculum by **kqueiroz** and **loda-sil**.*

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42sp](https://img.shields.io/badge/42sp-000000?style=for-the-badge&logo=42&logoColor=white)

---

## Description

**cub3D** is a first-person raycasting project in C using MiniLibX (Linux).
It parses a `.cub` file, validates map/resources, renders textured walls, and
draws a minimap overlay.

Current implementation highlights:
- DDA raycasting (`ray_init.c`, `ray_dda.c`, `ray_project.c`)
- Textured walls (`NO`, `SO`, `WE`, `EA`)
- Floor and ceiling RGB colors (`F`, `C`)
- Strict parser checks (missing/duplicate elements, malformed colors, unknown identifiers)
- Map validation (allowed chars, single spawn, closed map, irregular line safety)
- Continuous render loop with minimap + player direction
- Frame-time scaled movement/rotation (`get_frame_scale`) to avoid FPS-dependent speed
- Clean shutdown on `ESC` and window close

---

## Build and Run

### Requirements

- GCC (or compatible C compiler)
- `make`
- Linux with X11 libraries (`libx11`, `libxext`, `zlib`, `libm`)
- MiniLibX Linux (vendored in `libs/minilibx`)

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

### Valgrind target (Makefile)

```bash
make valgrind ARGS="maps/simple.cub"
```

---

## Controls

- `W` / `S`: move forward / backward
- `A` / `D`: strafe left / right
- `Left Arrow` / `Right Arrow`: rotate camera
- `ESC`: exit

---

## `.cub` Format (as implemented)

A valid file must provide:
1. Texture paths (exactly once each):
   - `NO path_to_north_texture`
   - `SO path_to_south_texture`
   - `WE path_to_west_texture`
   - `EA path_to_east_texture`
2. Colors (exactly once each):
   - `F r,g,b`
   - `C r,g,b`
3. A map block at the end of the file.

Parser rules currently enforced:
- Color format must contain exactly 2 commas and 3 numeric components.
- Color values must be in `[0, 255]`.
- Unknown non-map identifiers are rejected.
- Duplicate texture/color entries are rejected.

Valid map characters:
- `1` wall
- `0` walkable tile
- `N`, `S`, `E`, `W` spawn (exactly one)
- space (` `) as map padding/outside area

Example:

```text
NO srcs/assets/Rocks_1.xpm
SO srcs/assets/Rocks_2.xpm
WE srcs/assets/bricks_1.xpm
EA srcs/assets/bricks_2.xpm

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
│   └── simple.cub
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
│   │   ├── set_texture.c
│   │   ├── parse_utils.c
│   │   ├── parse_map.c
│   │   ├── parse_map_helpers.c
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
  -> parse/validate elements
  -> extract final map block
  -> validate map/spawn/closure
  -> init MLX + textures
  -> loop:
       movement (time-scaled)
       render_3d (raycast + textured walls)
       draw_minimap overlay
```

---

## Useful Checks

### Norminette

```bash
norminette inc srcs
```

### Full Valgrind (recommended for evaluation)

```bash
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --num-callers=25 \
  --errors-for-leak-kinds=all \
  --error-exitcode=42 \
  ./cub3D maps/simple.cub
```

---

## Resources

- [Ray Casting](https://en.wikipedia.org/wiki/Ray_casting)
- [DDA line traversal concept](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [MiniLibX (42 Linux)](https://github.com/42Paris/minilibx-linux)
- [XPM format](https://en.wikipedia.org/wiki/X_PixMap)

---

## Authors

- **kqueiroz**
- **loda-sil**

---

## License

This project is part of the 42 School educational curriculum.

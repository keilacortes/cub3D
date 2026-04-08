# 🚀 PRÓXIMO PASSO - Implementação Direta

## ✅ O QUE JÁ EXISTE

Analisando seu projeto, você **já tem pronto**:

### Header (inc/cub3d.h) ✅
- ✅ Todas structs necessárias: `s_img`, `s_camera`, `s_render`
- ✅ `s_game` já integra camera e render
- ✅ Includes corretos (mlx.h, math.h, etc.)

### Parser (srcs/parse/) ✅
- ✅ `parse_file.c` - Parse de texturas e cores
- ✅ `parse_map.c` - Parse do mapa
- ✅ `validate_map.c` - Validação
- ✅ `validate_tex.c` - Validação de texturas

### Estrutura base ✅
- ✅ `main.c` com init_game()
- ✅ `cub3d_utils.c` com exit_error()
- ✅ `cleanup_game.c` com liberação
- ✅ Makefile funcional com libft e MLX

### MLX já inicializado ✅
```c
game.mlx = mlx_init();
win = mlx_new_window(game.mlx, 800, 600, "cub3D");
```

---

## 🎯 O QUE FALTA (apenas renderização!)

Você está **80% pronto**! Falta apenas:

### 1️⃣ Adicionar defines ao header
### 2️⃣ Criar `srcs/init.c` (carregamento de texturas)
### 3️⃣ Criar `srcs/cleanup.c` (limpar renderização)
### 4️⃣ Criar `srcs/render/render.c` (loop principal)
### 5️⃣ Criar `srcs/render/draw.c` (desenhar chão/teto)
### 6️⃣ Atualizar `main.c` (integrar renderização)

---

## 📝 PASSO A PASSO

### PASSO 1: Atualizar `inc/cub3d.h`

**Adicione após os includes (linha 23):**

```c
/* Dimensões da janela */
# define SCREEN_W 800
# define SCREEN_H 600

/* Velocidades */
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

/* Keycodes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* Índices de texturas */
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
```

**Adicione antes do `#endif` (linha 96):**

```c
/* Novas funções de renderização */
void	init_render(t_game *game);
void	init_camera(t_game *game);
void	load_textures(t_game *game);
void	cleanup_render(t_game *game);
int		render_frame(t_game *game);
void	draw_floor_ceiling(t_game *game);
int		handle_keypress(int key, t_game *game);
int		handle_close(t_game *game);
```

**CORRIJA a struct `s_render` (linha 65-74):**

A struct atual tem `img_data`, mas deveria ter `data` + metadados. Substitua por:

```c
typedef struct s_render
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
	t_img	textures[4];
}	t_render;
```

---

### PASSO 2: Criar `srcs/init.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:00:00 by loena             #+#    #+#             */
/*   Updated: 2026/04/07 01:00:00 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_game *game, int index, char *path)
{
	t_img	*tex;

	tex = &game->rend.textures[index];
	tex->img = mlx_xpm_file_to_image(game->rend.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		exit_error("Erro ao carregar textura");
	tex->data = (int *)mlx_get_data_addr(tex->img, &game->rend.bpp,
			&game->rend.size_line, &game->rend.endian);
}

void	load_textures(t_game *game)
{
	load_single_texture(game, NORTH, game->tex.north);
	load_single_texture(game, SOUTH, game->tex.south);
	load_single_texture(game, WEST, game->tex.west);
	load_single_texture(game, EAST, game->tex.east);
}

void	init_render(t_game *game)
{
	game->rend.mlx = mlx_init();
	if (!game->rend.mlx)
		exit_error("Erro ao inicializar MLX");
	game->rend.win = mlx_new_window(game->rend.mlx, SCREEN_W,
			SCREEN_H, "cub3D");
	if (!game->rend.win)
		exit_error("Erro ao criar janela");
	game->rend.img = mlx_new_image(game->rend.mlx, SCREEN_W, SCREEN_H);
	if (!game->rend.img)
		exit_error("Erro ao criar imagem");
	game->rend.data = (int *)mlx_get_data_addr(game->rend.img,
			&game->rend.bpp, &game->rend.size_line, &game->rend.endian);
}

void	init_camera(t_game *game)
{
	game->camera.x = (double)game->player.pos_y + 0.5;
	game->camera.y = (double)game->player.pos_x + 0.5;
	game->camera.fov = M_PI / 3.0;
	if (game->map.spawn == 'N')
		game->camera.angle = 3 * M_PI / 2;
	else if (game->map.spawn == 'S')
		game->camera.angle = M_PI / 2;
	else if (game->map.spawn == 'E')
		game->camera.angle = 0;
	else if (game->map.spawn == 'W')
		game->camera.angle = M_PI;
	else
		game->camera.angle = 0;
}
```

---

### PASSO 3: Criar `srcs/cleanup.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   cleanup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:00:00 by loena             #+#    #+#             */
/*   Updated: 2026/04/07 01:00:00 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_render(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->rend.textures[i].img)
			mlx_destroy_image(game->rend.mlx, game->rend.textures[i].img);
		i++;
	}
	if (game->rend.img)
		mlx_destroy_image(game->rend.mlx, game->rend.img);
	if (game->rend.win)
		mlx_destroy_window(game->rend.mlx, game->rend.win);
}
```

---

### PASSO 4: Criar pasta e arquivo `srcs/render/render.c`

```bash
mkdir -p srcs/render
```

```c
/* ************************************************************************** */
/*                                                                            */
/*   render.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:00:00 by loena             #+#    #+#             */
/*   Updated: 2026/04/07 01:00:00 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	mlx_put_image_to_window(game->rend.mlx, game->rend.win,
		game->rend.img, 0, 0);
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup_render(game);
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		handle_close(game);
	return (0);
}
```

---

### PASSO 5: Criar `srcs/render/draw.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   draw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:00:00 by loena             #+#    #+#             */
/*   Updated: 2026/04/07 01:00:00 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_int(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	draw_ceiling(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H / 2)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			game->rend.data[y * SCREEN_W + x] = color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_game *game, int color)
{
	int	x;
	int	y;

	y = SCREEN_H / 2;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			game->rend.data[y * SCREEN_W + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_floor_ceiling(t_game *game)
{
	int	floor_color;
	int	ceil_color;

	floor_color = rgb_to_int(game->tex.floor);
	ceil_color = rgb_to_int(game->tex.ceiling);
	draw_ceiling(game, ceil_color);
	draw_floor(game, floor_color);
}
```

---

### PASSO 6: Atualizar `srcs/main.c`

**SUBSTITUA o main existente (linhas 15-48) por:**

```c
static void	init_game_values(t_game *game)
{
	int	i;

	game->tex.north = NULL;
	game->tex.south = NULL;
	game->tex.west = NULL;
	game->tex.east = NULL;
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.spawn = '\0';
	game->player.spawn_found = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	i = -1;
	while (++i < 3)
	{
		game->tex.floor[i] = -1;
		game->tex.ceiling[i] = -1;
	}
}

static void	init_render_values(t_game *game)
{
	int	i;

	game->rend.mlx = NULL;
	game->rend.win = NULL;
	game->rend.img = NULL;
	i = 0;
	while (i < 4)
	{
		game->rend.textures[i].img = NULL;
		i++;
	}
}

void	init_game(t_game *game)
{
	init_game_values(game);
	init_render_values(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_error("Usage: ./cub3d <file.cub>");
	init_game(&game);
	check_arg(argv[1], &game);
	init_render(&game);
	load_textures(&game);
	init_camera(&game);
	mlx_loop_hook(game.rend.mlx, render_frame, &game);
	mlx_hook(game.rend.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.rend.win, 17, 0, handle_close, &game);
	mlx_loop(game.rend.mlx);
	return (0);
}
```

---

### PASSO 7: Atualizar `Makefile`

**Adicione os novos arquivos na variável SRCS (linha 13):**

```makefile
SRCS = $(addprefix srcs/, main.c \
						  cub3d_utils.c \
						  cleanup_game.c \
						  init.c \
						  cleanup.c \
						  parse/parse_file.c \
						  parse/parse_utils.c \
						  parse/parse_map.c \
						  parse/validate_map.c \
						  parse/validate_tex.c \
						  render/render.c \
						  render/draw.c \
)
```

---

## 🧪 TESTAR

```bash
make re
./cub3D maps/simple.cub
```

**Resultado esperado:**
- Janela 800x600 abre
- Metade superior = cor do teto (C)
- Metade inferior = cor do chão (F)
- ESC fecha o programa

---

## 📊 RESUMO

| Componente | Status | Observação |
|------------|--------|------------|
| Parser | ✅ Pronto | 100% funcional |
| Structs | ✅ Pronto | Já no header |
| MLX Init | ✅ Pronto | Já no main |
| Texturas | 🟡 Adicionar | init.c |
| Renderização | 🟡 Adicionar | render/ |
| Callbacks | 🟡 Adicionar | Integrar no main |

**Você já tem 70% do código pronto!** Falta só plugar a renderização. 🚀

---

## 🎯 PRÓXIMAS FASES

Depois deste passo (chão/teto funcionando):

1. **FASE 2**: Ray-casting DDA (paredes com cores sólidas)
2. **FASE 3**: Texturização de paredes
3. **FASE 4**: Movimento do jogador
4. **FASE 5**: Rotação da câmera

Tudo está documentado em `implementacao-dda.md` e `plano-mandatorio.md`!

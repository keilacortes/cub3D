# 🚀 IMPLEMENTAÇÃO DIRETA — Cub3D Mandatório

## ⚡ PLANO SEM CORREÇÃO DE BUGS

Começamos direto na implementação das funcionalidades de renderização.

---

## 📋 OBSERVAÇÕES IMPORTANTES

### Norminette
Todo código neste guia segue as regras da Norma 42:
- ✅ Máximo 25 linhas por função
- ✅ Máximo 5 funções por arquivo (exceto arquivos complexos)
- ✅ Máximo 80 caracteres por linha
- ✅ Tabs (não espaços) para indentação
- ✅ Comentários em formato `/* */`
- ✅ Header 42 padrão em todos arquivos

### Substituições Necessárias
Nos cabeçalhos dos arquivos, substitua:
- `<login>` → seu login da 42
- Datas `2026/04/07` → data atual

### Estrutura de Projeto
```
cub3D/
├── inc/cub3d.h          # Cabeçalho principal
├── srcs/
│   ├── main.c           # Entry point
│   ├── init.c           # Inicialização MLX/texturas
│   ├── cleanup.c        # Liberação de recursos
│   └── render/
│       ├── render.c     # Loop de renderização
│       └── draw.c       # Funções de desenho
├── maps/simple.cub      # Mapa de teste
└── Makefile
```

---

## 🗺️ ROADMAP (5 FASES)

### ✅ FASE 0: Estrutura Base ⏱️ 2-3h 🔴 COMEÇAR AQUI

**Objetivo**: Preparar structs e inicialização MLX

#### Arquivos a criar:
- [ ] `srcs/init.c`
- [ ] `srcs/cleanup.c`

#### Arquivos a modificar:
- [ ] `inc/cub3d.h` (adicionar structs de renderização)
- [ ] `srcs/main.c` (novo fluxo com MLX)

#### Tarefas:
1. Atualizar `cub3d.h` com structs otimizadas
2. Criar `init.c` com:
   - `init_game()`
   - `init_mlx()`
   - `init_player()`
   - `load_textures()`
3. Criar `cleanup.c` com liberação de recursos
4. Atualizar `main.c` com novo fluxo

**Teste**: Janela abre e fecha sem crash

---

### ✅ FASE 1: Chão e Teto ⏱️ 1-2h

**Objetivo**: Renderizar cores básicas (F e C)

#### Arquivos a criar:
- [ ] `srcs/render/render.c`
- [ ] `srcs/render/draw.c`

#### Tarefas:
1. Criar função `render_frame()`
2. Criar função `draw_floor_ceiling()`
3. Registrar `mlx_loop_hook` no main
4. Testar que metade da tela é F e metade é C

**Teste**: Tela com cores F (chão) e C (teto)

---

### ✅ FASE 2: Ray-Casting (Cores Sólidas) ⏱️ 6-8h ⚠️ NÚCLEO

**Objetivo**: Visão 3D sem texturas

#### Arquivos a criar:
- [ ] `srcs/render/raycasting.c`

#### Tarefas:
1. Implementar DDA algorithm
2. Detectar colisão com paredes
3. Calcular distância perpendicular
4. Desenhar colunas com cores sólidas:
   - Norte: Vermelho
   - Sul: Azul
   - Leste: Verde
   - Oeste: Amarelo

**Teste**: Visão 3D funcional com cores sólidas

---

### ✅ FASE 3: Aplicar Texturas ⏱️ 3-4h

**Objetivo**: Substituir cores por texturas reais

#### Arquivos a modificar:
- [ ] `srcs/render/raycasting.c` (adicionar mapeamento de textura)
- [ ] `srcs/render/draw.c` (desenhar com pixels de textura)

#### Tarefas:
1. Calcular `wall_x` (posição onde raio atingiu)
2. Selecionar textura correta (N/S/E/W)
3. Mapear coluna da textura
4. Desenhar pixel por pixel com textura

**Teste**: Paredes com texturas XPM visíveis

---

### ✅ FASE 4: Controles ⏱️ 2-3h

**Objetivo**: Movimento e rotação

#### Arquivos a criar:
- [ ] `srcs/controls/controls.c`

#### Tarefas:
1. Implementar `handle_keypress()`
2. Implementar movimento (WASD)
3. Implementar rotação (setas)
4. Implementar detecção de colisão
5. Implementar `handle_close()` (ESC e X)

**Teste**: Andar e girar sem atravessar paredes

---

### ✅ FASE 5: Polimento ⏱️ 1-2h

**Objetivo**: Finalizar e validar

#### Tarefas:
1. Ajustar velocidades (MOVE_SPEED, ROT_SPEED)
2. Executar `norminette` e corrigir
3. Executar `valgrind` e corrigir leaks
4. Criar texturas XPM (se ainda não tiver)
5. Testar com múltiplos mapas

**Teste**: Projeto completo, funcional e sem erros

---

## ⏱️ ESTIMATIVA TOTAL

| Fase | Tempo |
|------|-------|
| 0. Estrutura Base | 2-3h |
| 1. Chão/Teto | 1-2h |
| 2. Ray-Casting | 6-8h |
| 3. Texturas | 3-4h |
| 4. Controles | 2-3h |
| 5. Polimento | 1-2h |
| **TOTAL** | **15-22h** |

---

## 💻 IMPLEMENTAÇÃO PASSO A PASSO

### FASE 0: Estrutura Base

#### 1. Atualizar `inc/cub3d.h`

```c
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

/*
** ============================================================================
** CONSTANTES
** ============================================================================
*/

/* Dimensões da janela */
# define SCREEN_W 800
# define SCREEN_H 600

/* Velocidades de movimento e rotação */
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

/* Keycodes Linux (X11) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* Índices de texturas no array */
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

/*
** ============================================================================
** STRUCTS EXISTENTES (do parser)
** ============================================================================
*/
typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     floor[3];
    int     ceiling[3];
}   t_textures;

typedef struct s_map
{
	char	**grid;
	char	spawn;
	int		height;
}	t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		spawn_found;
}	t_player;

/*
** ============================================================================
** NOVAS STRUCTS (renderização)
** ============================================================================
*/

/*
** s_img: Representa uma imagem carregada (textura)
** - img: Ponteiro MLX para a imagem
** - data: Array de pixels (acesso direto)
** - width/height: Dimensões da textura
*/
typedef struct s_img
{
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_img;

/*
** s_camera: Posição e orientação do jogador
** - x, y: Posição float no mapa (não inteira como no parser)
** - angle: Ângulo de visão em radianos (0 = leste, π/2 = sul, π = oeste, 3π/2 = norte)
** - fov: Campo de visão (field of view) em radianos (padrão: π/3 = 60°)
*/
typedef struct s_camera
{
	double	x;
	double	y;
	double	angle;
	double	fov;
}	t_camera;

/*
** s_render: Contexto de renderização
** - mlx: Conexão com servidor gráfico
** - win: Janela onde renderizamos
** - img: Buffer de imagem (double buffering)
** - data: Array de pixels do buffer (acesso direto via mlx_get_data_addr)
** - textures[4]: Texturas carregadas (NORTH, SOUTH, WEST, EAST)
** - size_line/bpp/endian: Informações de formato da imagem
*/
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

/*
** s_game: Estrutura principal do jogo
** Agrega todas as outras structs
*/
typedef struct s_game
{
	t_map		map;
	t_textures	tex;
	t_player	player;
	t_camera	camera;
	t_render	rend;
}	t_game;

/*
** ============================================================================
** PROTÓTIPOS DE FUNÇÕES
** ============================================================================
*/

/* Funções existentes (parser) */
void	exit_error(char *message);
void	free_grid(char **arr);
void	cleanup_game(t_game *game);
void	check_arg(char *arg, t_game *game);
void	parse_file(const char *file, t_game *game);
int		is_valid_num(char *str);
char	*get_value(char *line);
void	parse_map(const char *file, t_map *map, t_player *player);
void	validate_map(t_map *map, t_player *player);

/* Novas funções (renderização) */
void	init_render(t_game *game);
void	init_camera(t_game *game);
void	load_textures(t_game *game);
void	cleanup_render(t_game *game);
int		render_frame(t_game *game);
void	draw_floor_ceiling(t_game *game);
void	cast_all_rays(t_game *game);
int		handle_keypress(int key, t_game *game);
int		handle_close(t_game *game);

#endif
```

#### 2. Criar `srcs/init.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by <login>       #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Funções de inicialização do sistema de renderização
** - init_render: Inicializa MLX, janela e buffer de imagem
** - load_textures: Carrega as 4 texturas XPM das paredes
** - init_camera: Define posição e ângulo inicial da câmera
*/

#include "cub3d.h"

/*
** Converte componentes RGB (0-255) em um inteiro de cor
** Formato: 0xRRGGBB
** R (red) desloca 16 bits, G (green) 8 bits, B (blue) fica no lugar
*/
static int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/*
** Inicializa o buffer de imagem onde a cena será renderizada
** mlx_new_image: Cria uma imagem do tamanho da tela
** mlx_get_data_addr: Obtém ponteiro para o array de pixels e metadados
*/
static void	init_image_buffer(t_game *game)
{
	game->rend.img = mlx_new_image(game->rend.mlx, SCREEN_W, SCREEN_H);
	if (!game->rend.img)
		exit_error("Failed to create image");
	game->rend.data = (int *)mlx_get_data_addr(game->rend.img,
			&game->rend.bpp, &game->rend.size_line, &game->rend.endian);
}

/*
** Inicializa o sistema de renderização:
** 1. Conecta com o servidor gráfico (mlx_init)
** 2. Cria janela de 800x600 pixels
** 3. Cria buffer de imagem para renderização
*/
void	init_render(t_game *game)
{
	game->rend.mlx = mlx_init();
	if (!game->rend.mlx)
		exit_error("Failed to initialize MLX");
	game->rend.win = mlx_new_window(game->rend.mlx,
			SCREEN_W, SCREEN_H, "cub3D");
	if (!game->rend.win)
		exit_error("Failed to create window");
	init_image_buffer(game);
}

/*
** Carrega uma única textura XPM e obtém seus dados de pixel
** mlx_xpm_file_to_image: Carrega arquivo XPM e retorna ponteiro de imagem
** mlx_get_data_addr: Obtém array de pixels (ARGB em inteiros)
** idx: Índice no array (NORTH=0, SOUTH=1, WEST=2, EAST=3)
*/
static void	load_single_texture(t_game *g, int idx, char *path)
{
	int	bpp;
	int	size_line;
	int	endian;

	g->rend.textures[idx].img = mlx_xpm_file_to_image(g->rend.mlx, path,
			&g->rend.textures[idx].width, &g->rend.textures[idx].height);
	if (!g->rend.textures[idx].img)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		exit(1);
	}
	g->rend.textures[idx].data = (int *)mlx_get_data_addr(
			g->rend.textures[idx].img, &bpp, &size_line, &endian);
}

/*
** Carrega todas as 4 texturas das paredes
** Ordem do array: [0]=Norte, [1]=Sul, [2]=Oeste, [3]=Leste
** Os caminhos vêm da struct game->tex (parseados do arquivo .cub)
*/
void	load_textures(t_game *game)
{
	load_single_texture(game, NORTH, game->tex.north);
	load_single_texture(game, SOUTH, game->tex.south);
	load_single_texture(game, WEST, game->tex.west);
	load_single_texture(game, EAST, game->tex.east);
}

/*
** Inicializa a câmera do jogador baseado na posição de spawn
** - Converte posição inteira do parser para double (coordenadas precisas)
** - Adiciona 0.5 para centralizar no tile
** - Define ângulo inicial baseado no caractere de spawn (N/S/E/W)
** - N aponta para cima (270°), S para baixo (90°), E direita (0°), W esquerda (180°)
*/
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

#### 3. Criar `srcs/cleanup.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   cleanup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by <login>       #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Libera todos os recursos alocados para renderização
** - Destroi as 4 texturas carregadas
** - Destroi o buffer de imagem
** - Destroi a janela
** Importante: Sempre chamar antes de encerrar o programa
*/

#include "cub3d.h"

/*
** Libera recursos de renderização na ordem correta:
** 1. Texturas (imagens carregadas de XPM)
** 2. Buffer de imagem (onde renderizamos a cena)
** 3. Janela (interface gráfica)
** Nota: O ponteiro mlx não é liberado (gerenciado internamente pela MLX)
*/
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

#### 4. Modificar `srcs/main.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:51:06 by <login>       #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Programa principal do Cub3D
** Fluxo: Parse → Inicialização → Loop de Renderização
*/

#include "cub3d.h"

/*
** Inicializa todos os campos da struct game com valores padrão
** - Ponteiros são setados para NULL (segurança)
** - Arrays RGB são setados para -1 (indicador de não-configurado)
** - Contadores zerados
*/
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

/*
** Inicializa campos de renderização com valores seguros
** Importante fazer antes de qualquer operação de limpeza
*/
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

/*
** Função principal de inicialização
** Zera todas as structs para evitar lixo de memória
*/
void	init_game(t_game *game)
{
	init_game_values(game);
	init_render_values(game);
}

/*
** Função principal do programa
** 1. Valida argumentos (deve receber exatamente 1 arquivo .cub)
** 2. Parse do arquivo de configuração
** 3. Inicializa sistema gráfico (MLX)
** 4. Carrega recursos (texturas)
** 5. Configura câmera
** 6. Registra callbacks de eventos
** 7. Entra no loop principal
*/
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_error("Usage: ./cub3D <map.cub>");
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

#### 5. Atualizar `Makefile`

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
)
```

---

### FASE 1: Chão e Teto

#### 1. Criar `srcs/render/render.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   render.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by <login>       #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Loop principal de renderização
** Chamado automaticamente pela MLX a cada frame
** Ordem: 1. Desenhar chão/teto → 2. Ray-casting → 3. Exibir na tela
*/

#include "cub3d.h"

/*
** Função de renderização chamada a cada frame
** 1. draw_floor_ceiling: Pinta metades da tela (F e C)
** 2. cast_all_rays: Ray-casting para visão 3D (FASE 2)
** 3. mlx_put_image_to_window: Exibe buffer na janela
** Retorna 0 para continuar o loop
*/
int	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	mlx_put_image_to_window(game->rend.mlx, game->rend.win,
		game->rend.img, 0, 0);
	return (0);
}
```

#### 2. Criar `srcs/render/draw.c`

```c
/* ************************************************************************** */
/*                                                                            */
/*   draw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by <login>       #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Funções de desenho básico
** - Colocar pixels no buffer de imagem
** - Preencher chão e teto com cores sólidas
*/

#include "cub3d.h"

/*
** Converte array RGB [0-255] para int no formato MLX (0xRRGGBB)
** - R (vermelho) deslocado 16 bits à esquerda
** - G (verde) deslocado 8 bits à esquerda
** - B (azul) sem deslocamento
** Exemplo: [255, 128, 0] → 0xFF8000 (laranja)
*/
static int	rgb_to_int(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/*
** Preenche a metade superior da tela com cor do teto
** Loop: para cada linha de 0 até metade, pinta todas colunas
*/
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

/*
** Preenche a metade inferior da tela com cor do chão
** Loop: para cada linha da metade até o fim, pinta todas colunas
*/
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

/*
** Desenha chão e teto com cores configuradas no arquivo .cub
** Divide a tela ao meio horizontalmente:
** - Metade superior: cor do teto (C)
** - Metade inferior: cor do chão (F)
*/
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

#### 3. Atualizar Makefile

```makefile
# **************************************************************************** #
#                                                                              #
#    Makefile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 00:00:00 by <login>       #+#    #+#              #
#    Updated: 2026/04/07 00:00:00 by <login>      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = cub3D

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Diretórios
INC_DIR = inc
SRC_DIR = srcs
OBJ_DIR = obj

# Arquivos fonte (adicione novos arquivos aqui)
SRCS = $(addprefix $(SRC_DIR)/, main.c \
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

# Objetos (gerados automaticamente a partir dos .c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MiniLibX (ajuste o caminho conforme sua instalação)
MLX_DIR = libs/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft (caso use)
# LIBFT_DIR = libs/libft
# LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Regra padrão: compila tudo
all: $(NAME)

# Compila o executável
$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compilado com sucesso!"

# Compila cada arquivo .c em um .o (cria subdiretórios se necessário)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@

# Compila a MiniLibX
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Remove objetos
clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objetos removidos"

# Remove objetos e executável
fclean: clean
	@rm -f $(NAME)
	@echo "🧹 $(NAME) removido"

# Recompila tudo do zero
re: fclean all

# Regras que não são arquivos
.PHONY: all clean fclean re
```

**TESTE**: 
```bash
make re
./cub3D maps/simple.cub
# Deve abrir janela com cores F (chão) e C (teto)
```

---

## 📋 PRÓXIMOS PASSOS

### Imediato (AGORA):
1. Criar pastas: `mkdir -p srcs/render srcs/controls`
2. Copiar código da FASE 0
3. Compilar e testar

### Depois (FASE 2):
Ver `implementacao-dda.md` para código completo do ray-casting

---

## ✅ CHECKLIST RÁPIDO

- [ ] Criar `srcs/render/` e `srcs/controls/`
- [ ] Atualizar `inc/cub3d.h`
- [ ] Criar `srcs/init.c`
- [ ] Criar `srcs/cleanup.c`
- [ ] Modificar `srcs/main.c`
- [ ] Criar `srcs/render/render.c`
- [ ] Criar `srcs/render/draw.c`
- [ ] Atualizar `Makefile`
- [ ] Testar que janela abre com cores

---

**Começe pela FASE 0 agora! O código está pronto para copiar! 🚀**

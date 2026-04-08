# 🎯 PLANO MANDATÓRIO — Cub3D (Apenas Parte Obrigatória)

## 📋 Checklist do Mandatório

### Requisitos Funcionais
- [ ] Parser de arquivo `.cub` (texturas, cores, mapa)
- [ ] Ray-casting funcional (visão 3D)
- [ ] 4 texturas diferentes nas paredes (N, S, E, W)
- [ ] Chão com cor F configurada
- [ ] Teto com cor C configurada
- [ ] Movimento: W (frente), S (trás), A (esquerda), D (direita)
- [ ] Rotação: ← (esquerda), → (direita)
- [ ] ESC fecha janela
- [ ] Clicar X fecha janela
- [ ] Renderização suave (sem flickering)

### Requisitos Técnicos
- [ ] Código compila com `-Wall -Wextra -Werror`
- [ ] Sem memory leaks (valgrind clean)
- [ ] Sem crashes (segfault, bus error, double free)
- [ ] Norma 42 aprovada
- [ ] Makefile com regras: all, clean, fclean, re
- [ ] README.md completo

---

## 🏗️ ESTRUTURA MÍNIMA NECESSÁRIA

### Header Simplificado (inc/cub3d.h)

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

// Constantes básicas
# define SCREEN_W 800
# define SCREEN_H 600
# define TEX_SIZE 64
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// Keycodes Linux
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// Índices de texturas
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

// Configuração do arquivo .cub
typedef struct s_config
{
    char    *tex_paths[4];      // [NORTH, SOUTH, WEST, EAST]
    int     floor_color;        // RGB convertido para int
    int     ceiling_color;      // RGB convertido para int
    char    **map;
    int     map_height;
    int     map_width;
}   t_config;

// Dados da textura carregada
typedef struct s_texture
{
    void    *img;
    int     *data;
    int     width;
    int     height;
}   t_texture;

// Estado do jogador
typedef struct s_player
{
    double  x;          // Posição X (float para movimento suave)
    double  y;          // Posição Y
    double  angle;      // Ângulo de visão (radianos)
    double  fov;        // Campo de visão
}   t_player;

// Sistema de renderização
typedef struct s_render
{
    void        *mlx;
    void        *win;
    void        *img;           // Buffer de renderização
    int         *img_data;
    t_texture   textures[4];    // [NORTH, SOUTH, WEST, EAST]
}   t_render;

// Struct principal
typedef struct s_game
{
    t_config    cfg;
    t_player    player;
    t_render    rend;
}   t_game;

// Parsing
void    parse_file(char *filepath, t_game *game);
void    validate_map(t_game *game);

// Init
void    init_game(t_game *game);
void    init_mlx(t_game *game);
void    init_player(t_game *game);

// Rendering
int     render_frame(t_game *game);
void    draw_floor_ceiling(t_game *game);
void    cast_all_rays(t_game *game);

// Controls
int     handle_keypress(int key, t_game *game);
int     handle_close(t_game *game);

// Utils
void    exit_error(char *msg);
void    cleanup(t_game *game);
int     create_rgb(int r, int g, int b);

#endif
```

---

## 📁 ESTRUTURA DE ARQUIVOS MÍNIMA

```
cub3D/
├── Makefile
├── README.md
│
├── inc/
│   └── cub3d.h                 (Header único e simples)
│
├── srcs/
│   ├── main.c                  (50 linhas)
│   ├── init.c                  (100 linhas - init_game, init_mlx, init_player)
│   ├── cleanup.c               (50 linhas)
│   │
│   ├── parse/
│   │   ├── parse_file.c        (JÁ EXISTE - corrigir bugs)
│   │   ├── parse_map.c         (JÁ EXISTE)
│   │   ├── parse_utils.c       (JÁ EXISTE)
│   │   ├── validate_map.c      (JÁ EXISTE - corrigir bugs)
│   │   └── validate_tex.c      (JÁ EXISTE - corrigir bugs)
│   │
│   ├── render/
│   │   ├── render.c            (80 linhas - render_frame + helpers)
│   │   ├── raycasting.c        (150 linhas - cast_all_rays + DDA)
│   │   └── draw.c              (100 linhas - draw_floor_ceiling + draw_wall)
│   │
│   └── controls/
│       └── controls.c          (80 linhas - keypress + close)
│
├── maps/
│   └── simple.cub
│
├── textures/
│   ├── north.xpm
│   ├── south.xpm
│   ├── west.xpm
│   └── east.xpm
│
└── libs/
    ├── libft/
    └── minilibx/
```

**Total**: ~13 arquivos .c (já tem 9, falta criar 4)

---

## 🚀 ROADMAP OTIMIZADO (Apenas Mandatório)

### FASE 0: Correção de Bugs ⏱️ 1-2h 🔴 URGENTE
- [ ] Corrigir `validate_tex.c` (Bug #1)
- [ ] Corrigir `parse_file.c` (Bug #2)
- [ ] Corrigir `validate_map.c` (Bugs #3 e #4)
- [ ] Testar parsing com mapas válidos/inválidos

---

### FASE 1: Estrutura Base ⏱️ 2-3h
- [ ] Atualizar `cub3d.h` com structs otimizadas
- [ ] Criar `srcs/init.c`
  - `init_game()` - Zera structs
  - `init_mlx()` - Inicializa MLX + janela + buffer
  - `init_player()` - Define posição e ângulo inicial
- [ ] Atualizar `main.c` com novo fluxo
- [ ] Criar `srcs/cleanup.c` - Libera tudo

**Teste**: Janela abre e fecha sem crash

---

### FASE 2: Carregar Texturas ⏱️ 2-3h
- [ ] Adicionar função `load_textures()` em `init.c`
- [ ] Criar 4 texturas XPM simples (64x64)
- [ ] Validar que texturas carregam sem erro

**Teste**: `valgrind` sem leaks ao abrir/fechar

---

### FASE 3: Ray-Casting (Cores Sólidas) ⏱️ 8-10h ⚠️ NÚCLEO
- [ ] Criar `srcs/render/raycasting.c`
  - `cast_all_rays()` - Loop principal
  - `cast_single_ray()` - DDA algorithm
  - `get_wall_distance()` - Cálculo de distância
- [ ] Criar `srcs/render/draw.c`
  - `draw_floor_ceiling()` - Pinta metades da tela
  - `draw_wall_line()` - Desenha coluna (cor sólida por direção)
- [ ] Criar `srcs/render/render.c`
  - `render_frame()` - Orquestra tudo
- [ ] Testar com cores sólidas:
  - Norte: Vermelho
  - Sul: Azul
  - Leste: Verde
  - Oeste: Amarelo

**Teste**: Visão 3D funcional (sem texturas ainda)

---

### FASE 4: Aplicar Texturas ⏱️ 3-4h
- [ ] Modificar `draw_wall_line()` para usar texturas
- [ ] Calcular `wall_x` (onde raio atingiu parede)
- [ ] Mapear coluna da textura correta
- [ ] Desenhar com pixels da textura

**Teste**: Paredes com texturas visíveis

---

### FASE 5: Controles ⏱️ 2-3h
- [ ] Criar `srcs/controls/controls.c`
  - `handle_keypress()` - Switch para WASD + setas + ESC
  - `move_player()` - Atualiza posição (com validação de parede)
  - `rotate_player()` - Atualiza ângulo
  - `handle_close()` - Cleanup e exit
- [ ] Registrar hooks no `main.c`
- [ ] Testar movimento e rotação

**Teste**: Consegue andar e girar sem atravessar paredes

---

### FASE 6: Polimento Final ⏱️ 2-3h
- [ ] Ajustar velocidades (MOVE_SPEED, ROT_SPEED)
- [ ] Validar que ESC e X fecham janela
- [ ] Executar `norminette` e corrigir
- [ ] Executar `valgrind` e corrigir leaks
- [ ] Criar mapas de teste (válidos e inválidos)
- [ ] Atualizar README.md

**Teste**: Projeto completo e funcional

---

## ⏱️ ESTIMATIVA TOTAL

| Fase | Tempo | Prioridade |
|------|-------|------------|
| 0. Bugs | 1-2h | 🔴 Crítico |
| 1. Base | 2-3h | 🔴 Crítico |
| 2. Texturas | 2-3h | 🟡 Importante |
| 3. Ray-casting | 8-10h | 🔴 Crítico |
| 4. Texturas nas Paredes | 3-4h | 🟡 Importante |
| 5. Controles | 2-3h | 🟡 Importante |
| 6. Polimento | 2-3h | 🟢 Final |
| **TOTAL** | **20-28h** | |

**Economia**: ~20-30 horas comparado com implementação que inclui bônus!

---

## 💻 CÓDIGO ESSENCIAL

### main.c Simplificado

```c
#include "cub3d.h"

int main(int ac, char **av)
{
    t_game  game;
    
    if (ac != 2)
        exit_error("Usage: ./cub3D <map.cub>");
    
    init_game(&game);
    parse_file(av[1], &game);
    validate_map(&game);
    
    init_mlx(&game);
    init_player(&game);
    
    mlx_loop_hook(game.rend.mlx, render_frame, &game);
    mlx_hook(game.rend.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.rend.win, 17, 0, handle_close, &game);
    
    mlx_loop(game.rend.mlx);
    return (0);
}
```

### init.c Essencial

```c
#include "cub3d.h"

void    init_game(t_game *game)
{
    int i;
    
    // Zerar config
    i = 0;
    while (i < 4)
        game->cfg.tex_paths[i++] = NULL;
    game->cfg.map = NULL;
    game->cfg.floor_color = 0;
    game->cfg.ceiling_color = 0;
    
    // Zerar render
    game->rend.mlx = NULL;
    game->rend.win = NULL;
    game->rend.img = NULL;
    i = 0;
    while (i < 4)
    {
        game->rend.textures[i].img = NULL;
        i++;
    }
    
    // Zerar player
    game->player.x = 0;
    game->player.y = 0;
    game->player.angle = 0;
    game->player.fov = M_PI / 3;  // 60 graus
}

void    init_mlx(t_game *game)
{
    int bpp;
    int size_line;
    int endian;
    
    game->rend.mlx = mlx_init();
    if (!game->rend.mlx)
        exit_error("MLX init failed");
    
    game->rend.win = mlx_new_window(game->rend.mlx, 
        SCREEN_W, SCREEN_H, "cub3D");
    if (!game->rend.win)
        exit_error("Window creation failed");
    
    game->rend.img = mlx_new_image(game->rend.mlx, SCREEN_W, SCREEN_H);
    if (!game->rend.img)
        exit_error("Image creation failed");
    
    game->rend.img_data = (int *)mlx_get_data_addr(game->rend.img,
        &bpp, &size_line, &endian);
    
    load_textures(game);
}

static void load_single_texture(t_game *g, int idx)
{
    int bpp, sl, end;
    
    g->rend.textures[idx].img = mlx_xpm_file_to_image(
        g->rend.mlx, g->cfg.tex_paths[idx],
        &g->rend.textures[idx].width,
        &g->rend.textures[idx].height);
    
    if (!g->rend.textures[idx].img)
        exit_error("Texture load failed");
    
    g->rend.textures[idx].data = (int *)mlx_get_data_addr(
        g->rend.textures[idx].img, &bpp, &sl, &end);
}

void    load_textures(t_game *game)
{
    load_single_texture(game, NORTH);
    load_single_texture(game, SOUTH);
    load_single_texture(game, WEST);
    load_single_texture(game, EAST);
}

void    init_player(t_game *game)
{
    int     i;
    int     j;
    char    spawn;
    
    // Encontrar spawn
    i = 0;
    while (i < game->cfg.map_height)
    {
        j = 0;
        while (game->cfg.map[i][j])
        {
            spawn = game->cfg.map[i][j];
            if (spawn == 'N' || spawn == 'S' || 
                spawn == 'E' || spawn == 'W')
            {
                game->player.x = j + 0.5;
                game->player.y = i + 0.5;
                
                if (spawn == 'N')
                    game->player.angle = 3 * M_PI / 2;
                else if (spawn == 'S')
                    game->player.angle = M_PI / 2;
                else if (spawn == 'E')
                    game->player.angle = 0;
                else
                    game->player.angle = M_PI;
                return;
            }
            j++;
        }
        i++;
    }
}
```

### render.c Mínimo

```c
#include "cub3d.h"

int render_frame(t_game *game)
{
    draw_floor_ceiling(game);
    cast_all_rays(game);
    mlx_put_image_to_window(game->rend.mlx, game->rend.win,
        game->rend.img, 0, 0);
    return (0);
}

void    draw_floor_ceiling(t_game *game)
{
    int x;
    int y;
    
    // Teto
    y = 0;
    while (y < SCREEN_H / 2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            game->rend.img_data[y * SCREEN_W + x] = game->cfg.ceiling_color;
            x++;
        }
        y++;
    }
    
    // Chão
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            game->rend.img_data[y * SCREEN_W + x] = game->cfg.floor_color;
            x++;
        }
        y++;
    }
}
```

### controls.c Simples

```c
#include "cub3d.h"

static int  is_wall(t_game *g, int x, int y)
{
    if (x < 0 || y < 0 || y >= g->cfg.map_height)
        return (1);
    if (!g->cfg.map[y] || x >= (int)ft_strlen(g->cfg.map[y]))
        return (1);
    return (g->cfg.map[y][x] == '1');
}

static void move_player(t_game *g, double forward, double strafe)
{
    double  new_x;
    double  new_y;
    double  dx;
    double  dy;
    
    dx = cos(g->player.angle) * forward + cos(g->player.angle + M_PI/2) * strafe;
    dy = sin(g->player.angle) * forward + sin(g->player.angle + M_PI/2) * strafe;
    
    new_x = g->player.x + dx * MOVE_SPEED;
    new_y = g->player.y + dy * MOVE_SPEED;
    
    if (!is_wall(g, (int)new_x, (int)g->player.y))
        g->player.x = new_x;
    if (!is_wall(g, (int)g->player.x, (int)new_y))
        g->player.y = new_y;
}

int handle_keypress(int key, t_game *game)
{
    if (key == KEY_ESC)
        handle_close(game);
    else if (key == KEY_W)
        move_player(game, 1, 0);
    else if (key == KEY_S)
        move_player(game, -1, 0);
    else if (key == KEY_A)
        move_player(game, 0, -1);
    else if (key == KEY_D)
        move_player(game, 0, 1);
    else if (key == KEY_LEFT)
        game->player.angle -= ROT_SPEED;
    else if (key == KEY_RIGHT)
        game->player.angle += ROT_SPEED;
    return (0);
}

int handle_close(t_game *game)
{
    cleanup(game);
    exit(0);
    return (0);
}
```

---

## 🎯 FOCO: Apenas o DDA (Ray-Casting)

O único algoritmo realmente complexo é o **DDA** em `raycasting.c`.

Vou criar um documento separado com implementação completa e comentada do DDA.

---

## ✅ CHECKLIST FINAL MANDATÓRIO

### Funcionalidades
- [ ] Parser completo (texturas, cores, mapa)
- [ ] Validação completa (sem bugs)
- [ ] Visão 3D com ray-casting
- [ ] 4 texturas nas paredes
- [ ] Chão colorido
- [ ] Teto colorido
- [ ] Movimento WASD
- [ ] Rotação setas
- [ ] ESC fecha
- [ ] X fecha

### Qualidade
- [ ] Norma 42 OK
- [ ] Sem memory leaks
- [ ] Sem crashes
- [ ] README completo
- [ ] Makefile correto

---

## 📊 DIFERENÇAS: Completo vs. Mandatório

| Aspecto | Completo (com bônus) | Mandatório |
|---------|---------------------|------------|
| **Tempo** | 41-60h | 20-28h |
| **Arquivos .c** | 25-30 | 13 |
| **Linhas** | 2000-3000 | 1000-1500 |
| **Complexidade** | Alta | Média |
| **Struct t_game** | 7 sub-structs | 3 sub-structs |
| **Minimapa** | Sim | Não |
| **Colisão avançada** | Sim | Básica |
| **Sprites** | Sim | Não |
| **Mouse** | Sim | Não |

**Economia**: ~50% menos tempo e código!

---

## 🚀 COMECE AGORA

**Ordem de execução**:

1. **HOJE**: Corrigir bugs (FASE 0)
2. **AMANHÃ**: Criar estrutura base (FASE 1 + 2)
3. **DEPOIS**: Ray-casting (FASE 3) — maior esforço
4. **FINAL**: Texturas + Controles + Polimento (FASE 4-6)

**Próximo passo**:
```bash
# Voltar ao projeto
cd ~/projects/cub3D

# Corrigir bugs identificados
vim srcs/parse/validate_tex.c
```

---

**Foco no essencial. Sem distrações. Mandatório primeiro! 🎯**

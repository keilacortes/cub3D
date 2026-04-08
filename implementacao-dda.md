# 🔦 IMPLEMENTAÇÃO COMPLETA — Ray-Casting DDA

## 🎯 O QUE É DDA?

**DDA (Digital Differential Analyzer)** é um algoritmo que traça uma linha no grid do mapa, detectando quando o raio colide com uma parede.

### Analogia Simples
Imagine um laser pointer atravessando um tabuleiro de xadrez. O DDA "anda" de quadrado em quadrado até atingir uma parede.

---

## 📐 MATEMÁTICA BÁSICA

### Conceitos Necessários

```
1. Direção do raio (dx, dy):
   dx = cos(ângulo)  // Componente X
   dy = sin(ângulo)  // Componente Y

2. Posição no mapa:
   mapX = (int)player.x
   mapY = (int)player.y

3. Step (direção do avanço):
   stepX = 1 (se dx > 0) ou -1 (se dx < 0)
   stepY = 1 (se dy > 0) ou -1 (se dy < 0)

4. Delta (distância entre interseções):
   deltaDistX = |1 / dx|
   deltaDistY = |1 / dy|
```

---

## 💻 IMPLEMENTAÇÃO COMPLETA

### raycasting.c

```c
#include "cub3d.h"

// Struct para dados do raio (local)
typedef struct s_ray_data
{
    double  camera_x;       // Posição na tela (-1 a 1)
    double  ray_dir_x;      // Direção X do raio
    double  ray_dir_y;      // Direção Y do raio
    int     map_x;          // Posição X no mapa
    int     map_y;          // Posição Y no mapa
    double  side_dist_x;    // Distância até próxima linha vertical
    double  side_dist_y;    // Distância até próxima linha horizontal
    double  delta_dist_x;   // Distância entre linhas verticais
    double  delta_dist_y;   // Distância entre linhas horizontais
    int     step_x;         // Direção do step X (+1 ou -1)
    int     step_y;         // Direção do step Y (+1 ou -1)
    int     hit;            // Flag: colidiu com parede?
    int     side;           // 0 = vertical (E/W), 1 = horizontal (N/S)
    double  perp_wall_dist; // Distância perpendicular à parede
    int     wall_dir;       // Índice da textura (NORTH/SOUTH/EAST/WEST)
    double  wall_x;         // Posição exata onde raio atingiu (0.0 a 1.0)
}   t_ray_data;

// PASSO 1: Inicializar raio
static void init_ray(t_game *g, t_ray_data *r, int x)
{
    // Converter coluna da tela para coordenada de câmera (-1 a 1)
    r->camera_x = 2 * x / (double)SCREEN_W - 1;
    
    // Calcular direção do raio usando o plano da câmera
    // plane_x e plane_y representam o vetor perpendicular à direção
    double plane_x = -sin(g->player.angle) * tan(g->player.fov / 2);
    double plane_y = cos(g->player.angle) * tan(g->player.fov / 2);
    
    r->ray_dir_x = cos(g->player.angle) + plane_x * r->camera_x;
    r->ray_dir_y = sin(g->player.angle) + plane_y * r->camera_x;
    
    // Posição inicial no mapa
    r->map_x = (int)g->player.x;
    r->map_y = (int)g->player.y;
    
    // Calcular delta (distância entre interseções no grid)
    if (r->ray_dir_x == 0)
        r->delta_dist_x = 1e30;  // Infinity
    else
        r->delta_dist_x = fabs(1 / r->ray_dir_x);
    
    if (r->ray_dir_y == 0)
        r->delta_dist_y = 1e30;
    else
        r->delta_dist_y = fabs(1 / r->ray_dir_y);
    
    r->hit = 0;
}

// PASSO 2: Calcular step e sideDist inicial
static void calc_step_and_sidedist(t_game *g, t_ray_data *r)
{
    // Step e sideDist para X
    if (r->ray_dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - g->player.x) * r->delta_dist_x;
    }
    
    // Step e sideDist para Y
    if (r->ray_dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - g->player.y) * r->delta_dist_y;
    }
}

// PASSO 3: Loop DDA (encontrar parede)
static void perform_dda(t_game *g, t_ray_data *r)
{
    while (r->hit == 0)
    {
        // Avançar para próxima interseção (X ou Y)
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;  // Parede vertical (E ou W)
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y;
            r->side = 1;  // Parede horizontal (N ou S)
        }
        
        // Verificar se atingiu parede
        if (r->map_x < 0 || r->map_y < 0 || 
            r->map_y >= g->cfg.map_height ||
            r->map_x >= (int)ft_strlen(g->cfg.map[r->map_y]))
        {
            r->hit = 1;  // Fora do mapa = parede
        }
        else if (g->cfg.map[r->map_y][r->map_x] == '1')
        {
            r->hit = 1;  // Encontrou parede
        }
    }
}

// PASSO 4: Calcular distância perpendicular (evita fish-eye)
static void calc_wall_distance(t_game *g, t_ray_data *r)
{
    if (r->side == 0)  // Parede vertical
    {
        r->perp_wall_dist = (r->map_x - g->player.x + 
            (1 - r->step_x) / 2) / r->ray_dir_x;
    }
    else  // Parede horizontal
    {
        r->perp_wall_dist = (r->map_y - g->player.y + 
            (1 - r->step_y) / 2) / r->ray_dir_y;
    }
}

// PASSO 5: Determinar direção da parede (qual textura usar)
static void get_wall_direction(t_ray_data *r)
{
    if (r->side == 0)  // Parede vertical
    {
        if (r->step_x > 0)
            r->wall_dir = EAST;
        else
            r->wall_dir = WEST;
    }
    else  // Parede horizontal
    {
        if (r->step_y > 0)
            r->wall_dir = SOUTH;
        else
            r->wall_dir = NORTH;
    }
}

// PASSO 6: Calcular posição exata onde raio atingiu parede
static void calc_wall_x(t_game *g, t_ray_data *r)
{
    if (r->side == 0)  // Parede vertical
        r->wall_x = g->player.y + r->perp_wall_dist * r->ray_dir_y;
    else  // Parede horizontal
        r->wall_x = g->player.x + r->perp_wall_dist * r->ray_dir_x;
    
    // Obter apenas a parte fracionária (0.0 a 1.0)
    r->wall_x -= floor(r->wall_x);
}

// PASSO 7: Desenhar coluna da parede
static void draw_wall_column(t_game *g, t_ray_data *r, int x)
{
    int         line_height;
    int         draw_start;
    int         draw_end;
    int         y;
    int         tex_x;
    int         tex_y;
    double      step;
    double      tex_pos;
    t_texture   *tex;
    int         color;
    
    // Calcular altura da linha na tela
    line_height = (int)(SCREEN_H / r->perp_wall_dist);
    
    // Calcular onde desenhar (início e fim)
    draw_start = -line_height / 2 + SCREEN_H / 2;
    if (draw_start < 0)
        draw_start = 0;
    
    draw_end = line_height / 2 + SCREEN_H / 2;
    if (draw_end >= SCREEN_H)
        draw_end = SCREEN_H - 1;
    
    // Selecionar textura correta
    tex = &g->rend.textures[r->wall_dir];
    
    // Calcular X da textura
    tex_x = (int)(r->wall_x * tex->width);
    if ((r->side == 0 && r->ray_dir_x > 0) || 
        (r->side == 1 && r->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    
    // Calcular step e posição inicial na textura
    step = 1.0 * tex->height / line_height;
    tex_pos = (draw_start - SCREEN_H / 2 + line_height / 2) * step;
    
    // Desenhar coluna pixel por pixel
    y = draw_start;
    while (y < draw_end)
    {
        // Calcular Y da textura
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        
        // Obter cor do pixel da textura
        color = tex->data[tex->height * tex_y + tex_x];
        
        // Aplicar shading (paredes horizontais mais escuras)
        if (r->side == 1)
            color = (color >> 1) & 0x7F7F7F;  // Dividir por 2 (mais escuro)
        
        // Desenhar pixel
        g->rend.img_data[y * SCREEN_W + x] = color;
        y++;
    }
}

// FUNÇÃO PRINCIPAL: Lançar todos os raios
void    cast_all_rays(t_game *game)
{
    t_ray_data  ray;
    int         x;
    
    x = 0;
    while (x < SCREEN_W)
    {
        // 1. Inicializar raio
        init_ray(game, &ray, x);
        
        // 2. Calcular step e sideDist
        calc_step_and_sidedist(game, &ray);
        
        // 3. Executar DDA
        perform_dda(game, &ray);
        
        // 4. Calcular distância
        calc_wall_distance(game, &ray);
        
        // 5. Determinar direção
        get_wall_direction(&ray);
        
        // 6. Calcular wall_x
        calc_wall_x(game, &ray);
        
        // 7. Desenhar coluna
        draw_wall_column(game, &ray, x);
        
        x++;
    }
}
```

---

## 🎨 VERSÃO SIMPLIFICADA (Cores Sólidas)

Para testar o DDA antes de implementar texturas:

```c
// draw_wall_column_simple() — Versão sem texturas
static void draw_wall_column_simple(t_game *g, t_ray_data *r, int x)
{
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     y;
    int     color;
    
    line_height = (int)(SCREEN_H / r->perp_wall_dist);
    
    draw_start = -line_height / 2 + SCREEN_H / 2;
    if (draw_start < 0)
        draw_start = 0;
    
    draw_end = line_height / 2 + SCREEN_H / 2;
    if (draw_end >= SCREEN_H)
        draw_end = SCREEN_H - 1;
    
    // Cores diferentes por direção
    if (r->wall_dir == NORTH)
        color = 0xFF0000;  // Vermelho
    else if (r->wall_dir == SOUTH)
        color = 0x0000FF;  // Azul
    else if (r->wall_dir == EAST)
        color = 0x00FF00;  // Verde
    else
        color = 0xFFFF00;  // Amarelo
    
    // Aplicar shading
    if (r->side == 1)
        color = (color >> 1) & 0x7F7F7F;
    
    // Desenhar coluna
    y = draw_start;
    while (y < draw_end)
    {
        g->rend.img_data[y * SCREEN_W + x] = color;
        y++;
    }
}
```

**Teste**:
1. Primeiro implemente a versão simples
2. Teste se visão 3D funciona
3. Depois substitua por versão com texturas

---

## 🐛 DEBUG

### Adicionar Prints de Debug

```c
// No início de perform_dda()
printf("Starting DDA at map[%d][%d]\n", r->map_y, r->map_x);
printf("Ray direction: (%.2f, %.2f)\n", r->ray_dir_x, r->ray_dir_y);

// Quando encontrar parede
printf("Hit wall at map[%d][%d], side=%d\n", r->map_y, r->map_x, r->side);
printf("Distance: %.2f\n", r->perp_wall_dist);
```

### Problemas Comuns

| Sintoma | Causa Provável | Solução |
|---------|----------------|---------|
| Tela preta | Raio nunca colide | Verificar validação de parede |
| Fish-eye effect | Distância euclidiana | Usar `perp_wall_dist` |
| Texturas espelhadas | `tex_x` invertido | Ajustar lógica de inversão |
| Crashes | Acesso fora do array | Validar `map_x` e `map_y` |
| Linhas verticais | `delta_dist` errado | Verificar divisão por zero |

---

## 📊 VISUALIZAÇÃO DO DDA

```
Grid do Mapa:
    0   1   2   3   4
  +---+---+---+---+---+
0 | 1 | 1 | 1 | 1 | 1 |
  +---+---+---+---+---+
1 | 1 | 0 | 0 | 0 | 1 |
  +---+---+---+---+---+
2 | 1 | 0 | P→ | 0 | 1 |  P = Player (2.5, 2.5)
  +---+---+---+---+---+
3 | 1 | 0 | 0 | 0 | 1 |
  +---+---+---+---+---+
4 | 1 | 1 | 1 | 1 | 1 |
  +---+---+---+---+---+

Raio apontando para LESTE (→):
- Início: (2.5, 2.5)
- Direção: (1.0, 0.0)
- Passos:
  1. (2.5, 2.5) → avança X → (3, 2.5)
  2. (3, 2.5) → avança X → (4, 2.5)
  3. (4, 2.5) → HIT! (parede em map[2][4])

Distância percorrida: 1.5 unidades
```

---

## ✅ CHECKLIST DE IMPLEMENTAÇÃO

### Fase 1: DDA Básico (Cores Sólidas)
- [ ] Criar `srcs/render/raycasting.c`
- [ ] Implementar `init_ray()`
- [ ] Implementar `calc_step_and_sidedist()`
- [ ] Implementar `perform_dda()`
- [ ] Implementar `calc_wall_distance()`
- [ ] Implementar `get_wall_direction()`
- [ ] Implementar `draw_wall_column_simple()`
- [ ] Implementar `cast_all_rays()`
- [ ] Testar com cores sólidas

### Fase 2: Adicionar Texturas
- [ ] Implementar `calc_wall_x()`
- [ ] Modificar para `draw_wall_column()` com texturas
- [ ] Adicionar shading
- [ ] Testar com texturas carregadas

---

## 🎯 TESTE PASSO A PASSO

```bash
# 1. Compilar
make re

# 2. Executar
./cub3D maps/simple.cub

# 3. Verificar
# - Deve aparecer visão 3D
# - Paredes com cores diferentes
# - Movimento funcional

# 4. Debug
# - Adicionar prints se algo estranho
# - Verificar ângulos e distâncias

# 5. Valgrind
make valgrind ARGS="maps/simple.cub"
```

---

## 📚 RECURSOS

- **Lode's Tutorial**: https://lodev.org/cgtutor/raycasting.html
  - Seção: "DDA Algorithm"
  - Leia pelo menos 3x!

- **Visualização interativa**: https://www.playfuljs.com/a-first-person-engine-in-265-lines/

---

**O DDA é o coração do Cub3D. Entenda bem e o resto é fácil! 🎯**

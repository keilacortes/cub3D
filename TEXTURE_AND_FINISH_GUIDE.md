# cub3D — Texturas e finalização (baseado no estado atual)

Este guia foi refeito com base no código atual de `srcs/render/*.c`, que já está renderizando, permitindo movimentação e rotação.

## 1) Estado real do raycasting hoje

### Já está funcionando
- Pipeline por coluna (`init_ray -> calc_step_side -> run_dda -> calc_wall_height -> draw_wall_column`).
- DDA com proteção de borda via `get_map_cell`.
- Floor/ceiling por cor.
- Janela abre e player movimenta.
- Parsing/validação de mapa já estão sólidos (inclui checagem de arquivo de textura em disco com `check_file_tex`).
- Minimap existe e funciona, mas está comentado no `game_loop` para focar no 3D.

### Pendências/ajustes imediatos antes de texturizar
1. Em `ray_project.c`, no caso `side == 1`, o divisor está errado:
   - atual: `... / ray->ray_dir_x`
   - correto: `... / ray->ray_dir_y`
2. Em `render_3d.c`, cor `0x009CC` está incompleta (hex de 24 bits inconsistente).
3. `cleanup_game.c` ainda não destrói `game->screen.img`.

---

## 2) Como preparar estrutura de textura

Hoje `t_textures` guarda só os paths (`north/south/west/east`).  
Para texturizar parede, você precisa guardar também as imagens carregadas.

## 2.1 Atualização de estrutura (sugestão)

```c
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_textures;
```

> Se quiser, adicione `int width` e `int height` em `t_img` para simplificar mapeamento `tex_x/tex_y`.

---

## 3) Carregamento de texturas XPM

Crie `srcs/render/texture_load.c` com:
- `load_one_texture(void *mlx, char *path, t_img *tex)`
- `load_textures(t_game *game)`

Fluxo:
1. `mlx_xpm_file_to_image(...)`
2. `mlx_get_data_addr(...)`
3. erro explícito se qualquer passo falhar

Chamada em `main.c`: depois de criar `mlx`, janela e `screen`, antes de `setup_hooks`.

Observação: o parser já valida existência dos arquivos XPM (`check_file_tex`), então essa etapa aqui é só carregamento MLX e preparação de buffer.

---

## 4) Integrar textura no render atual (sem refatorar tudo)

Você já tem `draw_wall_column(game, ray, x)`.  
Troca interna dessa função:

1. escolher textura por face (`NO/SO/WE/EA`) usando `ray->side`, `ray->step_x`, `ray->step_y`;
2. calcular `wall_x` (ponto fracionário da parede);
3. calcular `tex_x`;
4. iterar `y` e calcular `tex_y`;
5. pegar pixel da textura e chamar `put_pixel`.

### Regra de face (padrão)
- `side == 0 && step_x > 0` -> WE
- `side == 0 && step_x < 0` -> EA
- `side == 1 && step_y > 0` -> NO
- `side == 1 && step_y < 0` -> SO

Se ficar invertido visualmente, troque os pares mantendo consistência.

---

## 5) Fórmulas de mapeamento (adaptadas ao seu pipeline)

Após `calc_wall_height`:

```c
if (ray->side == 0)
	wall_x = game->player.pos_y + ray->perp_dist * ray->ray_dir_y;
else
	wall_x = game->player.pos_x + ray->perp_dist * ray->ray_dir_x;
wall_x -= floor(wall_x);
tex_x = (int)(wall_x * tex_w);
```

Espelhamento comum:

```c
if (ray->side == 0 && ray->ray_dir_x > 0)
	tex_x = tex_w - tex_x - 1;
if (ray->side == 1 && ray->ray_dir_y < 0)
	tex_x = tex_w - tex_x - 1;
```

Vertical:

```c
step = (double)tex_h / ray->line_height;
tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
```

No loop de `y`, `tex_y = (int)tex_pos`, incrementa `tex_pos += step`.

---

## 6) Cleanup para fechar o obrigatório

Em `cleanup_game.c`:
1. destruir `screen.img`;
2. destruir `tex.no.img`, `tex.so.img`, `tex.we.img`, `tex.ea.img` (quando existirem);
3. destruir janela;
4. destruir display;
5. liberar `mlx` (Linux) se seu fluxo exigir.

Hoje isso ainda está incompleto e pode gerar leak.

---

## 7) Correções críticas no código atual (antes de texturas)

1. `srcs/render/ray_project.c`: no caso `side == 1`, trocar divisor para `ray->ray_dir_y`.
2. `srcs/render/render_3d.c`: corrigir cor `0x009CC` para um valor RGB válido (ex.: `0x0099CC`).
3. `srcs/cleanup_game.c`: destruir `game->screen.img` com `mlx_destroy_image`.

---

## 8) Ordem recomendada daqui até concluir

1. Aplicar as correções críticas da seção anterior.
2. Adicionar `t_img` em `t_textures` e inicializar no `init_game`.
3. Implementar `texture_load.c` e chamar `load_textures` no `main`.
4. Texturizar `draw_wall_column`.
5. Completar cleanup (screen + texturas MLX).
6. Rodar checklist final (build, execução, mapa inválido, fechamento, norminette, valgrind).

---

## 9) Checklist final de entrega (mandatório)

- [ ] Raycasting estável sem distorção grave.
- [ ] NO/SO/WE/EA aplicadas corretamente.
- [ ] Floor e ceiling por cor.
- [ ] Movimento/rotação funcionais com colisão aceitável.
- [ ] Parsing e validação de mapa robustos.
- [ ] `ray_project.c` usando `ray_dir_y` no ramo `side == 1`.
- [ ] Cor de parede em hexadecimal RGB válido.
- [ ] ESC e X fecham com cleanup correto.
- [ ] `screen.img` e texturas destruídas no cleanup.
- [ ] `make/re/clean/fclean` OK.
- [ ] Norminette OK.
- [ ] Sem leaks relevantes.

# cub3D - Conceitos por tras do projeto

Este documento explica os conceitos tecnicos usados no projeto, com base no codigo atual.

---

## 1) Objetivo do projeto

O `cub3D` implementa um renderizador 3D em primeira pessoa usando **raycasting** sobre um mapa 2D em grade.

Em vez de desenhar geometria 3D real (triangulos), o projeto:
1. interpreta o mundo como uma matriz de celulas (`1`, `0`, etc.),
2. lanca um raio por coluna da tela,
3. encontra a parede atingida,
4. projeta a altura dessa parede no plano da tela,
5. aplica textura na coluna desenhada.

---

## 2) Modelo de mundo (2D) e dados principais

No `inc/cub3d.h`, as estruturas centrais sao:

- `t_map`: grade (`char **grid`), altura e spawn.
- `t_player`: posicao (`pos_x`, `pos_y`), direcao (`dir_x`, `dir_y`) e plano da camera (`plane_x`, `plane_y`).
- `t_ray`: estado do raio durante o calculo (direcao, delta distancias, passos, hit, distancia perpendicular, etc.).
- `t_textures`: caminhos de textura, cores de piso/teto e imagens carregadas (`t_img`).
- `t_game`: estado global do jogo (mapa, jogador, texturas, janela e framebuffer).

Conceito importante:
- O mundo e 2D (top-down), mas a visualizacao projetada e 3D.

---

## 3) Pipeline geral do programa

Fluxo alto nivel:

1. `main.c`
   - inicializa estado do jogo,
   - parseia arquivo `.cub`,
   - inicializa MLX/janela/framebuffer,
   - carrega texturas,
   - registra hooks,
   - entra no loop (`mlx_loop`).

2. Loop de jogo (`game_loop` em `controls/minimap.c`)
   - atualiza movimento do jogador (`handle_movement`),
   - renderiza frame 3D (`render_3d`),
   - desenha minimap por cima (`draw_minimap`).

---

## 4) Parsing e validacao do `.cub`

Arquivos: `parse_file.c`, `parse_map.c`, `validate_map.c`, `player_spawn.c`, `validate_tex.c`, `parse_utils.c`.

### 4.1 Elementos de configuracao

`parse_file.c` extrai:
- texturas `NO`, `SO`, `WE`, `EA`,
- cores `F` (floor) e `C` (ceiling) em RGB.

Regras aplicadas:
- cada cor deve ter exatamente 3 componentes,
- cada componente precisa estar em `[0, 255]`,
- todas as texturas precisam existir e abrir no sistema.

### 4.2 Extracao do mapa

`parse_map.c`:
- copia o arquivo inteiro para memoria,
- considera o **bloco final de linhas nao vazias** como mapa,
- duplica esse bloco em `map->grid`.

Implicacao de design:
- o mapa deve estar no fim do `.cub`.

### 4.3 Spawn e orientacao inicial

`player_spawn.c`:
- aceita um unico spawn (`N`, `S`, `E`, `W`),
- define:
  - vetor de direcao (`dir_x`, `dir_y`),
  - plano da camera (`plane_x`, `plane_y`) com FOV aproximado via `0.66`.

### 4.4 Validacao do mapa

`validate_map.c` valida:
- caracteres permitidos (`1`, `0`, espaco, `NSEW`),
- existencia de spawn unico,
- fechamento do mapa.

A verificacao de fechamento usa duas ideias:
1. para cada celula caminhavel (`0` ou spawn), checar vizinhos cardinais,
2. se algum vizinho for espaco, `\0` ou fora da area valida, o mapa nao e fechado.

---

## 5) Fundamentos de raycasting no projeto

Arquivos: `ray_init.c`, `ray_dda.c`, `ray_project.c`, `render_3d.c`, `render_walls.c`.

### 5.1 Camera e raio por coluna

Para cada coluna `x` da tela:

1. normaliza para espaco da camera:
   - `camera_x = 2 * x / WIDTH - 1` (intervalo `[-1, 1]`).
2. calcula direcao do raio:
   - `ray_dir = dir + plane * camera_x`.

Isso gera raios diferentes para cada coluna e simula FOV.

### 5.2 DDA (Digital Differential Analyzer)

Objetivo: caminhar celula por celula no grid ate encontrar parede.

Passos:
1. calcula `delta_dist_x` e `delta_dist_y` (custo para cruzar uma linha de grade em cada eixo),
2. define `step_x` e `step_y` (direcao +1 ou -1),
3. inicializa `side_dist_x` e `side_dist_y`,
4. em loop:
   - avanca no menor `side_dist`,
   - marca se bateu em lado X ou Y,
   - para quando celula for parede.

No codigo, `get_map_cell` trata espacos e fora dos limites como parede, robustecendo o cast.

### 5.3 Distancia perpendicular e projecao

Depois do hit:
- calcula `perp_dist` (distancia perpendicular a camera) para evitar efeito fish-eye,
- calcula altura da parede:
  - `line_height = HEIGHT / perp_dist`,
- calcula faixa vertical:
  - `draw_start`, `draw_end`, com clamp na tela.

### 5.4 Mapeamento de textura

Em `render_walls.c`:
1. escolhe textura conforme lado atingido e direcao do passo,
2. calcula `wall_x` (ponto fracionario do impacto na parede),
3. converte para `tex_x`,
4. possivelmente espelha `tex_x` dependendo do lado/direcao,
5. varre `y` de `draw_start` a `draw_end`, calculando `tex_y` por incremento (`tex_pos += step`).

Resultado: cada coluna de tela recebe pixels da textura correta.

---

## 6) Piso e teto

`render_3d.c` desenha primeiro piso/teto no framebuffer:
- metade superior com cor `ceiling`,
- metade inferior com cor `floor`.

Depois as paredes sao desenhadas por cima.

---

## 7) Movimento, colisao e rotacao

Arquivo: `controls/movement.c`.

### 7.1 Input por estado de tecla

`hooks.c` nao move o jogador diretamente.
Ele apenas liga/desliga flags (`keys.w`, `keys.a`, etc.).
O movimento real ocorre no loop (`handle_movement`), garantindo atualizacao continua por frame.

### 7.2 Colisao

Antes de atualizar posicao:
- testa se a celula alvo e diferente de `'1'`.

A movimentacao separa eixo X e Y para reduzir "travar diagonal" em quinas.

### 7.3 Rotacao

Rotacao usa matriz 2D:
- atualiza vetor de direcao,
- atualiza plano da camera.

Isso gira a camera sem alterar posicao.

---

## 8) Minimap

Arquivo: `controls/minimap.c`.

O minimap:
- desenha celulas do mapa com escala fixa (`MINIMAP_SCALE`),
- marca jogador,
- desenha direcao do jogador.

Detalhe importante de implementacao:
- o desenho e feito no **framebuffer** (`game->screen`) e nao direto na janela,
- isso evita flickering entre `mlx_put_image_to_window` e desenho overlay.

---

## 9) Ciclo de render por frame

Sequencia atual:
1. `handle_movement`
2. `render_3d`
   - floor/ceiling
   - raycast por coluna
   - draw walls texturizadas
   - `mlx_put_image_to_window`
3. `draw_minimap` (overlay no mesmo buffer de frame)

---

## 10) Gerenciamento de recursos

Arquivos: `texture_load.c`, `cleanup_game.c`.

- Texturas XPM sao carregadas com `mlx_xpm_file_to_image`.
- Endereco bruto do pixel buffer e obtido com `mlx_get_data_addr`.
- No fechamento:
  - destroi imagens,
  - destroi janela,
  - destroi display do MLX,
  - libera memoria de contexto.

---

## 11) Build e dependencias

`Makefile`:
- compila `libft` e `minilibx` locais,
- compila fontes em `obj/`,
- linka com X11 e math (`-lXext -lX11 -lm -lz`),
- oferece `clean`, `fclean`, `re` e `valgrind`.

---

## 12) Limitacoes atuais (do codigo atual)

Com base no estado atual:
- sem rotacao por mouse (apenas teclado),
- sem sprites/entidades 3D adicionais,
- sem portas animadas,
- sem sistema de iluminacao dinamica.

O foco esta em raycasting classico com mapa estatico, texturas e navegacao fluida.

---

## 13) Resumo conceitual rapido

Se voce lembrar de 5 ideias, sao estas:

1. O mundo e uma grade 2D de tiles.
2. Cada coluna da tela recebe um raio.
3. DDA encontra a primeira parede do raio.
4. Distancia perpendicular vira altura projetada.
5. `wall_x/tex_x/tex_y` mapeiam textura para os pixels da coluna.

Essas cinco etapas transformam um mapa 2D em uma visao 3D em tempo real.

---

## 14) Onde cada conceito aparece no codigo

### 14.1 Inicializacao e ciclo principal

- Entrada do programa: `srcs/main.c:59` -> `main`
- Estado inicial do jogo: `srcs/main.c:41` -> `init_game`
- Inicializacao de janela/framebuffer MLX: `srcs/main.c:32` -> `init_mlx`
- Registro de hooks/eventos: `srcs/controls/hooks.c:51` -> `setup_hooks`
- Loop por frame: `srcs/controls/minimap.c:91` -> `game_loop`

### 14.2 Parsing do `.cub`

- Parse dos elementos (`NO/SO/WE/EA/F/C`): `srcs/parse/parse_file.c:43` -> `parse_elements`
- Validacao de cores RGB: `srcs/parse/parse_file.c:78` -> `validate_colors`
- Orquestracao do parse: `srcs/parse/parse_file.c:98` -> `parse_file`
- Extracao do bloco de mapa: `srcs/parse/parse_map.c:97` -> `parse_map`

### 14.3 Spawn e validacao de mapa

- Conversao de tile `N/S/E/W` em estado do player: `srcs/parse/player_spawn.c:55` -> `player_pos`
- Validacao de caracteres/tile: `srcs/parse/validate_map.c:15` -> `validate_tile`
- Varredura global de caracteres do mapa: `srcs/parse/validate_map.c:31` -> `validate_char`
- Validacao de vizinhanca/fechamento: `srcs/parse/validate_map.c:50` -> `check_neighbors`
- Validacao final de fechamento: `srcs/parse/validate_map.c:70` -> `validate_path`
- Entrada da validacao do mapa: `srcs/parse/validate_map.c:93` -> `validate_map`

### 14.4 Raycasting (core)

- Inicializacao do raio por coluna: `srcs/render/ray_init.c:27` -> `init_ray`
- Calculo de passos/distancias iniciais DDA: `srcs/render/ray_init.c:38` -> `calc_step_side`
- Loop DDA ate hit: `srcs/render/ray_dda.c:43` -> `run_dda`
- Projecao de parede na tela: `srcs/render/ray_project.c:23` -> `calc_wall_height`
- Orquestracao do render por coluna: `srcs/render/render_3d.c:52` -> `render_3d`

### 14.5 Textura e rasterizacao de parede

- Selecao da textura por lado: `srcs/render/render_walls.c:25` -> `get_texture`
- Coordenada fracionaria de impacto: `srcs/render/render_walls.c:38` -> `get_wall_x`
- Amostragem vertical de textura (`tex_y`): `srcs/render/render_walls.c:49` -> `draw_tex_pixels`
- Render da coluna de parede texturizada: `srcs/render/render_walls.c:71` -> `draw_wall_column`

### 14.6 Input, movimento e rotacao

- Tecla pressionada (set de flags): `srcs/controls/hooks.c:15` -> `key_press`
- Tecla solta (clear de flags): `srcs/controls/hooks.c:34` -> `key_release`
- Atualizacao de movimento por frame: `srcs/controls/movement.c:58` -> `handle_movement`
- Rotacao com trigonometria: `srcs/controls/movement.c:41` -> `rotate`

### 14.7 Minimap e overlay

- Desenho do minimap: `srcs/controls/minimap.c:67` -> `draw_minimap`
- Ordem do frame (`movimento -> render_3d -> minimap`): `srcs/controls/minimap.c:91` -> `game_loop`

### 14.8 Recursos e encerramento

- Carregamento de texturas XPM: `srcs/render/texture_load.c:27` -> `load_textures`
- Limpeza de imagens/janela/display: `srcs/cleanup_game.c:15` -> `cleanup_game`
- Fechamento do jogo: `srcs/cleanup_game.c:38` -> `close_game`

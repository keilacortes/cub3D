# Próximos passos do Raycast (a partir da etapa 2)

## Estado atual confirmado no projeto

- **Parsing e validação** prontos (`srcs/parse/*.c`): NO/SO/WE/EA, F/C, mapa e spawn.
- **Loop e controles** prontos (`srcs/controls/hooks.c`, `movement.c`, `minimap.c`).
- **Render atual**: apenas minimap 2D em `game_loop()` via `draw_minimap()`.
- **Texturas**: apenas caminhos (`t_textures` em `inc/cub3d.h`), sem carregamento de imagem MLX.
- **Raycast 3D**: ainda não existe módulo em `srcs/render/`.

---

## Objetivo do próximo ciclo

Entregar render 3D por raycasting no loop principal, primeiro com parede sólida (MVP), depois com texturas por face (NO/SO/WE/EA).

---

## Backlog recomendado (ordem de execução)

### 1) Preparar estruturas para render 3D

**Arquivos**
- `inc/cub3d.h`
- `srcs/main.c`

**Ações**
- Adicionar estrutura de imagem (buffer) para desenho por frame (MLX image + data addr).
- Adicionar campos no `t_game` para buffer de tela.
- Adicionar campos no `t_textures` para imagens carregadas (não só paths).
- Inicializar esses campos em `init_game()`.

**DoD**
- Projeto compila.
- `t_game` e `t_textures` já suportam render por buffer e texturas MLX.

---

### 2) Criar módulo de raycasting

**Arquivos**
- `srcs/render/raycasting.c` (**novo**)
- `inc/cub3d.h`
- `Makefile`

**Ações**
- Criar função principal `render_3d(t_game *game)`.
- Implementar DDA por coluna (um raio por `x` da tela).
- Calcular distância perpendicular para evitar fish-eye.
- Adicionar protótipos no header e incluir o novo `.c` no Makefile.

**DoD**
- Render 3D básico aparece na janela (sem textura ainda).
- Movimento/rotação continuam funcionando.

---

### 3) Integrar raycast no loop principal

**Arquivo**
- `srcs/controls/minimap.c`

**Ações**
- Alterar `game_loop()` para chamar `render_3d(game)`.
- Manter minimap opcional (debug) por cima do 3D ou desabilitar temporariamente.

**DoD**
- `game_loop` usa render 3D em tempo real.
- Não há regressão nos controles.

---

### 4) Carregar texturas XPM em memória MLX

**Arquivos**
- `srcs/parse/validate_tex.c`
- `srcs/main.c`
- `srcs/cleanup_game.c`

**Ações**
- Manter validação de arquivo existente.
- Criar etapa de load (`mlx_xpm_file_to_image`) para NO/SO/WE/EA após `mlx_init()`.
- Salvar ponteiro de pixel (`mlx_get_data_addr`) de cada textura.
- Destruir imagens no cleanup.

**DoD**
- 4 texturas carregadas e liberadas corretamente no encerramento.

---

### 5) Texturizar paredes no raycast

**Arquivo**
- `srcs/render/raycasting.c`

**Ações**
- Determinar face atingida (N/S/E/W) no DDA.
- Selecionar textura correta por face.
- Mapear `tex_x/tex_y` por coluna e amostrar cor via data buffer.
- Renderizar teto/chão com as cores `F` e `C`.

**DoD**
- Paredes texturizadas por face com perspectiva correta.
- Piso e teto renderizados com as cores do `.cub`.

---

### 6) Ajustes de robustez/performance

**Arquivos**
- `srcs/render/raycasting.c`
- `srcs/controls/movement.c`

**Ações**
- Trocar desenho por pixel direto em image buffer (evitar `mlx_pixel_put` no 3D).
- Revisar colisão do player para reduzir clipping em quina.
- Ajustar constantes de velocidade/rotação se necessário.

**DoD**
- Movimento estável e render fluido no mapa de teste.

---

## Pontos de integração críticos

1. `main.c`: criar janela + carregar texturas + criar buffer de frame.
2. `minimap.c::game_loop()`: substituir/combinar `draw_minimap` com `render_3d`.
3. `cleanup_game.c`: destruir todas as imagens MLX adicionadas.
4. `Makefile`: incluir novos arquivos de `srcs/render/`.

---

## Critério de pronto da etapa (MVP + textura)

- `./cub3D maps/simple.cub` abre janela e renderiza 3D.
- WASD e setas funcionam sobre cena 3D.
- Paredes com textura correta por orientação.
- Piso/teto com cores do mapa.

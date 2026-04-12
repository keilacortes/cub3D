# Guia de Desenvolvimento — cub3D (Somente Mandatório)

Este guia foi montado com base no subject `cub3D` (v12.0, pt-BR) e no estado atual deste repositório.

## 1) Escopo fechado (o que entra e o que não entra)

**Foco deste guia:** apenas a parte obrigatória.

**Obrigatório:**
- MiniLibX funcionando com janela estável.
- Renderização **3D em primeira pessoa** usando raycasting.
- 4 texturas de parede (NO/SO/WE/EA) conforme direção da face atingida.
- Cor de chão (F) e teto (C).
- Controles: `W A S D`, setas esquerda/direita, `ESC`, fechar no `X`.
- Parse de `.cub` com validações e mensagens `Error\n...`.

**Fora de escopo (bônus):**
- minimapa, mouse look, portas, sprites animadas etc.

---

## 2) Diagnóstico rápido do repositório atual

## ✅ Já existe (base boa)
- Parser de elementos (`NO/SO/WE/EA/F/C`) em `srcs/parse/parse_file.c`.
- Validação de cores e existência dos arquivos de textura.
- Extração e validação de mapa em `parse_map.c` + `validate_map.c`.
- Spawn com direção inicial (`N/S/E/W`) já convertido para vetores de direção.
- Hooks de teclado e loop principal (`srcs/controls/hooks.c`).
- Movimento e rotação (`srcs/controls/movement.c`).
- `maps/simple.cub` como mapa de teste.

## ⚠️ Falta para cumprir o mandatório
- **Motor de raycasting 3D** (DDA por coluna) ainda não implementado.
- **Render por imagem** (`mlx_new_image` + buffer + `mlx_put_image_to_window`) não integrado.
- **Carregamento das texturas XPM** para uso no raycasting não integrado.
- Há inconsistência estrutural: `main.c` usa `game.mlx/game.win`, mas em `cub3d.h` esses campos estão em `game.rend` (hoje não compila).

## ℹ️ Observação de escopo
- `srcs/controls/minimap.c` é bônus. Pode ficar no projeto, mas não deve atrapalhar o fluxo do mandatório.

---

## 3) Ordem recomendada de implementação (roadmap)

## Fase 0 — Desbloquear build e estrutura base
1. Padronizar acesso aos ponteiros da MLX (`game.rend.mlx`, `game.rend.win`, etc.).
2. Garantir `init_game` inicializando toda a estrutura de render.
3. Ajustar `cleanup_game` para destruir imagem/janela/display com segurança.

**Saída da fase:** projeto compila e abre janela.

## Fase 1 — Pipeline de render por frame
1. Criar imagem off-screen por frame (ou reutilizável) e obter `data`, `bpp`, `size_line`, `endian`.
2. Criar helper de pixel no buffer.
3. Desenhar primeiro só fundo: teto (metade superior) e chão (metade inferior) com as cores `C` e `F`.

**Saída da fase:** janela mostra teto/chão corretamente.

## Fase 2 — Raycasting DDA (núcleo obrigatório)
Para cada coluna `x` da tela:
1. Calcular `camera_x` em `[-1, 1]`.
2. Definir `ray_dir = dir + plane * camera_x`.
3. Inicializar célula do mapa (`map_x`, `map_y`) e `delta_dist`.
4. Definir `step_x/step_y` e `side_dist`.
5. Rodar DDA até colidir em parede (`'1'`).
6. Calcular `perp_wall_dist`.
7. Calcular altura da faixa (`line_height`) e intervalo `draw_start/draw_end`.

**Saída da fase:** paredes em 3D sem textura (cor sólida por face).

## Fase 3 — Texturização por face (NO/SO/WE/EA)
1. Carregar as 4 texturas via `mlx_xpm_file_to_image`.
2. Para cada raio, escolher textura pela face/direção atingida.
3. Calcular coordenada `tex_x` com `wall_x`.
4. Fazer stepping vertical (`tex_pos`, `step`) para `tex_y`.
5. Escrever pixel de textura no buffer.

**Saída da fase:** paredes 3D texturizadas por direção, conforme subject.

## Fase 4 — Integração com movimento/eventos
1. Em cada `game_loop`: atualizar movimento/rotação, renderizar frame completo, mandar para janela.
2. Garantir comportamento suave ao alternar/minimizar janela.
3. ESC e botão X encerrando limpo.

**Saída da fase:** gameplay obrigatório completo.

## Fase 5 — Robustez de parser para avaliação
1. Reforçar regras de `.cub`:
   - mapa por último;
   - elementos em qualquer ordem;
   - múltiplas linhas vazias fora do mapa;
   - espaços no mapa tratados como válidos;
   - erro explícito para configuração inválida.
2. Validar “um e apenas um spawn”.

**Saída da fase:** parser resistente aos casos de avaliação.

---

## 4) Estrutura de módulos sugerida (encaixando no que vocês já têm)

- `srcs/parse/*`: manter parsing/validação.
- `srcs/render/` (novo):
  - `render_frame.c` (pipeline do frame),
  - `raycast.c` (DDA),
  - `textures.c` (load/free/sample),
  - `draw.c` (put pixel, ceiling/floor, wall stripe).
- `srcs/controls/*`: manter hooks e movement.
- `srcs/main.c`: init → parse → init render/texturas → hooks/loop.

Essa separação facilita explicar o projeto na defesa.

---

## 5) Checklist de conformidade (mandatório)

- [ ] Compila com `-Wall -Wextra -Werror`.
- [ ] Executa com `./cub3D map.cub`.
- [ ] Janela abre sem travar.
- [ ] ESC fecha corretamente.
- [ ] X da janela fecha corretamente.
- [ ] W/A/S/D movimentam.
- [ ] Setas esquerda/direita rotacionam visão.
- [ ] Chão e teto com cores distintas (`F`, `C`).
- [ ] Paredes com texturas NO/SO/WE/EA conforme direção.
- [ ] Mapa fechado obrigatório.
- [ ] Erros de `.cub` retornam `Error\n` + mensagem clara.
- [ ] Sem segfault/double free/leaks no fluxo principal.

---

## 6) Casos de teste mínimos para avançar com segurança

1. **Mapa válido mínimo** com 1 spawn.
2. **Extensão inválida** (`.txt`).
3. **Elemento faltando** (ex.: sem `EA`).
4. **Cor inválida** (`F 300,0,0`, `F 10,20`).
5. **Mapa aberto** (vazando para espaço externo).
6. **Dois spawns** e **zero spawn**.
7. **Linhas vazias extras** antes dos elementos e entre elementos.
8. **Mapa com espaços internos**.

---

## 7) Estratégia prática de execução (curta)

1. Primeiro, corrigir a inconsistência estrutural (`game` vs `game.rend`) para voltar a compilar.
2. Implementar raycasting sem textura (visual rápido para depurar matemática).
3. Só então ligar texturas e finalizar parser edge-cases.
4. Deixar minimapa desativável/isolado para não misturar bônus com o obrigatório.

Se seguir essa ordem, você reduz risco e chega mais rápido num mandatório apresentável e defensável.

# ✅ Tasks — cub3D

## 📁 Estrutura do Projeto

- [x] Adicionar a Libft
- [x] Adicionar a minilibX
- [x] Makefile compila com flags `-Wall`, `-Wextra`, `-Werror` usando `cc`
- [x] Criar arquivo `README.md` na raiz do repositório

---

## 🗺️ Parser — Arquivo `.cub`

- [x] Parsear textura Norte (`NO ./path`)
- [x] Parsear textura Sul (`SO ./path`)
- [x] Parsear textura Oeste (`WE ./path`)
- [x] Parsear textura Leste (`EA ./path`)
- [x] Parsear cor do chão — `F R,G,B` (valores entre 0 e 255)
- [x] Parsear cor do teto — `C R,G,B` (valores entre 0 e 255)
- [x] Elementos podem estar em qualquer ordem (exceto o mapa, que deve ser o último)
- [x] Elementos podem ser separados por uma ou mais linhas vazias entre si
- [x] Informações de cada elemento podem ser separadas por um ou mais espaços
- [x] Mapa composto apenas pelos caracteres: `0`, `1`, `N`, `S`, `E`, `W`
- [x] Somente uma posição inicial de jogador (`N`, `S`, `E` ou `W`) no mapa
- [x] Mapa deve ser fechado/cercado de paredes (`1`)
- [x] Qualquer falha de configuração retorna `"Error\n"` + mensagem de erro

---

## 🎮 Engine — Ray-Casting

- [ ] Implementar algoritmo de ray-casting
- [ ] Renderizar visão 3D em primeira pessoa do labirinto
- [ ] Exibir textura diferente para cada direção de parede (N, S, E, O)
- [ ] Renderizar chão com a cor configurada no `.cub`
- [ ] Renderizar teto com a cor configurada no `.cub`

---

## 🖼️ Janela — miniLibX

- [ ] Usar a miniLibX para gerenciar a janela
- [ ] Exibir a imagem renderizada na janela
- [ ] Usar `mlx_image`
- [ ] Gerenciamento suave da janela (minimizar, trocar de janela, etc.)

---

## ⌨️ Controles

- [ ] Seta `←` — rotacionar câmera para a esquerda
- [ ] Seta `→` — rotacionar câmera para a direita
- [ ] Tecla `W` — mover para frente
- [ ] Tecla `S` — mover para trás
- [ ] Tecla `A` — mover para a esquerda
- [ ] Tecla `D` — mover para a direita
- [ ] Tecla `ESC` — fechar janela e encerrar o programa de forma limpa
- [ ] Clicar no `X` da janela — fechar e encerrar de forma limpa

---

## 🛡️ Norma & Qualidade de Código

- [ ] Todo o código segue a Norma da 42
- [ ] Arquivos bônus também seguem a Norma
- [ ] Sem crashes (segfault, bus error, double free, etc.)
- [ ] Toda memória alocada é liberada corretamente (sem memory leaks)

---

## 📄 README.md

- [x] Primeira linha em itálico: `*Este projeto foi criado como parte do currículo da 42 por <login>...*`
- [ ] Seção **Descrição** — objetivo e visão geral do projeto
- [ ] Seção **Instruções** — como compilar, instalar e executar
- [ ] Seção **Recursos** — referências (docs, artigos, tutoriais) + como a IA foi utilizada (quais tarefas e partes do projeto)

---

## ⭐ Bônus *(?)*

- [ ] Colisão com as paredes
- [ ] Minimapa
- [ ] Portas que abrem e fecham
- [ ] Sprite animado
- [ ] Rotação da câmera com o mouse
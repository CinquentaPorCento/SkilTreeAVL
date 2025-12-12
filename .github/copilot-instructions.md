# Copilot / AI Agent Instructions

This repository is a compact C demo implementing an AVL-based "Skill Tree" (árvore de habilidades). The file layout is simple:

- `main.c` — program entry, example usage and high-level scenario.
- `func.h` — contains the AVL implementation (node/skill structs), insertion, search, traversal and a small game-style `desbloquearHabilidade` helper. The header currently also contains full function implementations.
- `output/` — target folder for compiled executable.

Objective for AI contributors
- Make small, focused edits: add new skills, adjust conditions in `desbloquearHabilidade`, improve printing, or refactor AVL logic into `.c` files while keeping behavior unchanged.

Important code patterns and conventions
- Key types: `Habilidade` (skill) and `No` (AVL node).
- Primary functions used from `main.c` and to reference in changes:
  - `No *inserir(No *no, Habilidade hab)` — inserts by `habilidade.id` (unique key).
  - `No *buscar(No *raiz, int id)` — efficient BST/AVL search; returns `No*` or `NULL`.
  - `void inOrder(No *raiz)` — inorder traversal printing `ID, Nome, Custo, Nivel Min`.
  - `void desbloquearHabilidade(No *raiz, int id_habilidade, int pontos_jogador, int nivel_jogador)` — game-logic example that uses `buscar` and prints outcome.

Implementation notes discovered in `func.h`
- `func.h` currently mixes API and implementation (definitions + bodies). If you add new C files, be consistent: either keep inline implementations or split into `func.c` + `func.h` and update includes.
- Error handling: `novoNo` calls `perror` + `exit(EXIT_FAILURE)` on malloc failure — preserve this behavior unless implementing a different allocation strategy.
- Strings and messages are in Portuguese; preserve language for consistency unless the user requests translation.

Build, run and debug
- Build with GCC (MinGW on this workspace). Example PowerShell commands that match the user's environment:
  - Compile:
    ````powershell
    gcc -Wall -Wextra -g3 main.c -o output/main.exe
    ````
  - Run:
    ````powershell
    & .\output\main.exe
    ````
- The provided development task uses a full path to `gcc` in the user's task runner; when editing `tasks.json` or CI, prefer the simpler `gcc` invocation unless absolute paths are required.

Testing and expectations
- There are no unit tests in the repo. Use the sample data in `main.c` to exercise behavior. `main.c` inserts a few `Habilidade` items, prints the tree (`inOrder`) and calls `desbloquearHabilidade` and `buscar`.
- Be mindful that memory-freeing routines (removal / free all nodes) are not implemented — don't assume a destructor exists.

When modifying code, follow these practical rules
- Keep changes minimal and behavior-preserving for existing demos. If changing APIs (e.g., function signatures), update `main.c` and any place that calls them.
- If you split `func.h` into `func.c` + `func.h`, keep exported signatures identical and ensure `main.c` includes `func.h` (no other build-system changes expected).
- Preserve Portuguese log messages and function/variable names unless the user asks for renaming. Example identifiers to keep as-is: `Habilidade`, `No`, `novoNo`, `inserir`, `buscar`, `inOrder`, `desbloquearHabilidade`.

Examples (copy-paste friendly)
- Search for a skill by id (same pattern used in `main.c`):
  ````c
  No *node = buscar(raiz, 7);
  if (node) printf("Encontrado: %s\n", node->habilidade.nome);
  ````
- Insert a new skill (preserve `id` uniqueness):
  ````c
  Habilidade nova = {20, "NomeEx", 4, 2};
  raiz = inserir(raiz, nova);
  ````

If you need clarification
- Ask the repo owner whether they prefer implementations moved out of headers, whether logging should be localized/translated, and whether a memory-free routine is desired.

Next steps for AI agents
- For small changes: edit `func.h` or `main.c` and run the compile/run commands above.
- For refactors: propose splitting `func.h` into `func.c` + `func.h` and include a brief plan in the PR description.

If anything in this summary is unclear or you want a different scope (tests, CI, refactor), please tell me which part to expand.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para uma Habilidade (Skill)
typedef struct Habilidade {
    int id;               // ID único para a habilidade (será a chave da AVL)
    char nome[50];        // Nome da habilidade
    int custo_pontos;     // Custo para desbloquear a habilidade
    int nivel_minimo;     // Nível mínimo do personagem para desbloquear
} Habilidade;

// Definição do Nó da Árvore AVL
typedef struct No {
    Habilidade habilidade;
    struct No *esquerda;
    struct No *direita;
    int altura; // Altura do nó na árvore
} No;

// --- Funções Auxiliares da AVL ---

// Funcao para obter a altura de um nó
int altura(No *N) {
    if (N == NULL)
        return 0;
    return N->altura;
}

// Funcao para obter o maior de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Funcao para criar um novo nó
No *novoNo(Habilidade hab) {
    No *no = (No *)malloc(sizeof(No));
    if (no == NULL) {
        perror("Falha ao alocar memória para novo nó");
        exit(EXIT_FAILURE);
    }
    no->habilidade = hab;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Novo nó é inicialmente adicionado na folha
    return no;
}

// Funcao para rotação simples à direita (Right Rotation)
No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Funcao para rotação simples à esquerda (Left Rotation)
No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Funcao para obter o fator de balanceamento de um nó
int obterFatorBalanceamento(No *N) {
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}

// Funcao de Insercao na AVL com Balanceamento Automatico
No *inserir(No *no, Habilidade hab) {
    // 1. Inserção normal de BST
    if (no == NULL)
        return novoNo(hab);

    if (hab.id < no->habilidade.id)
        no->esquerda = inserir(no->esquerda, hab);
    else if (hab.id > no->habilidade.id)
        no->direita = inserir(no->direita, hab);
    else // Chaves iguais não são permitidas
        return no;

    // 2. Atualiza a altura do nó ancestral
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // 3. Obtém o fator de balanceamento para verificar se o nó ficou desbalanceado
    int balanceamento = obterFatorBalanceamento(no);

    // 4. Se o nó estiver desbalanceado, há 4 casos

    // Caso Esquerda-Esquerda (LL)
    if (balanceamento > 1 && hab.id < no->esquerda->habilidade.id)
        return rotacaoDireita(no);

    // Caso Direita-Direita (RR)
    if (balanceamento < -1 && hab.id > no->direita->habilidade.id)
        return rotacaoEsquerda(no);

    // Caso Esquerda-Direita (LR)
    if (balanceamento > 1 && hab.id > no->esquerda->habilidade.id) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita-Esquerda (RL)
    if (balanceamento < -1 && hab.id < no->direita->habilidade.id) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // Retorna o ponteiro do nó (inalterado se balanceado)
    return no;
}

// Funcao de Busca Eficiente de Dados
No *buscar(No *raiz, int id) {
    // Caso base: a raiz é nula ou o ID está na raiz
    if (raiz == NULL || raiz->habilidade.id == id)
        return raiz;

    // ID é maior que o ID da raiz
    if (raiz->habilidade.id < id)
        return buscar(raiz->direita, id);

    // ID é menor que o ID da raiz
    return buscar(raiz->esquerda, id);
}

// Função para percorrer e imprimir a Árvore de Habilidades (Inorder)
void inOrder(No *raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esquerda);
        printf("ID: %d | Nome: %s | Custo: %d | Nivel Min: %d | Altura: %d\n",
               raiz->habilidade.id, raiz->habilidade.nome,
               raiz->habilidade.custo_pontos, raiz->habilidade.nivel_minimo,
               raiz->altura);
        inOrder(raiz->direita);
    }
}

// Função de exemplo para 'desbloquear' uma habilidade no jogo
void desbloquearHabilidade(No *raiz, int id_habilidade, int pontos_jogador, int nivel_jogador) {
    No *skill_node = buscar(raiz, id_habilidade);

    if (skill_node == NULL) {
        printf("\n[LOG] Habilidade com ID %d nao encontrada.\n", id_habilidade);
        return;
    }

    Habilidade hab = skill_node->habilidade;
    printf("\n[LOG] Tentando desbloquear '%s'...\n", hab.nome);

    if (pontos_jogador >= hab.custo_pontos && nivel_jogador >= hab.nivel_minimo) {
        printf("[SUCESSO] Habilidade '%s' desbloqueada! (Custo: %d)\n", hab.nome, hab.custo_pontos);
        // Em um jogo real, aqui você decrementaria os pontos do jogador e marcaria a habilidade como 'aprendida'
    } else {
        printf("[FALHA] Nao e possivel desbloquear '%s'.\n", hab.nome);
        if (pontos_jogador < hab.custo_pontos) {
            printf("  - Pontos insuficientes (Necessario: %d, Possui: %d)\n", hab.custo_pontos, pontos_jogador);
        }
        if (nivel_jogador < hab.nivel_minimo) {
            printf("  - Nivel do personagem muito baixo (Necessario: %d, Possui: %d)\n", hab.nivel_minimo, nivel_jogador);
        }
    }
}


// Funcao principal para demonstrar a aplicacao
int main() {
    No *raiz = NULL;

    printf("--- Simulacao da Arvore de Habilidades (Skill Tree) ---\n");
    printf("--- Estrutura de Dados: Arvore AVL ---\n\n");

    // Definição de Habilidades (Inserção na AVL)
    Habilidade hab1 = {10, "Ataque Basico Reforcado", 5, 1};
    Habilidade hab2 = {5, "Defesa Aprimorada", 3, 1};
    Habilidade hab3 = {15, "Furia", 10, 5};
    Habilidade hab4 = {2, "Bloqueio Rapido", 2, 1};
    Habilidade hab5 = {7, "Curar Feridas", 8, 3};

    // Inserindo as habilidades. A AVL garante o balanceamento.
    raiz = inserir(raiz, hab1);
    raiz = inserir(raiz, hab2);
    raiz = inserir(raiz, hab3);
    raiz = inserir(raiz, hab4);
    raiz = inserir(raiz, hab5);

    printf("1. Arvore de Habilidades (Inorder):\n");
    inOrder(raiz);
    printf("\n-------------------------------------------------\n");


    // 2. Simulação de um jogador
    int pontos_disponiveis = 12;
    int nivel_atual = 4;
    printf("2. Status do Jogador: Pontos de Habilidade: %d, Nivel Atual: %d\n", pontos_disponiveis, nivel_atual);

    // 3. Testes de Busca e Desbloqueio (Aplicação)
    desbloquearHabilidade(raiz, 10, pontos_disponiveis, nivel_atual); // ID 10: Sucesso
    desbloquearHabilidade(raiz, 15, pontos_disponiveis, nivel_atual); // ID 15: Falha (Nível < 5)
    desbloquearHabilidade(raiz, 20, pontos_disponiveis, nivel_atual); // ID 20: Não encontrada

    // Demonstração de busca eficiente
    No *busca_result = buscar(raiz, 7);
    if (busca_result != NULL) {
        printf("\n[BUSCA] Habilidade ID 7 encontrada: %s (Custo: %d)\n",
               busca_result->habilidade.nome, busca_result->habilidade.custo_pontos);
    }
    printf("\n-------------------------------------------------\n");

    // Limpeza de memória
    // (Em um projeto completo, a função de remoção e liberação de memória seria implementada)

    return 0;
}
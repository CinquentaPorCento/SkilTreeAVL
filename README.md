Aluno: Gabriel Pereira Cardoso Soares
Estrutura de dados II

Este repositório contém uma implementação em C de uma Árvore de Habilidades (Skill Tree) utilizando a estrutura de dados Árvore AVL. A AVL garante que as operações de busca e inserção sejam eficientes (O(logn)) através do auto-balanceamento automático dos nós.
📝 Ordem de Inserção e Balanceamento

Para demonstrar a capacidade de auto-balanceamento da AVL, as habilidades são inseridas em uma ordem que força a árvore a se reestruturar.
1. Ordem de Inserção

As seguintes seis habilidades são inseridas sequencialmente no main.c.

A ordem de inserção é: 10, 5, 15, 2, 7, 1.
2. Efeito do Balanceamento

A inserção da última habilidade, ID 1, causou um desbalanceamento do tipo Esquerda-Esquerda (LL) no nó com ID 5, que é o ancestral do nó 1.

O algoritmo AVL detectou esse desequilíbrio e automaticamente executou uma Rotação Simples à Direita. Essa rotação reorganiza os nós para que a diferença de altura em qualquer ponto da árvore seja no máximo 1, garantindo a eficiência da Skill Tree.

A função inOrder (listagem em ordem crescente de ID) é usada para confirmar o estado final e a altura de cada nó após o balanceamento.
🧠 Como o Código Funciona

O código é dividido em estruturas de dados (cabeçalho da árvore) e funções lógicas (operações da AVL e simulação de jogo).
🏗️ Estruturas de Dados

    Habilidade: Define os dados da skill (ID, nome, custo e nível).

    No: Define a estrutura do nó da AVL, contendo uma Habilidade, ponteiros para os filhos (esquerda, direita) e o campo altura, usado para o balanceamento.

    Variáveis Globais (pontos_disponiveis, nivel_atual): Simulam o status mutável do jogador para que os pontos sejam debitados corretamente após um desbloqueio.

🎯 Funções Principais

    inserir(No *no, Habilidade hab):

        Executa a inserção normal de uma BST.

        Após a inserção, calcula o Fator de Balanceamento (obterFatorBalanceamento).

        Se o fator for maior que ∣1∣, aciona as funções de rotação (rotacaoDireita ou rotacaoEsquerda) para reequilibrar a árvore, conforme demonstrado pela inserção do ID 1.

    buscar(No *raiz, int id):

        Permite a busca rápida de uma Habilidade pelo seu id (chave).

    desbloquearHabilidade(No *raiz, int id_habilidade):

        Simula a lógica do jogo.

        Usa buscar para localizar a skill.

        Verifica se o jogador atende aos requisitos de custo e nível.

        Se for bem-sucedido, decrementa a variável global pontos_disponiveis.

    main():

        Cria e insere as seis habilidades.

        Imprime o resultado da árvore final (inOrder).

        Inicia um loop interativo que permite ao usuário digitar o ID da habilidade que deseja desbloquear e acompanha o gasto dos pontos do jogador;
        

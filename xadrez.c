#include <stdio.h>

int main() {
    // Posição inicial do Bispo no tabuleiro (linha e coluna)
    int linha = 0;
    int coluna = 0;

    // Contador para controlar o número de movimentos
    int movimentos = 0;

    // O Bispo deve se mover 5 casas na diagonal superior direita
    while (movimentos < 5) {
        // Atualiza a posição do Bispo
        linha++;
        coluna++;

        // Exibe a direção do movimento
        printf("Movendo para a diagonal superior direita: linha %d, coluna %d\n", linha, coluna);

        // Incrementa o contador de movimentos
        movimentos++;
    }

    // Mensagem final
    printf("O Bispo completou 5 movimentos na diagonal superior direita.\n");

    return 0;
}



// Desafio de Xadrez - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de movimentação das peças de xadrez.
// O objetivo é utilizar estruturas de repetição e funções para determinar os limites de movimentação dentro do jogo.


    // Implementação de Movimentação da Torre
    // Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Torre para a direita.

    // Implementação de Movimentação da Rainha
    // Sugestão: Utilize uma estrutura de repetição para simular a movimentação da Rainha para a esquerda.

    // Nível Aventureiro - Movimentação do Cavalo
    // Sugestão: Utilize loops aninhados para simular a movimentação do Cavalo em L.
    // Um loop pode representar a movimentação horizontal e outro vertical.

    // Nível Mestre - Funções Recursivas e Loops Aninhados
    // Sugestão: Substitua as movimentações das peças por funções recursivas.
    // Exemplo: Crie uma função recursiva para o movimento do Bispo.

    // Sugestão: Implemente a movimentação do Cavalo utilizando loops com variáveis múltiplas e condições avançadas.
    // Inclua o uso de continue e break dentro dos loops.

   


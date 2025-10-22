#include <stdio.h>

// Constantes para quantidade de movimentos
#define BISPO_MOV 5
#define TORRE_MOV 5
#define RAINHA_MOV 8

int main() {
    int i;

    // Movimentação do Bispo (diagonal superior direita = Cima + Direita)
    printf("Movimentação do Bispo:\n");
    for (i = 0; i < BISPO_MOV; i++) {
        printf("Cima\n");
        printf("Direita\n");
    }

    // Movimentação da Torre (direita)
    printf("\nMovimentação da Torre:\n");
    while (i < BISPO_MOV + TORRE_MOV) {
        printf("Direita\n");
        i++;
    }

    // Movimentação da Rainha (esquerda)
    printf("\nMovimentação da Rainha:\n");
    do {
        printf("Esquerda\n");
        i++;
    } while (i < BISPO_MOV + TORRE_MOV + RAINHA_MOV);

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

   


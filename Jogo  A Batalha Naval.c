/*
    Batalha Naval - Estrutura em C

    Este programa cria um tabuleiro 10x10 para um jogo de batalha naval. Quatro navios de tamanho 3 são posicionados:
    - Dois navios em direção horizontal/vertical
    - Dois navios em direção diagonal (principal e secundária)

    Água = 0, parte do navio = 3

    O programa valida limites, sobreposição e exibe o tabuleiro ao final.

    Autor: HackerJeday7
*/

#include <stdio.h>
#include <stdbool.h>

// Tamanho do tabuleiro
#define TAMANHO 10
// Valor que representa água
#define AGUA 0
// Valor que representa navio
#define NAVIO 3
// Tamanho padrão dos navios
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se é possível posicionar navio sem sobrepor
bool podePosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, char direcao) {
    for (int k = 0; k < tamanho; k++) {
        int lin = linha;
        int col = coluna;
        switch (direcao) {
            case 'H': col += k; break;                   // Horizontal
            case 'V': lin += k; break;                   // Vertical
            case 'D': lin += k; col += k; break;         // Diagonal principal (linha=coluna)
            case 'S': lin += k; col -= k; break;         // Diagonal secundária (linha+coluna constante)
        }
        // Verifica limites e sobreposição
        if (lin < 0 || lin >= TAMANHO || col < 0 || col >= TAMANHO)
            return false;
        if (tabuleiro[lin][col] == NAVIO)
            return false;
    }
    return true;
}

// Função para posicionar navio (já validado)
void posicionaNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, char direcao) {
    for (int k = 0; k < tamanho; k++) {
        int lin = linha;
        int col = coluna;
        switch (direcao) {
            case 'H': col += k; break;
            case 'V': lin += k; break;
            case 'D': lin += k; col += k; break;
            case 'S': lin += k; col -= k; break;
        }
        tabuleiro[lin][col] = NAVIO;
    }
}

// Função para exibir tabuleiro no console
void exibeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro Batalha Naval (10x10):\n\n   ");
    // Números das colunas
    for (int col = 0; col < TAMANHO; col++)
        printf("%2d ", col);
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = água | 3 = navio\n");
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializaTabuleiro(tabuleiro);

    // Definição das coordenadas e direções dos navios
    // Navio 1: Horizontal, começa em (2, 4)
    int l1=2, c1=4;
    char d1='H';
    // Navio 2: Vertical, começa em (6, 1)
    int l2=6, c2=1;
    char d2='V';
    // Navio 3: Diagonal principal, começa em (0,0)
    int l3=0, c3=0;
    char d3='D';
    // Navio 4: Diagonal secundária, começa em (0,7)
    int l4=0, c4=7;
    char d4='S';

    // Posicionamento com validação
    if (podePosicionarNavio(tabuleiro, l1, c1, TAM_NAVIO, d1))
        posicionaNavio(tabuleiro, l1, c1, TAM_NAVIO, d1);
    else
        printf("Erro ao posicionar Navio 1!\n");

    if (podePosicionarNavio(tabuleiro, l2, c2, TAM_NAVIO, d2))
        posicionaNavio(tabuleiro, l2, c2, TAM_NAVIO, d2);
    else
        printf("Erro ao posicionar Navio 2!\n");

    if (podePosicionarNavio(tabuleiro, l3, c3, TAM_NAVIO, d3))
        posicionaNavio(tabuleiro, l3, c3, TAM_NAVIO, d3);
    else
        printf("Erro ao posicionar Navio 3!\n");

    if (podePosicionarNavio(tabuleiro, l4, c4, TAM_NAVIO, d4))
        posicionaNavio(tabuleiro, l4, c4, TAM_NAVIO, d4);
    else
        printf("Erro ao posicionar Navio 4!\n");

    // Exibe o tabuleiro final
    exibeTabuleiro(tabuleiro);

    return 0;
}

/*
    Explicação dos valores:
    - tabuleiro[i][j] == 0     → Água
    - tabuleiro[i][j] == 3     → Parte de navio

    Funções bem documentadas:
    - inicializaTabuleiro: prepara o tabuleiro.
    - podePosicionarNavio: verifica se há espaço para o navio e não há sobreposição.
    - posicionaNavio: coloca o navio nas coordenadas.
    - exibeTabuleiro: exibe a matriz alinhada na tela.
*/
#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Estrutura para representar um navio
typedef struct {
    int linha_inicial;
    int coluna_inicial;
    // Direção: 0=horizontal, 1=vertical, 2=diagonal principal, 3=diagonal secundária
    int direcao;
} Navio;

// Função para verificar se o navio cabe no tabuleiro e não sobrepõe outros navios
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = navio.linha_inicial, coluna = navio.coluna_inicial;
        switch (navio.direcao) {
            case 0: // Horizontal
                coluna += i;
                break;
            case 1: // Vertical
                linha += i;
                break;
            case 2: // Diagonal principal (linha++, coluna++)
                linha += i;
                coluna += i;
                break;
            case 3: // Diagonal secundária (linha++, coluna--)
                linha += i;
                coluna -= i;
                break;
        }
        // Verifica limites
        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO)
            return 0;
        // Verifica sobreposição
        if (tabuleiro[linha][coluna] == NAVIO)
            return 0;
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = navio.linha_inicial, coluna = navio.coluna_inicial;
        switch (navio.direcao) {
            case 0: coluna += i; break;
            case 1: linha += i; break;
            case 2: linha += i; coluna += i; break;
            case 3: linha += i; coluna -= i; break;
        }
        tabuleiro[linha][coluna] = NAVIO;
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro e inicialização com água
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Exemplo de navios posicionados diretamente no código
    Navio navios[4] = {
        {2, 1, 0}, // Horizontal iniciado em (2,1)
        {6, 4, 1}, // Vertical iniciado em (6,4)
        {0, 0, 2}, // Diagonal principal iniciado em (0,0)
        {0, 9, 3}  // Diagonal secundária (linha 0, coluna 9)
    };

    // Posiciona cada navio, validando sobreposição e limites
    for (int k = 0; k < 4; k++) {
        if (pode_posicionar(tabuleiro, navios[k])) {
            posicionar_navio(tabuleiro, navios[k]);
        } else {
            printf("Erro: Não foi possível posicionar o navio %d na posição especificada.\n", k+1);
        }
    }

    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);
    return 0;
}

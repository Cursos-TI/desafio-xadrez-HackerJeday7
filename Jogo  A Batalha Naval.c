#include <stdio.h>
#include <stdbool.h>

// =====================
// Configuração do jogo
// =====================
#define TAMANHO 10   // Tamanho do tabuleiro (10x10)
#define AGUA 0       // Valor que representa água
#define NAVIO 3      // Valor que representa navio
#define AOE 5        // Valor que representa área afetada por habilidade
#define TAM_NAVIO 3  // Tamanho padrão dos navios

// =====================
// Habilidades (matrizes 0/1)
// =====================
#define TAM_HAB 5    // Tamanho da matriz de habilidade (ímpar: 5, 7, ...)

// ---------------------
// Funções do tabuleiro
// ---------------------

// Inicializa o tabuleiro com água (0)
void inicializaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se é possível posicionar navio sem sair dos limites e sem sobrepor
bool podePosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, char direcao) {
    for (int k = 0; k < tamanho; k++) {
        int lin = linha;
        int col = coluna;
        switch (direcao) {
            case 'H': col += k; break;                   // Horizontal
            case 'V': lin += k; break;                   // Vertical
            case 'D': lin += k; col += k; break;         // Diagonal principal (linha=coluna)
            case 'S': lin += k; col -= k; break;         // Diagonal secundária (linha+coluna constante)
            default: return false;
        }
        // Verifica limites e sobreposição
        if (lin < 0 || lin >= TAMANHO || col < 0 || col >= TAMANHO) return false;
        if (tabuleiro[lin][col] == NAVIO) return false;
    }
    return true;
}

// Posiciona navio já validado
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

// Exibe o tabuleiro no console
void exibeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro Batalha Naval (10x10):\n\n   ");
    // Números das colunas
    for (int col = 0; col < TAMANHO; col++) printf("%2d ", col);
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = água | 3 = navio | 5 = área da habilidade\n");
}

// -------------------------------
// Construção das matrizes (0/1)
// -------------------------------

// CONE apontando para baixo, com a "ponta" no topo da matriz.
// A regra é: numa linha i, ativar colunas j tais que (mid - i) <= j <= (mid + i).
void construirCone(int m[TAM_HAB][TAM_HAB]) {
    int mid = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= mid - i && j <= mid + i) m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

// CRUZ com origem no centro: ativa a linha e a coluna centrais.
void construirCruz(int m[TAM_HAB][TAM_HAB]) {
    int mid = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == mid || j == mid) m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

// OCTAEDRO (losango) usando distância Manhattan ao centro:
// ativa se |i - mid| + |j - mid| <= mid.
void construirOctaedro(int m[TAM_HAB][TAM_HAB]) {
    int mid = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int di = (i > mid) ? (i - mid) : (mid - i);
            int dj = (j > mid) ? (j - mid) : (mid - j);
            if (di + dj <= mid) m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

// ---------------------------------------
// Sobreposição da habilidade no tabuleiro
// ---------------------------------------
// Alinha um "ponto de origem" da matriz de habilidade a uma posição alvo no tabuleiro.
// - skill_origem_lin/col: qual célula da matriz representa a origem (ex.: centro ou ponta do cone).
// - board_origem_lin/col: célula do tabuleiro onde a origem será posicionada.
// - Marca as células 1 da matriz como AOE (5), sem sobrescrever NAVIO (3).
void sobreporHabilidade(const int hab[TAM_HAB][TAM_HAB],
                        int tabuleiro[TAMANHO][TAMANHO],
                        int skill_origem_lin, int skill_origem_col,
                        int board_origem_lin, int board_origem_col,
                        int valor_marca)
{
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int alvo_lin = board_origem_lin + (i - skill_origem_lin);
                int alvo_col = board_origem_col + (j - skill_origem_col);

                // Mantém dentro dos limites do tabuleiro
                if (alvo_lin >= 0 && alvo_lin < TAMANHO &&
                    alvo_col >= 0 && alvo_col < TAMANHO)
                {
                    // Não sobrescreve navio
                    if (tabuleiro[alvo_lin][alvo_col] != NAVIO) {
                        tabuleiro[alvo_lin][alvo_col] = valor_marca;
                    }
                }
            }
        }
    }
}

// =====================
// Programa principal
// =====================
int main(void) {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializaTabuleiro(tabuleiro);

    // ---- Navios de demonstração (iguais ao seu código) ----
    int l1=2, c1=4; char d1='H'; // Horizontal, começa em (2,4)
    int l2=6, c2=1; char d2='V'; // Vertical,   começa em (6,1)
    int l3=0, c3=0; char d3='D'; // Diagonal principal, começa em (0,0)
    int l4=0, c4=7; char d4='S'; // Diagonal secundária, começa em (0,7)

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

    // ---- Habilidades: construir e sobrepor ----
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octa[TAM_HAB][TAM_HAB];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octa);

    int mid = TAM_HAB / 2;

    // 1) Cone apontando para baixo: origem = PONTA (topo da matriz) -> (0, mid)
    //    Vamos posicionar a ponta em (1, 2) do tabuleiro
    sobreporHabilidade(cone, tabuleiro,
                       /*skill origem*/ 0, mid,
                       /*board origem*/ 1, 2,
                       AOE);

    // 2) Cruz: origem = CENTRO (mid, mid)
    //    Posicionar o centro em (6, 6)
    sobreporHabilidade(cruz, tabuleiro,
                       /*skill origem*/ mid, mid,
                       /*board origem*/ 6, 6,
                       AOE);

    // 3) Octaedro (losango): origem = CENTRO (mid, mid)
    //    Posicionar o centro em (7, 3)
    sobreporHabilidade(octa, tabuleiro,
                       /*skill origem*/ mid, mid,
                       /*board origem*/ 7, 3,
                       AOE);

    // ---- Exibir resultado ----
    exibeTabuleiro(tabuleiro);

    return 0;
}

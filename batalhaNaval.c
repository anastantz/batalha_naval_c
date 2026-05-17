#include <stdio.h>

/*
 * Projeto: Batalha Naval - MateCheck
 * Nivel: Novato - Posicionamento de navios no tabuleiro
 *
 * Tabuleiro 10x10 inicializado com 0 (agua).
 * Dois navios de tamanho 3 sao posicionados:
 * - Navio horizontal: linha 2, coluna 4
 * - Navio vertical:   linha 5, coluna 7
 * Posicoes ocupadas por navios recebem valor 3.
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO     3
#define AGUA              0
#define NAVIO             3

int main() {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    int navioHorizontal[TAMANHO_NAVIO];
    int navioVertical[TAMANHO_NAVIO];

    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    int linhaVertical = 5;
    int colunaVertical = 7;

    int linha;
    int coluna;
    int i;

    int posicaoFinalHorizontal;
    int posicaoFinalVertical;

    int sobreposicao;

    /*
     * Inicializacao do tabuleiro com AGUA (0).
     * Loops aninhados percorrem todas as celulas da matriz.
     */
    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /*
     * Inicializacao dos vetores dos navios.
     * Cada posicao do vetor representa uma celula ocupada pelo navio.
     * O valor 3 sera copiado para o tabuleiro durante o posicionamento.
     */
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        navioHorizontal[i] = NAVIO;
        navioVertical[i]   = NAVIO;
    }

    /*
     * Validacao dos limites do tabuleiro.
     *
     * Navio horizontal ocupa colunas de colunaHorizontal ate
     * colunaHorizontal + TAMANHO_NAVIO - 1, na mesma linha.
     *
     * Navio vertical ocupa linhas de linhaVertical ate
     * linhaVertical + TAMANHO_NAVIO - 1, na mesma coluna.
     */
    posicaoFinalHorizontal = colunaHorizontal + TAMANHO_NAVIO - 1;
    posicaoFinalVertical   = linhaVertical    + TAMANHO_NAVIO - 1;

    if (linhaHorizontal < 0 || linhaHorizontal >= TAMANHO_TABULEIRO ||
        colunaHorizontal < 0 || posicaoFinalHorizontal >= TAMANHO_TABULEIRO) {
        printf("Erro: navio horizontal fora dos limites do tabuleiro.\n");
        return 1;
    }

    if (colunaVertical < 0 || colunaVertical >= TAMANHO_TABULEIRO ||
        linhaVertical < 0  || posicaoFinalVertical >= TAMANHO_TABULEIRO) {
        printf("Erro: navio vertical fora dos limites do tabuleiro.\n");
        return 1;
    }

    /*
     * Validacao de sobreposicao entre os dois navios.
     *
     * O navio horizontal ocupa: linha = linhaHorizontal,
     * colunas de colunaHorizontal ate colunaHorizontal + TAMANHO_NAVIO - 1.
     *
     * O navio vertical ocupa: coluna = colunaVertical,
     * linhas de linhaVertical ate linhaVertical + TAMANHO_NAVIO - 1.
     *
     * Ha sobreposicao se a linha do horizontal estiver dentro do
     * intervalo vertical E a coluna do vertical estiver dentro do
     * intervalo horizontal ao mesmo tempo.
     */
    sobreposicao = (linhaHorizontal >= linhaVertical &&
                    linhaHorizontal <= posicaoFinalVertical &&
                    colunaVertical  >= colunaHorizontal &&
                    colunaVertical  <= posicaoFinalHorizontal);

    if (sobreposicao) {
        printf("Erro: os navios se sobrepoem.\n");
        return 1;
    }

    /*
     * Posicionamento do navio horizontal no tabuleiro.
     * Copia o valor de cada posicao do vetor navioHorizontal
     * para a linha fixa, avancando coluna a coluna.
     */
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaHorizontal][colunaHorizontal + i] = navioHorizontal[i];
    }

    /*
     * Posicionamento do navio vertical no tabuleiro.
     * Copia o valor de cada posicao do vetor navioVertical
     * para a coluna fixa, avancando linha a linha.
     */
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaVertical + i][colunaVertical] = navioVertical[i];
    }

    /*
     * Exibicao do tabuleiro.
     * Loops aninhados percorrem a matriz linha por linha.
     * Cada celula e impressa separada por espaco.
     * Ao final de cada linha, uma quebra de linha organiza a saida.
     */
    printf("===== BATALHA NAVAL =====\n\n");

    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\n0 = Agua  |  3 = Navio\n");

    return 0;
}
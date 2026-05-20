#include <stdio.h>

/*
 * Projeto: Batalha Naval - MateCheck
 * Nivel: Aventureiro - Tabuleiro completo com navios diagonais
 *
 * Quatro navios de tamanho 3 posicionados:
 * - Navio 1: horizontal, linha 2, coluna 1
 * - Navio 2: vertical,   linha 6, coluna 0
 * - Navio 3: diagonal principal (linha e coluna crescem juntas), inicio linha 0, coluna 6
 * - Navio 4: diagonal secundaria (linha cresce, coluna decresce), inicio linha 7, coluna 9
 *
 * Agua = 0, Navio = 3.
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO     3
#define AGUA              0
#define NAVIO             3

/*
 * Funcao: posicaoValida
 *
 * Verifica se uma celula (lin, col) esta dentro dos limites do tabuleiro.
 * Retorna 1 se valida, 0 se invalida.
 * Usada antes de qualquer posicionamento para evitar acesso fora da matriz.
 */
int posicaoValida(int lin, int col) {
    return (lin >= 0 && lin < TAMANHO_TABULEIRO &&
            col >= 0 && col < TAMANHO_TABULEIRO);
}

/*
 * Funcao: celulaLivre
 *
 * Verifica se uma celula do tabuleiro ainda esta com AGUA (nao ocupada).
 * Retorna 1 se livre, 0 se ja ocupada por outro navio.
 * Usada para detectar sobreposicao antes de posicionar cada navio.
 */
int celulaLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col) {
    return tabuleiro[lin][col] == AGUA;
}

int main() {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    int linha;
    int coluna;
    int i;

    /* Coordenadas iniciais de cada navio */
    int linhaH  = 2, colunaH  = 1; /* Navio 1: horizontal        */
    int linhaV  = 6, colunaV  = 0; /* Navio 2: vertical          */
    int linhaD1 = 0, colunaD1 = 6; /* Navio 3: diagonal principal */
    int linhaD2 = 7, colunaD2 = 9; /* Navio 4: diagonal secundaria */

    int erro = 0; /* Flag de erro: 1 encerra o programa apos mensagem */

    /*
     * Inicializacao do tabuleiro com AGUA.
     * Todos os 100 elementos recebem 0 antes de qualquer posicionamento.
     */
    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /*
     * Posicionamento do Navio 1 - Horizontal.
     *
     * Ocupa TAMANHO_NAVIO colunas consecutivas na mesma linha.
     * Linha fixa: linhaH. Colunas: colunaH, colunaH+1, colunaH+2.
     *
     * Validacao: cada celula deve estar dentro do tabuleiro e livre.
     */
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (!posicaoValida(linhaH, colunaH + i)) {
            printf("Erro: navio horizontal fora dos limites.\n");
            erro = 1;
            break;
        }
        if (!celulaLivre(tabuleiro, linhaH, colunaH + i)) {
            printf("Erro: navio horizontal se sobrepoem com outro navio.\n");
            erro = 1;
            break;
        }
        tabuleiro[linhaH][colunaH + i] = NAVIO;
    }

    /*
     * Posicionamento do Navio 2 - Vertical.
     *
     * Ocupa TAMANHO_NAVIO linhas consecutivas na mesma coluna.
     * Coluna fixa: colunaV. Linhas: linhaV, linhaV+1, linhaV+2.
     */
    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaV + i, colunaV)) {
                printf("Erro: navio vertical fora dos limites.\n");
                erro = 1;
                break;
            }
            if (!celulaLivre(tabuleiro, linhaV + i, colunaV)) {
                printf("Erro: navio vertical se sobrepoem com outro navio.\n");
                erro = 1;
                break;
            }
            tabuleiro[linhaV + i][colunaV] = NAVIO;
        }
    }

    /*
     * Posicionamento do Navio 3 - Diagonal principal.
     *
     * Linha e coluna crescem juntas a cada passo.
     * Celulas: (linhaD1, colunaD1), (linhaD1+1, colunaD1+1), (linhaD1+2, colunaD1+2).
     *
     * Esse padrao imita a diagonal onde linha == coluna (com deslocamento).
     */
    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaD1 + i, colunaD1 + i)) {
                printf("Erro: navio diagonal principal fora dos limites.\n");
                erro = 1;
                break;
            }
            if (!celulaLivre(tabuleiro, linhaD1 + i, colunaD1 + i)) {
                printf("Erro: navio diagonal principal se sobrepoem com outro navio.\n");
                erro = 1;
                break;
            }
            tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
        }
    }

    /*
     * Posicionamento do Navio 4 - Diagonal secundaria.
     *
     * Linha cresce e coluna decresce a cada passo.
     * Celulas: (linhaD2, colunaD2), (linhaD2+1, colunaD2-1), (linhaD2+2, colunaD2-2).
     *
     * Esse padrao imita a diagonal onde linha + coluna == constante.
     */
    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaD2 + i, colunaD2 - i)) {
                printf("Erro: navio diagonal secundaria fora dos limites.\n");
                erro = 1;
                break;
            }
            if (!celulaLivre(tabuleiro, linhaD2 + i, colunaD2 - i)) {
                printf("Erro: navio diagonal secundaria se sobrepoem com outro navio.\n");
                erro = 1;
                break;
            }
            tabuleiro[linhaD2 + i][colunaD2 - i] = NAVIO;
        }
    }

    if (erro) {
        return 1;
    }

    /*
     * Exibicao do tabuleiro.
     *
     * Loops aninhados percorrem a matriz linha por linha.
     * Cada valor e impresso com espaco a direita para alinhar as colunas.
     * Uma quebra de linha ao final de cada linha organiza a grade.
     */
    printf("===== BATALHA NAVAL =====\n\n");

    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\n0 = Agua  |  3 = Navio\n");
    printf("\nNavios posicionados:\n");
    printf("  Navio 1 (horizontal):         linha %d, colunas %d a %d\n",
           linhaH, colunaH, colunaH + TAMANHO_NAVIO - 1);
    printf("  Navio 2 (vertical):           linhas %d a %d, coluna %d\n",
           linhaV, linhaV + TAMANHO_NAVIO - 1, colunaV);
    printf("  Navio 3 (diagonal principal): inicio (%d,%d), fim (%d,%d)\n",
           linhaD1, colunaD1, linhaD1 + TAMANHO_NAVIO - 1, colunaD1 + TAMANHO_NAVIO - 1);
    printf("  Navio 4 (diagonal secundaria): inicio (%d,%d), fim (%d,%d)\n",
           linhaD2, colunaD2, linhaD2 + TAMANHO_NAVIO - 1, colunaD2 - TAMANHO_NAVIO + 1);

    return 0;
}
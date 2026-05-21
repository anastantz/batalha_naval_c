#include <stdio.h>

/*
 * Projeto: Batalha Naval - MateCheck
 * Nivel: Mestre - Habilidades especiais com areas de efeito
 *
 * Construido sobre o nivel aventureiro. Mantem os quatro navios
 * e adiciona tres habilidades especiais sobrepostas ao tabuleiro:
 *
 * - Cone:     expande de um ponto para baixo, alargando a cada linha
 * - Cruz:     linha horizontal e coluna vertical a partir do centro
 * - Octaedro: formato de losango (distancia <= raio)
 *
 * Valores no tabuleiro:
 *   0 = Agua
 *   3 = Navio
 *   5 = Area afetada por habilidade
 *
 * As matrizes de habilidade usam 0 e 1 internamente.
 * O valor 1 indica celula afetada, que vira 5 no tabuleiro
 * caso a posicao esteja dentro dos limites e nao seja um navio.
 */

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO     3
#define TAMANHO_HAB       5

#define AGUA              0
#define NAVIO             3
#define HABILIDADE        5

int posicaoValida(int lin, int col) {
    return (lin >= 0 && lin < TAMANHO_TABULEIRO &&
            col >= 0 && col < TAMANHO_TABULEIRO);
}

int celulaLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col) {
    return tabuleiro[lin][col] == AGUA;
}

/*
 * Funcao: aplicarHabilidade
 *
 * Sobrepora uma matriz de habilidade 5x5 ao tabuleiro principal,
 * centralizando-a no ponto de origem (origemLinha, origemColuna).
 *
 * O centro da matriz de habilidade e a posicao [raio][raio],
 * onde raio = TAMANHO_HAB / 2 = 2 para uma matriz 5x5.
 *
 * Para cada celula da matriz de habilidade com valor 1:
 *   - Calcula a posicao correspondente no tabuleiro somando o
 *     deslocamento (i - raio, j - raio) ao ponto de origem.
 *   - Se a posicao estiver dentro do tabuleiro e nao for um navio,
 *     marca com o valor HABILIDADE (5).
 *   - Navios (valor 3) nao sao sobrescritos: a habilidade os afeta
 *     em termos de jogo, mas a visualizacao prioriza o navio.
 */
void aplicarHabilidade(
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int habilidade[TAMANHO_HAB][TAMANHO_HAB],
    int origemLinha,
    int origemColuna
) {
    int raio = TAMANHO_HAB / 2;
    int i, j;
    int linTab, colTab;

    for (i = 0; i < TAMANHO_HAB; i++) {
        for (j = 0; j < TAMANHO_HAB; j++) {

            if (habilidade[i][j] == 1) {

                /*
                 * Converte coordenada da matriz de habilidade para
                 * coordenada do tabuleiro usando o deslocamento
                 * em relacao ao centro (raio, raio) da habilidade.
                 */
                linTab = origemLinha + (i - raio);
                colTab = origemColuna + (j - raio);

                if (posicaoValida(linTab, colTab)) {
                    if (tabuleiro[linTab][colTab] != NAVIO) {
                        tabuleiro[linTab][colTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    /*
     * Tres matrizes de habilidade 5x5.
     * Cada posicao vale 0 (nao afetada) ou 1 (afetada).
     * Sao construidas dinamicamente via loops e condicionais,
     * conforme exigido pelo enunciado.
     */
    int cone[TAMANHO_HAB][TAMANHO_HAB];
    int cruz[TAMANHO_HAB][TAMANHO_HAB];
    int octaedro[TAMANHO_HAB][TAMANHO_HAB];

    int linha, coluna, i;
    int raio = TAMANHO_HAB / 2;
    int distancia;
    int erro = 0;

    /* Coordenadas dos navios (mantidas do nivel aventureiro) */
    int linhaH  = 2, colunaH  = 1;
    int linhaV  = 6, colunaV  = 0;
    int linhaD1 = 0, colunaD1 = 6;
    int linhaD2 = 7, colunaD2 = 9;

    /*
     * Pontos de origem de cada habilidade no tabuleiro.
     * O ponto e o centro a partir do qual a area de efeito se expande.
     * Escolhidos para nao coincidir entre si e ficarem visiveis.
     */
    int origemConeLinha    = 2, origemConeColuna    = 7;
    int origemCruzLinha    = 5, origemCruzColuna    = 5;
    int origemOctaedroLinha= 8, origemOctaedroColuna= 5;

    /* Inicializacao do tabuleiro com agua */
    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /* Posicionamento dos navios (identico ao nivel aventureiro) */

    for (i = 0; i < TAMANHO_NAVIO; i++) {
        if (!posicaoValida(linhaH, colunaH + i)) {
            printf("Erro: navio horizontal fora dos limites.\n");
            erro = 1; break;
        }
        if (!celulaLivre(tabuleiro, linhaH, colunaH + i)) {
            printf("Erro: navio horizontal se sobrepoem.\n");
            erro = 1; break;
        }
        tabuleiro[linhaH][colunaH + i] = NAVIO;
    }

    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaV + i, colunaV)) {
                printf("Erro: navio vertical fora dos limites.\n");
                erro = 1; break;
            }
            if (!celulaLivre(tabuleiro, linhaV + i, colunaV)) {
                printf("Erro: navio vertical se sobrepoem.\n");
                erro = 1; break;
            }
            tabuleiro[linhaV + i][colunaV] = NAVIO;
        }
    }

    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaD1 + i, colunaD1 + i)) {
                printf("Erro: navio diagonal principal fora dos limites.\n");
                erro = 1; break;
            }
            if (!celulaLivre(tabuleiro, linhaD1 + i, colunaD1 + i)) {
                printf("Erro: navio diagonal principal se sobrepoem.\n");
                erro = 1; break;
            }
            tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
        }
    }

    if (!erro) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!posicaoValida(linhaD2 + i, colunaD2 - i)) {
                printf("Erro: navio diagonal secundaria fora dos limites.\n");
                erro = 1; break;
            }
            if (!celulaLivre(tabuleiro, linhaD2 + i, colunaD2 - i)) {
                printf("Erro: navio diagonal secundaria se sobrepoem.\n");
                erro = 1; break;
            }
            tabuleiro[linhaD2 + i][colunaD2 - i] = NAVIO;
        }
    }

    if (erro) return 1;

    /*
     * Construcao da habilidade CONE (5x5).
     *
     * O cone aponta para baixo: o topo e um unico ponto central,
     * e cada linha seguinte expande a largura afetada em 1 para
     * cada lado, ate cobrir a linha inteira na base.
     *
     * Regra: na linha i da matriz, as colunas afetadas sao aquelas
     * cuja distancia horizontal ao centro (raio) e <= i.
     * Ou seja: |j - raio| <= i
     *
     * Linha 0 (topo): so a coluna central (|j-2| <= 0 -> j=2)
     * Linha 1:        colunas 1,2,3        (|j-2| <= 1)
     * Linha 2:        colunas 0,1,2,3,4    (|j-2| <= 2, linha inteira)
     * Linhas 3 e 4:   linha inteira tambem
     *
     * Isso gera o formato triangular apontado para baixo.
     */
    for (linha = 0; linha < TAMANHO_HAB; linha++) {
        for (coluna = 0; coluna < TAMANHO_HAB; coluna++) {

            int distHorizontal = coluna - raio;
            if (distHorizontal < 0) distHorizontal = -distHorizontal;

            if (distHorizontal <= linha) {
                cone[linha][coluna] = 1;
            } else {
                cone[linha][coluna] = 0;
            }
        }
    }

    /*
     * Construcao da habilidade CRUZ (5x5).
     *
     * A cruz afeta toda a linha central (linha == raio) e
     * toda a coluna central (coluna == raio).
     *
     * Regra: uma celula e afetada se linha == raio OU coluna == raio.
     *
     * Resultado visual numa matriz 5x5:
     *   0 0 1 0 0
     *   0 0 1 0 0
     *   1 1 1 1 1
     *   0 0 1 0 0
     *   0 0 1 0 0
     */
    for (linha = 0; linha < TAMANHO_HAB; linha++) {
        for (coluna = 0; coluna < TAMANHO_HAB; coluna++) {

            if (linha == raio || coluna == raio) {
                cruz[linha][coluna] = 1;
            } else {
                cruz[linha][coluna] = 0;
            }
        }
    }

    /*
     * Construcao da habilidade OCTAEDRO / LOSANGO (5x5).
     *
     * O losango e definido pela distancia   ao centro:
     * a soma dos valores absolutos dos deslocamentos vertical e
     * horizontal deve ser menor ou igual ao raio.
     *
     * Regra: |linha - raio| + |coluna - raio| <= raio
     *
     * Resultado visual numa matriz 5x5 (raio = 2):
     *   0 0 1 0 0
     *   0 1 1 1 0
     *   1 1 1 1 1
     *   0 1 1 1 0
     *   0 0 1 0 0
     */
    for (linha = 0; linha < TAMANHO_HAB; linha++) {
        for (coluna = 0; coluna < TAMANHO_HAB; coluna++) {

            int distV = linha - raio;
            int distH = coluna - raio;
            if (distV < 0) distV = -distV;
            if (distH < 0) distH = -distH;

            distancia = distV + distH;

            if (distancia <= raio) {
                octaedro[linha][coluna] = 1;
            } else {
                octaedro[linha][coluna] = 0;
            }
        }
    }

    /*
     * Aplicacao das habilidades ao tabuleiro.
     *
     * Cada habilidade e sobreposta ao tabuleiro a partir do seu
     * ponto de origem. Celulas com NAVIO nao sao sobrescritas.
     */
    aplicarHabilidade(tabuleiro, cone,     origemConeLinha,     origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz,     origemCruzLinha,     origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    /*
     * Exibicao do tabuleiro final.
     *
     * Cada valor e convertido para um caractere descritivo:
     *   0 -> '~' (agua)
     *   3 -> 'N' (navio)
     *   5 -> '*' (area de habilidade)
     *
     * O uso de caracteres em vez de numeros torna a leitura
     * do tabuleiro muito mais clara no terminal.
     */
    printf("===== BATALHA NAVAL - NIVEL MESTRE =====\n\n");

    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {

            if (tabuleiro[linha][coluna] == AGUA) {
                printf("~ ");
            } else if (tabuleiro[linha][coluna] == NAVIO) {
                printf("N ");
            } else if (tabuleiro[linha][coluna] == HABILIDADE) {
                printf("* ");
            }
        }
        printf("\n");
    }

    printf("\n~ = Agua  |  N = Navio  |  * = Area de habilidade\n");

    printf("\nHabilidades aplicadas:\n");
    printf("  Cone     centrado em (%d,%d)\n", origemConeLinha,     origemConeColuna);
    printf("  Cruz     centrada em (%d,%d)\n", origemCruzLinha,     origemCruzColuna);
    printf("  Octaedro centrado em (%d,%d)\n", origemOctaedroLinha, origemOctaedroColuna);

    return 0;
}
/********************************************************
 *  Universidade Federal de Viçosa - Campus Florestal   *
 *  CCF330: Projeto e Análise de Algoritmos             *
 *  Prof: Daniel Mendes Barbosa                         *
 *  Aluno: Marcos V Assis (1804) e Luan H Alves (2278)  *
 *  Tarefa B: Sudoku                                    *
 ********************************************************/

#include "sudoku.h"

/**
 * Variaveis globais para 
 * contabilizar as analizes
 */
int conta_tentativa = 0;
int conta_recursao = 0;


/**
 * Imprime menu de opcoes para o usuario.
 */
int menu_opcoes(void) {

    int opcao;

    printf("\n _________________________________\n");
    printf("\n       SUDOKU BACKTRACKING        \n");
    printf(" _________________________________  \n");
    printf("  Escolha uma das opcoes abaixo:  \n\n");
    printf("    (1) Sudoku sem analise          \n");
    printf("    (2) Sudoku com analise          \n");
    printf("    (3) sair                        \n");
    printf(" _________________________________  \n");
    printf("\n Digite a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}


/**
 * Le o arquivo onde estao os numeros
 * do puzzle sudoku e os insere numa 
 * matriz.
 */
void le_arquivo(int quadro[TAM][TAM]) {
    
    FILE *arquivo;
    int i, j;
    int num;
    
    if ((arquivo = fopen("teste/quadro_sudoku.txt", "r")) == NULL) {
        perror(" Nao foi possivel abrir o arquivo desejado!\n");
        exit(EXIT_FAILURE);
    } else {
        
        while (!feof(arquivo)) {
            for (i = 0; i < TAM; i++) {
                for (j = 0; j < TAM; j++) {
                    fscanf(arquivo, "%d ", &num);
                    quadro[i][j] = num;
                }
            }
        }
    }
    fclose(arquivo);
}


/**
 * Inicializa o contador da analise 
 * e o quadro do sudoku.
 */
void inicializa(int quadro[TAM][TAM]) {

    conta_tentativa = 0;
    conta_recursao = 0;
    le_arquivo(quadro);
}

/**
 * Verifica se existe o numero num na coluna e retorna 1
 * se esta ja possui o numero a ser inserido e 0 caso 
 * contrario.
 */
int existe_na_coluna(int quadro[TAM][TAM], int coluna, int num) {

    int linha;
    
    for (linha = 0; linha < 9; linha++) {
        if (quadro[linha][coluna] == num) {
            return 1;
        }
    }
    return 0;
}


/**
 * Verifica se existe o numero num na linha e retorna 1
 * se esta ja possui o numero a ser inserido e 0 caso 
 * contrario.
 */
int existe_na_linha(int quadro[TAM][TAM], int linha, int num) {

    int coluna;

    for (coluna = 0; coluna < 9; coluna++) {
        if (quadro[linha][coluna] == num) {
            return 1;
        }
    }
    return 0;
}


/**
 * Verifica se existe o numero num na matriz 3 por 3 e
 * retorna 1 se ja existe, caso contrario retorna 0.
 */
int existe_no_subquadro(int quadro[TAM][TAM], int inicio_linha, int inicio_coluna, int num) {

    int linha;
    int coluna;
    int tam = TAM/MULTIPLO;

    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++) {
            if (quadro[linha + inicio_linha][coluna + inicio_coluna] == num) {
                return 1;
            }
        }
    }
    return 0;
}


/**
 * Utiliza as funcoes existe_na_linha, existe_na coluna e
 * existe_no_subquadro para verificar se o numero num pode
 * ser inserido na determinada posicao da matriz.
 */
int posicao_valida(int quadro[TAM][TAM], int linha, int coluna, int num) {
    if(!existe_na_coluna(quadro, coluna, num) && !existe_na_linha(quadro, linha, num) && 
       !existe_no_subquadro(quadro, linha - (linha %3), coluna - (coluna %3), num)){
        return 1;
    }
    return 0;
}


/**
 * Faz a busca por uma posicao vazia para inserir o numero num 
 * caso encontre uma posicao vazia retorna 1 e a referencia das
 * linhas e coluna tbm sao "retornadas".
 */
int busca_posicao(int quadro[TAM][TAM], int *linha, int *coluna) {
    for (*linha = 0; *linha < TAM; (*linha)++) {
        for (*coluna = 0; *coluna < TAM; (*coluna)++) {
            if (quadro[*linha][*coluna] == 0) {
                return 1;
            }
        }
    }
    return 0;
}


/**
 * Esta e a funcao que resolve o puzzle utilizando
 * as outras funcoes. Primeiro faz a busca por uma
 * posicao vazia, em seguida verifica se a posicao
 * encontrada e segura, e por fim, insere o numero
 * no quadro do sudoku.
 */
int solucao_sudoku(int quadro[TAM][TAM], int modo_analise) {
    
    int linha = 0;
    int coluna = 0;
    int num;
    
    
    if (!busca_posicao(quadro, &linha, &coluna)){
        // Se nao houver mais linhas vazias, retorna 1
        return 1;
    }
    
    // tenta inserir numeros de 1 a 9 no quadro.
    for (num = 1; num <= TAM; num++ ) {
        
        if (posicao_valida(quadro, linha, coluna, num)) {
            quadro[linha][coluna] = num;
            // Contabiliza do numero de tentativas de inserir
            // feita para inserir um numero do quadro.
            if(modo_analise) 
                conta_tentativa++;
            
            if (solucao_sudoku(quadro, modo_analise)) {
                // Contabiliza do numero de recursoe.    
                if(modo_analise) 
                    conta_recursao++;
                
                return 1;
            }
            quadro[linha][coluna] = 0;
        }
    }
    return 0;
}


/**
 * Imprime o quadro completo do sudoku e a
 * analise caso esta opcao esteja ativada.
 */
void imprime_quadro(int quadro[TAM][TAM], int modo_analise) {

    int linha;
    int coluna;
    
    for (linha = 0; linha < TAM; linha++) {
        for (coluna = 0; coluna < TAM; coluna++) {
            if(quadro[linha][coluna]!=0)
                printf("  %d", quadro[linha][coluna]);
            else
                printf("  _");
        }
        printf("\n");
    }
    if(modo_analise) 
        imprime_analise();
    
}


/**
 * Imprime as analise feitas da execucao do programa.
 */
void imprime_analise(){
    printf("\n ------ Analise ------");
    printf("\n  No. tentavivas: %d", conta_tentativa);
    printf("\n  No. recursao: %d", conta_recursao);
    printf("\n ---------------------");
}

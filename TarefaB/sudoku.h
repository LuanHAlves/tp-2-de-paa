#ifndef sudoku_h
#define sudoku_h

#include <stdio.h>
#include <stdlib.h>
/**
 * TAM pode ser de qualquer tamanho
 * desde que seja MULTIPLO de 3
 */
#define TAM 9 
#define MULTIPLO 3

int menu_opcoes(void);
void le_arquivo(int matriz[TAM][TAM]);
void inicializa(int matriz[TAM][TAM]);
int existe_na_coluna(int quadro[TAM][TAM], int coluna, int num) ;
int existe_na_linha(int quadro[TAM][TAM], int linha, int num);
int existe_no_subquadro(int quadro[TAM][TAM], int inicio_linha, int inicio_coluna, int num);
int verifica_posicao(int quadro[TAM][TAM], int linha, int coluna, int num);
int busca_posicao(int quadro[TAM][TAM], int *linha, int *coluna);
int solucao_sudoku(int quadro[TAM][TAM], int modo_analise);
void imprime_quadro(int quadro[TAM][TAM], int modo_analise);
void imprime_analise(void);

#endif /* sudoku_h */

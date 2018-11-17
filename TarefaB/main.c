/********************************************************
 *  Universidade Federal de Viçosa - Campus Florestal   *
 *  CCF330: Projeto e Análise de Algoritmos             *
 *  Prof: Daniel Mendes Barbosa                         *
 *  Aluno: Marcos V Assis (1804) e Luan H Alves (2278)  *
 *  Tarefa B: Sudoku 							  	    *
 ********************************************************/

#include <stdio.h>
#include "sudoku.h"

#define ANALISE_DESATIVADO 0
#define ANALISE_ATIVADO 1

int main(int argc, char const *argv[]) {
    
    int quadro[TAM][TAM];
    int opcao;

    do {
    	
    	inicializa(quadro);
    	printf("\n   Quadro inicial do Sudoku\n\n");
    	imprime_quadro(quadro, ANALISE_DESATIVADO);
        opcao = menu_opcoes();

        switch(opcao){
        	case 1:
	        	if (solucao_sudoku(quadro, ANALISE_DESATIVADO)) {
	        		printf("\n\n  Solucao do Sudoku:\n\n");
			        imprime_quadro(quadro, ANALISE_DESATIVADO);
			    } else {
			        printf(" Nao ha solucao possive :( ");
			    }
        	break;

        	case 2:
	        	if (solucao_sudoku(quadro, ANALISE_ATIVADO)) {
	        		printf("\n\n Solucao do Sudoku (Modo Analise):\n\n");
			        imprime_quadro(quadro, ANALISE_ATIVADO);
			    } else {
			        printf(" Nao ha solucao possive :( ");
			    }
		    break;
		    case 3:
		    	printf("\n\t--- Fim da execucao! --- \n\n"); 
		    	exit(1);
		    break;
		    default:
		    	printf(" Opcao invalida, tente novamente!\n");
		    break;
        }

    } while (1);

    return 0;
}

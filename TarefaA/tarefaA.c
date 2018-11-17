/********************************************************
 *  Universidade Federal de Viçosa - Campus Florestal   *
 *  CCF330: Projeto e Análise de Algoritmos             *
 *  Prof: Daniel Mendes Barbosa                         *
 *  Aluno: Marcos V Assis (1804) e Luan H Alves (2278)  *
 *  Tarefa A: Caça Palavras                             *
 ********************************************************/

#include "tarefaA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
void initStats(tipoCruzada *c)
{
    c->numOcorrencias = 0;
    c->numRec = 0;
}
int **alocarMatriz(int Linhas, int Colunas)
{
    int i, j;

    char **m = (char **)malloc(Linhas * sizeof(char *));

    for (i = 0; i < Linhas; i++) //Percorre as linhas do Vetor de Ponteiros
    {
        m[i] = (char *)malloc(Colunas * sizeof(char)); //Aloca um Vetor de Inteiros para cada posi��o do Vetor de Ponteiros.
        for (j = 0; j < Colunas; j++)
        {
            m[i][j] = '*';
        }
    }
    return m;
}
void inicializarCruzada(tipoCruzada *c)
{
    int i;
    c->matriz = (char **)malloc(c->linha * sizeof(char *));

    for (i = 0; i < c->linha; i++)
    {
        c->matriz[i] = (char *)malloc(c->coluna * sizeof(char));
    }
}
void imprime(char **m, int c, int l)
{
    int i, j;
    for (i = 0; i < l; i++)
    {

        for (j = 0; j < c; j++)
        {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}
void leArquivo(tipoCruzada *c, char **m, char *nomeArq)
{
    FILE *arq;
    int i, j;
    int linha, coluna;
    char car;
    arq = fopen(nomeArq, "r");

    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo desejado!\n");
        return;
    }
    else
    {
        fscanf(arq, "%d %d\n", &linha, &coluna);
        c->linha = linha;
        c->coluna = coluna;
        inicializarCruzada(c);
        while (!feof(arq))
        {
            for (i = 0; i < c->linha; i++)
            {
                for (j = 0; j < c->coluna; j++)
                {
                    fscanf(arq, "%c ", &car);
                    c->matriz[i][j] = car;
                }
            }
        }
    }

    
}
int valida(int linha, int coluna, int x, int y)
{
    if (x < linha && y < coluna && x >= 0 && y >= 0)
        return 1;
    return 0;
}

int procura(tipoCruzada *c, char **m, char *nome, int x, int y, int posPalavra, int direcao)
{
    c->numRec++;

    if (posPalavra == strlen(nome) - 1)
    {
        m[x][y] = nome[posPalavra];
        if (c->matriz[x][y] == nome[posPalavra])//encontrou a ultima posicao da palavra, verifica se e valido e encerra o backtracking para aquela palavra 
        {
            //printf("%d - %d\n", x+2, y+1);
            c->numOcorrencias++;
            return 1;
        }

        m[x][y] = '*';
        return 0;
    }

    if (valida(c->linha, c->coluna, x, y))
    {

        if (c->matriz[x][y] == nome[posPalavra])
        {
            m[x][y] = nome[posPalavra];
            if (direcao == 0)//movimento inicial para a posicao x, y 
            {
                if (procura(c, m, nome, x, y + 1, posPalavra + 1, 1))//Movimenta para o lado direito
                    return 1;
                if (procura(c, m, nome, x + 1, y, posPalavra + 1, 3))//Movimenta para baixo
                    return 1;
                if (procura(c, m, nome, x, y - 1, posPalavra + 1, 1))//Movimenta para o lado esquerdo
                    return 1;
            }
            if (direcao == 1)//movimento para um dos lados
            {
                if (procura(c, m, nome, x + 1, y, posPalavra + 1, 3))//Movimenta para baixo
                    return 1;
            }

            if (direcao == 3)//movimento para baixo
            {
                if (procura(c, m, nome, x, y - 1, posPalavra + 1, 1))//Movimenta para o lado esquerdo
                    return 1;
                if (procura(c, m, nome, x, y + 1, posPalavra + 1, 1))//Movimenta para o lado direito
                    return 1;
   
            }
            
            m[x][y] = '*';
            return 0;
        }

    }
    return 0;
}

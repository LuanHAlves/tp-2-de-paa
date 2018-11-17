/********************************************************
 *  Universidade Federal de Viçosa - Campus Florestal   *
 *  CCF330: Projeto e Análise de Algoritmos             *
 *  Prof: Daniel Mendes Barbosa                         *
 *  Aluno: Marcos V Assis (1804) e Luan H Alves (2278)  *
 *  Tarefa A: Caça Palavras                             *
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tarefaA.c"
#define statsOn 1
#define statsOff 0
int main()
{

    char **m, **matriz, palavra[40], nomeArq[20];
    int exibeStats = statsOff;
    FILE *arq;
    system("clear");

    printf("========================== Caça-Palavras Backtracking ==========================\n");
    printf("     Digite a palavra a ser procurada: ");
    scanf("%s", palavra);
    printf("     Digite o nome do arquivo que vc deseja carregar: ");
    scanf("%s", nomeArq);
    strcat(nomeArq, ".txt");

    int i, j, linha, coluna;
    tipoCruzada cruzada;
    leArquivo(&cruzada, m, nomeArq);

    m = alocarMatriz(cruzada.linha, cruzada.coluna);
    initStats(&cruzada);

    for (i = 0; i < cruzada.linha; i++)
    {
        for (j = 0; j < cruzada.coluna; j++)
        {
            procura(&cruzada, m, palavra, i, j, 0, 0);
        }
    }
    // procura(&cruzada, m, "casa", 0, 0, 0, 0);
    //printf("oi:%c",m[0][1]);
    system("clear");
    printf("========================== Caça-Palavras Backtracking ==========================\n");
    printf("Numero de ocorrencias da palavra procurada: %d\n", cruzada.numOcorrencias);
    imprime(m, cruzada.linha, cruzada.coluna);

    if (exibeStats)
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf("================== Modo Análise ==================\n");
        printf("Numero de chamadas recursivas: %d\n", cruzada.numRec);
    }
}

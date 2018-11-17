typedef struct cruzada{
    char** matriz;
    int linha;
    int coluna;
    int numOcorrencias;
    int numRec;

}tipoCruzada;

void imprime(char **m, int c, int l);
void leArquivo(tipoCruzada *c, char **m, char *nomeArq);
int valida(int linha, int coluna, int x, int y);
int procura(tipoCruzada *c, char **m, char *nome, int x, int y, int posPalavra, int direcao);
void inicializarCruzada(tipoCruzada *c);
int **alocarMatriz(int Linhas, int Colunas);
void initStats(tipoCruzada *c);
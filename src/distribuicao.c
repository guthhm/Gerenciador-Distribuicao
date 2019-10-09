/*=====================================================================================================================
Gerenciador de distribuição (@version) v0.01;
Created by (@author): Gustavo Martins e Braulindo Moreira;
Número IST: 91632;
Curso: Mestrado Integrado em Engenharia Eletrotécnica e de Computadores (MEEC);
Disciplina: Programação;
Ano: 2019;

Descrição: Este programa consiste em organizar de acordo com regras predefinidas a distribuição dos funcionários e aeronaves
de uma empresa fictícia e exibir esta disbribuição de forma gráfica no terminal;

======================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define version 0.01
#define YES 1
#define NO 0

void TablePrinter (char matriz_dist[8][8]) {

    //char matriz_dist[8][8] = {0};

    printf("   0  1  2  3  4  5  6  7\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i);
        for (int j = 0; j < 8; j++) {
            if (matriz_dist[i][j] != 'V' || matriz_dist[i][j] != '*')            
                matriz_dist[i][j] = '.';
            printf(" %c ", matriz_dist[i][j]);
        }    
        printf("\n");    
    }

}

int main (void) {

    int x = 0, y = 0;
    char matriz_dist[8][8] = {0}, linha[6], ocupante;
    FILE *dist_file;

    dist_file = fopen("../dist1.txt", "r");

    if (dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        exit(1);
    }

    while (fgets(linha, 6, dist_file) != NULL)
    {
        sscanf(linha, "%d %d %c", &x, &y, &ocupante);
        printf("%d - x    %d - y    %c - ocupante\n", x, y, ocupante);
        matriz_dist[x][y] = ocupante;
    }
    
    

    printf("Bem-vindo ao gerenciador de distribuicao versao %g. \n\n", version);

    //TablePrinter(matriz_dist);
    
    printf("   0  1  2  3  4  5  6  7\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i);
        for (int j = 0; j < 8; j++) {
            if (matriz_dist[i][j] != 'V' && matriz_dist[i][j] != '*')            
                matriz_dist[i][j] = '.';
            printf(" %c ", matriz_dist[i][j]);
        }    
        printf("\n");    
    }


    return 0;
}
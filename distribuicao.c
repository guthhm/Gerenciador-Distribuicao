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

int main (void) {

    char matriz_dist[8][8];

    printf("   1  2  3  4  5  6  7  8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i+1);
        for (int j = 0; j < 8; j++) {
            matriz_dist[i][j] = '.';
            printf(" %c ", matriz_dist[i][j]);
        }    
        printf("\n");    
    }
    
    return 0;
}
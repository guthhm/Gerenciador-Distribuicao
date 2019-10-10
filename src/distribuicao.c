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
#include <string.h>

/*---------- Definições gerais ----------*/
#define version 0.01
#define YES 1
#define NO 0

void TablePrinter (char matriz_dist[8][8]) {

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
    printf("\n");
}

int main (void) {

    int x = 0, y = 0, k = 0, valor =0;
    char matriz_dist[8][8] = {0}, linha[6], ocupante, file_list[10][20] = {0}, user_input[10] = {0}, file_to_open[30];
    FILE *primary_dist_file;
    FILE *dist_file;

    primary_dist_file = fopen("../distribuicao.txt", "r");

    if (primary_dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        exit(1);
    }

    while (fgets(file_list[k], 10, primary_dist_file) != NULL)
    {
        printf("%s\t k:%d\n", file_list[k], k);
        if (fscanf(primary_dist_file, "%s") != "\n")
        {
            k++;
        }

    }

    fclose(primary_dist_file);

    printf("\n\tBem-vindo ao gerenciador de distribuicao versao %g. \n\n", version);
    printf("Estes sao os ficheiros de distribuicao disponiveis:\n\n\n");
    
    for (int i = 0; i < k; i++)
    {
        printf("%d: %s\n", i+1, file_list[i]);
    }

    printf("\n\n");

    printf("Por favor, digite o numero ou nome correspondente a distribuicao desejada:\n>");
    do
    {
        scanf("%s", &user_input);

        if (strlen(user_input) > 1)
        {
            for (int i = 0; i < k; i++)
            {
                if (strstr(user_input, file_list[i]) != NULL) {
                    valor = i+1; // Faz com que o valor nunca seja 0 para que possa sair do loop
                    break;
                }
            }
        
        } else
        {
            if (user_input[0] > '0' && user_input[0] <= '9')
            {
                printf("Valor valido\n");
                valor = user_input[0] - '0'; // Converte o valor em ASCII para o equivalente em integer
            }else
            {
                printf("O valor digitado e invalido, por favor insira um valor valido\n>");
                valor = NO;
            }
        }
    } while (valor == 0);

    printf("\n Valor: %d\n\n", valor);

    valor = valor - 1;

    sprintf(file_to_open, "../%s", file_list[valor]);  // Cria o path para que o arquivo desejado seja aberto

    dist_file = fopen(file_to_open, "r");

    if (dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        exit(1);
    }

    while (fgets(linha, 6, dist_file) != NULL)
    {
        if (sscanf(linha, "%d") <= 3)
        {
            printf("%s", linha);
        }
        
        //sscanf(linha, "%d %d %c", &x, &y, &ocupante);
        //printf("%d - x    %d - y    %c - ocupante\n", x, y, ocupante);
        matriz_dist[x][y] = ocupante;
    }

    fclose(dist_file);

    TablePrinter(matriz_dist);

    return 0;
}
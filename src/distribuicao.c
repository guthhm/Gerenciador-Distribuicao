/*=====================================================================================================================
Gerenciador de distribuição (@version) v0.01;
Created by (@author): Gustavo Martins e Braulindo Moreira;
Número IST: 91632  e  94325;
Curso: Mestrado Integrado em Engenharia Eletrotécnica e de Computadores (MEEC);
Disciplina: Programação;
Ano: 2019;

Descrição: Este programa consiste em organizar de acordo com regras predefinidas a distribuição dos funcionários e aeronaves
de uma empresa fictícia e exibir esta distribuição de forma gráfica no terminal;
======================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*---------- Definições gerais ----------*/

#define version 0.01
#define YES 1
#define NO 0
#define WRITE_INFO_LINE 0
#define APPEND 1

void ResultWriter (int open_mode, int status_code, char file_to_open[23]) {

    char session_ID[7];
    FILE *result_file;
    time_t now = time(NULL);

    struct tm *t = localtime(&now); /* Struct que armazena informações do sistema de data e hora */

    result_file = fopen("../resultados.txt", "a");

    if (open_mode == WRITE_INFO_LINE)
    {
        for (int i = 0; i < 6; i++)
        {
            session_ID[i] = (rand() % 26) + 'A';
        }

        fprintf(result_file, "ID: %s ", session_ID);
        fprintf(result_file, "%s %d/%d/%d %d:%d\n", file_to_open, t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min);

        switch (status_code)
        {
        case 201:
            fprintf(result_file, "Status %d - O ficheiro distribuicao.txt nao foi encontrado ou aberto corretamente.\n", status_code);
            break;

        case 221:
            fprintf(result_file, "Status %d - Existem ficheiros inválidos apontados pelo ficheiro distribuicao.txt.\n", status_code);
            break;
        
        default:
            break;
        }
        
    }
    if (open_mode == APPEND)
    {
        /* code */
    }

    fclose(result_file);
}

void TablePrinter (char matriz_dist[7][7]) {

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

    int x = 0, y = 0, k = 0, valor = 0, error_flag = 0, line_count = 0, status_code = 0, open_mode;
    char matriz_dist[7][7] = {0}, linha[6], ocupante, file_list[20][20] = {0}, user_input[20] = {0}, file_to_open[23];
    FILE *primary_dist_file, *dist_file;

    srand(time(NULL));

    primary_dist_file = fopen("../distribuicao.txt", "r");

    if (primary_dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        ResultWriter(WRITE_INFO_LINE, 201, "NULL");
        exit(1);
    } else
    {
        char buffer[20];

        while ( fgets ( buffer, sizeof buffer, primary_dist_file ) != NULL ) /* read a line */
        {
            if (strstr(buffer, ".txt") && buffer[0] != '\n')
            {
                buffer[strlen(buffer)-1] = '\0';
                strcpy(file_list[k], buffer);
                k++;
            } else
            {
                status_code = 221;
            }
            
        }

        fclose (primary_dist_file);
    }

    printf("\n\tBem-vindo ao gerenciador de distribuicao versao %g. \n\n", version);

    do
    {

        printf("Estes sao os ficheiros de distribuicao disponiveis:\n\n\n");
        
        for (int i = 0; i < k; i++)
        {
            printf("%d: %s\n", i+1, file_list[i]);
        }

        printf("\n");    
        printf("Por favor, digite o numero ou nome (incluindo extensao) correspondente a distribuicao desejada:\n>");

        do
        {
            scanf("%s", &user_input);

            if (strlen(user_input) > 1)
            {
                for (int i = 0; i < k; i++)
                {
                    if (strstr(user_input, file_list[i]) != NULL) {
                        valor = i+1;  // Faz com que o valor nunca seja 0 para que possa sair do loop
                        break;
                    }
                }
            
            } else
            {
                if (user_input[0] > '0' && user_input[0] <= '9')
                {
                    valor = user_input[0] - '0'; // Converte o valor em ASCII para o equivalente em integer
                }else
                {
                    printf("O valor digitado e invalido, por favor insira um valor valido\n>");
                    valor = NO;
                }
            }
        } while (valor == 0);

        valor = valor - 1;

        printf("\n Valor: %d\n\n", valor);
        strcpy(file_to_open, "../");
        strcat(file_to_open, file_list[valor]);

        open_mode = WRITE_INFO_LINE;
        ResultWriter(open_mode, status_code, file_to_open);

        //printf("\nFile to open: %s", file_to_open); /* Valores impressos para somente para verificação */
        //printf("\n%sTeste", file_list[valor]);

        dist_file = fopen(file_to_open, "r");

        if (dist_file == NULL)
        {
            printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
            exit(1);
        }

        printf("\n");
        error_flag = 0;

        while (fgets(linha, 6, dist_file) != NULL)
        {
            if (linha[0] <= '3')
            {
                printf("%s", linha);
            }
        
            sscanf(linha, "%d %d %c", &x, &y, &ocupante);
            //printf("%d - x    %d - y    %c - ocupante\n", x, y, ocupante);

            if (x > 7 || x < 0 || y > 7 || y < 0)
            {
                error_flag = 1;
                if (ocupante != '*' && ocupante != 'V')
                {
                    error_flag = 2;
                    break;
                }
                break;
                
            } else
            {
                matriz_dist[x][y] = ocupante;
            }

            line_count++;
            
        }

        printf("\n\n");

        switch (error_flag)
        {
        case 1:
            //system ("tput clear");
            printf("Oh Oh! Parece que as coordenadas indicadas na linha %d nao sao validas, por favor corrija o problema para que a distribuicao possa ser validada. Nao e necessario reiniciar o programa.\n\n", line_count/2+1);        
            break;
        case 2:
            //system ("tput clear");
            printf("Não sabemos qual o ocupante da posicao indicada na linha %d, por favor corrija o ficheiro para prosseguirmos.\n\n", line_count/2+1);
            break;
        default:
            break;
        }

        line_count = 0;
        fclose(dist_file);

    } while (error_flag != NO);

    TablePrinter(matriz_dist);

    return 0;
}
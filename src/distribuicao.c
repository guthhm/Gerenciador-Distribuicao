/*=====================================================================================================================
Gerenciador de distribuição (@version) v1.00;
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
#include "validator.h"

/*---------- Definições gerais ----------*/

#define version 1.01
#define YES 1
#define NO 0
#define VAZIO 0
#define OK 1
#define ADJACENTE 2
#define SOZINHO 3
#define WRITE_INFO_LINE 0
#define APPEND 1

void ResultWriter (int open_mode, int status_code[5], char file_to_open[23], int func, int aero) {

    int count = 0;
    char session_ID[7];
    FILE *result_file;
    time_t now = time(NULL);

    struct tm *t = localtime(&now); /* Struct que armazena informações do sistema de data e hora */

    result_file = fopen("../resultados.txt", "a");

    if (open_mode == WRITE_INFO_LINE)
    {
        for (int i = 0; i < 6; i++)
            session_ID[i] = (rand() % 26) + 'A';

        fprintf(result_file, "ID: %s %s %d/%d/%d %d:%d ", session_ID, file_to_open, t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min, func, aero);
        for (int i = 0; i < 6; i++) {
            if (status_code[i] == 201 || status_code[i] == 301) {
                fprintf(result_file, "ERRO ", session_ID);
                break;
            }
            if (status_code[i] == 100){
                fprintf(result_file, "OK ", session_ID);
                printf("\nA execucao do ficheiro foi um sucesso.\n");
                break;
            }
            
            if (i == 5)
                fprintf(result_file, "AVISO ", session_ID);
        }

        fprintf(result_file, "Funcionarios: %d Aeronaves: %d\n", func, aero);

        for (int i = 0; i < 6; i++)
        {
            switch (status_code[i])
            {
            case 201:
                fprintf(result_file, "\tStatus %d - O ficheiro distribuicao.txt nao foi encontrado ou aberto corretamente.\n", status_code[i]);
                break;

            case 211:
                fprintf(result_file, "\tStatus %d - Existem ficheiros inválidos apontados pelo ficheiro distribuicao.txt.\n", status_code[i]);
                break;

            case 212:
                fprintf(result_file, "\tStatus %d - Caracteres contidos em um dos ficheiros indicados em distribuicao.txt são inválidos\n", status_code[i]);
                break;

            case 302:
                fprintf(result_file, "\tStatus %d - A coordenada 'X' indicada pelo ficheiro de distribuição escolhido é inválida.\n", status_code[i]);
                break;

            case 303:
                fprintf(result_file, "\tStatus %d - A coordenada 'Y' indicada pelo ficheiro de distribuição escolhido é inválida.\n", status_code[i]);
                break;

            case 304:
                fprintf(result_file, "\tStatus %d - O ocupante em uma das posições indicadas não é válido.\n", status_code[i]);
                break;

            case 321:
                fprintf(result_file, "\tStatus %d - O número de funcionários e aeronaves não é o mesmo.\n", status_code[i]);
                break;

            case 331:
                fprintf(result_file, "\tStatus %d - Pelo menos uma aeronave não tem funcionario atribuido.\n", status_code[i]);
                break;

            default:
                break;
            }
        }

        for (int i = 0; i < 6; i++)
            if (status_code[i] == 301)
                fprintf(result_file, "ERRO CRÍTICO - Não foi possível abrir o ficheiro de distribuição apontado por distribuicao.txt (301)\n");
        
        fprintf(result_file, "\n");
        
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
            printf(" %c ", matriz_dist[i][j]);
        }    
        printf("\n");    
    }
    printf("\n");

}

int main (void) {

    int x = 0, y = 0, k = 0, funcionario = 0, aeronave = 0, valor = 0, status_count = 0, error_flag = 0, line_count = 0, status_code[5] = {0}, aux = 0, matriz_validacao[7][7] = {0};
    char matriz_dist[7][7] = {NULL}, linha[10], ocupante, file_list[20][20] = {0}, user_input[20] = {0}, file_to_open[23];
    FILE *primary_dist_file, *dist_file;

    srand(time(NULL));

    primary_dist_file = fopen("../distribuicao.txt", "r");

    if (primary_dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        ResultWriter(WRITE_INFO_LINE, 201, "NULL", 0, 0);
        exit(1);
    } else
    {
        char buffer[20];

        while ( fgets ( buffer, sizeof buffer, primary_dist_file ) != NULL ) /* read a line */
        {
            if (strstr(buffer, ".txt") && buffer[0] != '\n')
            {
                if (buffer[strlen(buffer)-1] == '\n')
                    buffer[strlen(buffer)-1] = '\0';
                strcpy(file_list[k], buffer);
                k++;
                printf("%d: %s\n", k, buffer);
            } else
            {
                status_code[status_count] = 211;
                status_count++;
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

        //printf("\n Valor: %d\n\n", valor);
        strcpy(file_to_open, "../");
        strcat(file_to_open, file_list[valor]);

        //printf("\nFile to open: %s", file_to_open); /* Valores impressos para somente para verificação */
        //printf("\n%sTeste", file_list[valor]);

        dist_file = fopen(file_to_open, "r");

        if (dist_file == NULL)
        {
            printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
            status_code[status_count] = 301;
            ResultWriter(WRITE_INFO_LINE, status_code, file_to_open, 0, 0);
            exit(1);
        }

        //printf("\n");
        error_flag = 0;

        while (fgets(linha, sizeof linha, dist_file) != NULL)
        {
            //linha[strlen(linha)-1] = '\0';

            if (linha[0] <= '3')
                printf("%s", linha);
        
            sscanf(linha, "%d %d %c", &x, &y, &ocupante);
            //printf("%d - x    %d - y    %c - ocupante\n", x, y, ocupante);
            //printf("X: %d | Y: %d | Ocupante: %c\n", x, y, ocupante);

            if (x > 7 || x < 0)
            {
                error_flag = 1;
                status_code[status_count] = 302;
                status_count++;
                break;                
            } 
            if (y > 7 || y < 0)
            {
                error_flag = 1;
                status_code[status_count] = 303;
                status_count++;
                break;    
            } 
            if (ocupante != '*' && ocupante != 'V') {
                status_code[status_count] = 304;
                status_count++;
            }
            if (x <= 7 && x >=0 && y <= 7 && y >= 0){
                matriz_dist[x][y] = ocupante;
                //printf("\nTeste\n");
            }
        
            line_count++;

        }

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

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) {
                if (matriz_dist[i][j] == '*')
                    funcionario++;
                if (matriz_dist[i][j] == 'V')
                    aeronave++;
            }

        if (funcionario > aeronave || aeronave > funcionario)
        {
            status_code[status_count] = 321;
            status_count++;
        }

        for (int i; i < 6; i++)
            if (status_code[i] != NULL)  
                aux++;      

        if (aux == 0)
            status_code[0] = 100;
        
        ResultWriter(WRITE_INFO_LINE, status_code, file_to_open, funcionario, aeronave);

    } while (error_flag != NO);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (matriz_dist[i][j] != 'V' && matriz_dist[i][j] != '*')            
                matriz_dist[i][j] = '.';
        }    
    }

    printf("\n\n");
    DoValidation(&matriz_validacao, matriz_dist, &status_code, &status_count);
    TablePrinter(matriz_dist);

    return 0;
}
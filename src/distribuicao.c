/*=====================================================================================================================
Gerenciador de distribuição (@version) v0.01;
Created by (@author): Gustavo Martins e Braulindo Moreira;
Número IST: 91632;
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

    int x = 0, y = 0, k = 0, valor = 0, error_flag = 0, line_count = 0, error_code;
    char matriz_dist[7][7] = {0}, linha[6], ocupante, file_list[20][20] = {0}, user_input[20] = {0}, file_to_open[30], buffer[20];
    FILE *primary_dist_file;
    FILE *dist_file;

    int hours, minutes, seconds, day, month, year;

	// time_t is arithmetic time type
	time_t now;
	
	// Obtain current time
	// time() returns the current time of the system as a time_t value
	time(&now);

	// Convert to local time format and print to stdout
	printf("Today is : %s", ctime(&now));

    primary_dist_file = fopen("../distribuicao.txt", "r");

    if (primary_dist_file == NULL)
    {
        printf("Erro ao abrir o ficheiro, verifique se o ficheiro existe e tente novamente.");
        exit(1);
    }

    while (fgets(buffer, 20, primary_dist_file) != NULL)
    {
        if (strstr(buffer, ".txt"))
        {
            if (buffer[0] != '\n')
            {
                sprintf(file_list[k], "%s", buffer);
                k++;
            }
        }  
        else
        {
            error_code = 211;  // Conferir codigo de erro indicado na tabela
        }
              
    }

    fclose(primary_dist_file);

    printf("\n\tBem-vindo ao gerenciador de distribuicao versao %g. \n\n", version);

    do
    {

        printf("Estes sao os ficheiros de distribuicao disponiveis:\n\n\n");
        
        for (int i = 0; i < k; i++)
        {
            printf("%d: %s", i+1, file_list[i]);
        }

        printf("\n\n");

    
        printf("Por favor, digite o numero ou nome (incluindo extensao) correspondente a distribuicao desejada:\n>");

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
                    //printf("Valor valido\n");
                    valor = user_input[0] - '0'; // Converte o valor em ASCII para o equivalente em integer
                }else
                {
                    printf("O valor digitado e invalido, por favor insira um valor valido\n>");
                    valor = NO;
                }
            }
        } while (valor == 0);

        //printf("\n Valor: %d\n\n", valor);

        valor = valor - 1;

        sprintf(file_to_open, "../%s", file_list[valor]);  // Cria o path para que o arquivo desejado seja aberto
        //printf("\n%s\n", file_to_open);

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
            system ("tput clear");
            printf("Oh Oh! Parece que as coordenadas indicadas na linha %d nao sao validas, por favor corrija o problema para que a distribuicao possa ser validada. Nao e necessario reiniciar o programa.\n\n", line_count/2+1);        
            break;
        case 2:
            system ("tput clear");
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
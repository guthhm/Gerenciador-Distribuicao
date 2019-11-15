#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define SOZINHO 1
#define VAZIO 0

void DoValidation (int *validacao[7][7], char dist[7][7], int *erros[5], int *erro_count) {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (dist[i][j] == 'V')
            {
                if (dist[i-1][j] == '*' || dist[i][j-1] == '*' || dist[i][j+1] == '*' || dist[i+1][j] == '*')
                {
                    *validacao[i][j] == OK;
                } else
                {
                    *validacao[i][j] = SOZINHO;
                    *erros[*erro_count] = 312;
                    *erro_count++;
                    printf("\n%d %d\n", i, j);
                }
                
                
            } else if (dist[i][j] == '*')
            {
                /* code */
            } else
            {
                *validacao[i][j] = VAZIO;
            }
            
        }
        
    }
    
}
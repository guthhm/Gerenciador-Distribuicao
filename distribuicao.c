#include <stdio.h>
#include <stdlib.h>

int main (void) {

    char matriz_dist[8][8];

    printf("   1  2  3  4  5  6  7  8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i+1);
        for (int j = 0; j < 8; j++) {
            matriz_dist[i][j] = '*';
            printf(" %c ", matriz_dist[i][j]);
        }    
        printf("\n");    
    }
    
    return 0;
}
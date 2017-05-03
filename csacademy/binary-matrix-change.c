#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int first_line = 1, first_column = 1;
int n, m;

int main() {
    scanf("%d %d", &n, &m);

    int matrix[n][m];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j += 1) 
            scanf("%d", &matrix[i][j]);
    for (int i = 0; i < n; i++)
        first_column &= matrix[i][0];
    for (int j = 0; j < m; j++)
        first_line &= matrix[0][j];
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j += 1) 
            if (matrix[i][j] == 0) 
                matrix[i][0] = matrix[0][j] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) 
                printf("%d", (first_line   & matrix[0][j]));
            else if (j == 0) 
                printf("%d", (first_column & matrix[i][0]));
            else 
                printf("%d", (matrix[i][0] & matrix[0][j]));
            printf(" ");
        }
        puts("");
    }
    return 0;
}

























































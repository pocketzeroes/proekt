#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    scanf("%d", &n);
    char A[n][n];
    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            A[i][j] = getchar();
        }
        getchar();
    }
    int black;
    int white;
    for(int i=0; i<n; i++){
        black = 0;
        white = 0;
        for(int j=0; j<n; j++){
            char jj = A[i][j];
            if(jj == 'B')
                ++black;
            else
                ++white;
        }
        if(black != white){
            puts("0");
            return 0;
        }
    }
    for(int i=0; i!=n; ++i){
        black = 0;
        white = 0;
        for(int j=0; j!=n; ++j){
            if(A[j][i] == 'B')
                ++black;
            else
                ++white;
        }
        if(black != white){
            puts("0");
            return 0;
        }
    }
    for(int i=0; i<n; i++){
        char temp[n+1];
        for(int j=0; j<n; j++){
            char jj = A[i][j];
            temp[j] = jj;
        }
        temp[n] = '\0';
        if(strstr(temp, "BBB") != NULL||
           strstr(temp, "WWW") != NULL){
            puts("0");
            return 0;
        }
    }
    for(int i=0; i!=n; ++i){
        char temp[n+1];
        for(int j=0; j!=n; ++j){
            temp[j] = A[j][i];
        }
        temp[n] = '\0';
        if(strstr(temp, "BBB") != NULL||
           strstr(temp, "WWW") != NULL){
            puts("0");
            return 0;
        }
    }
    puts("1");
    return 0;
}

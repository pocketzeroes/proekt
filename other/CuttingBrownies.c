#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}

int n;
bool win[501][501];

int main(){
    for(int i = 1; i <= 500; ++i){
        for(int j = 1; j <= 500; ++j){
            win[i][j] = false;
            for(int k = 1; k < j; ++k){
                win[i][j] = win[i][j] || (!win[k][i] && !win[j - k][i]);
            }
        }
    }
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        int b, d;
        char*s;
        scanf("%d%d", &b, &d);
        s=getstr();
        printf("%s ", s);
        if(s[0] == 'H'){
            puts(win[b][d] ? "can win" : "cannot win");
        }
        else{
            puts(win[d][b] ? "can win" : "cannot win");
        }
    }
    return 0;
}

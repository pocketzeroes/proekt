#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    if((n + m) & 1){
        printf("0");
        return 0;
    }
    puts("1");
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            printf("1 1 ");
        }
        puts("");
    }
    return 0;
}

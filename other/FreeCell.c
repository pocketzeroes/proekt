#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    puts((k<=(n+1)<<m) ? "yes" : "no");
    return 0;
}

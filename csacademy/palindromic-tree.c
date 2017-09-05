#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}

char pattern[] = "001011";

int main(){
    int n;
    scanf("%d", &n);
    printf("%d\n", min(n, 8) - (n == 8));
    for(int i = 0; i < n; ++i)
        putchar(pattern[i % 6]);
    puts("");
}

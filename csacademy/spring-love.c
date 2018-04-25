#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int a, b, c = 0;
    scanf("%d", &a);
    for(int i = 1; i <= a; i++){
        scanf("%d", &b);
        c += b;
    }
    if(c % 2 == 1)
        puts("1");
    else
        puts("0");
    return 0;
}

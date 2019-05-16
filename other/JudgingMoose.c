#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

int main(){
    int l, r;
    scanf("%d %d", &l, &r);
    int val = 2 * max(l, r);
    if (val == 0)
        puts("Not a moose");
    else if (l == r)
        printf("Even %d\n", val);
    else
        printf("Odd %d\n", val);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int main(){
    int A, L, H;
    scanf("%d %d %d", &A, &L, &H);
    printf("%d\n", L-2*A-H);
    return 0;
}

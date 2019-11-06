#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

enum{ MAXN = 64};

typedef struct{
    double m[MAXN][MAXN];
}mtx;

mtx opMul(mtx tva, mtx oth){
    mtx res; clr(res.m);
    for(int i=0; i<MAXN; i++)
        for(int j=0; j<MAXN; j++)
            for(int k=0; k<MAXN; k++)
                res.m[i][j] += tva.m[i][k]*oth.m[k][j];
    return res;
}
mtx matrix_pow(int n, mtx m){
    if(n == 1)
       return m;
    mtx m2 = matrix_pow(n/2, m);
    return n%2 ? opMul(m, opMul(m2, m2)):opMul(m2, m2);
}
int r, c, n;
double p;

int main(){
    scanf("%d %d %d %lf", &r, &c, &n, &p);
    mtx dice; clr(dice.m);
    for(int i=0; i<r*c; i++){
        for(int j=i+1; j<=i+6; j++)
            dice.m[i][(int)fmin(j, r*c-1)] += 1.0/6.0;
    }
    mtx ladder; clr(ladder.m);
    for(int i=0; i<r*c; i++)
        ladder.m[i][i] = 1;
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        ladder.m[a][a] = 0;
        ladder.m[a][b] = 1;
    }
    mtx mat = opMul(dice, ladder);
    int a = 1, 
        b = 100000000;
    while(a < b){
        int m = (a+b) / 2;
        if(matrix_pow(m, mat).m[0][r*c-1] >= p)
            b = m;
        else
            a = m+1;
    }
    printf("%d\n", a);
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double**newmat(int x, int y){
  double**rv = calloc(x, sizeof(double*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(double));
  return rv;
}
/////////////////////////////////////////
int n;

double*gauss(double**A){
    for(int i=0; i<n; i++){
        double maxEl = fabs(A[i][i]);
        int maxRow   = i;
        for(int k=i+1; k<n;  k++){
            if(fabs(A[k][i]) > maxEl){
                maxEl = fabs(A[k][i]);
                maxRow = k;
            }
        }
        for(int k=i; k<n+1; k++){
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k]      = tmp;
        }
        for(int k=i+1; k<n;  k++){
            double c;
            if(A[i][i] != 0){
                c = -A[k][i]/A[i][i];
                for(int j=i; j<n+1; j++){
                    if(i==j)
                        A[k][j] = 0;
                    else
                        A[k][j] += c * A[i][j];
                }
            }
        }
    }
    double*x = calloc(n, sizeof(double));
    for(int i=n-1; i>=0; i--){
        if(A[i][i] != 0){
            x[i] = A[i][n]/A[i][i];
            for(int k=i-1; k>=0; k--)
                A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}
int main(){
    while(scanf("%d", &n)==1 && n){
        double**a;
        double b[n];
        a = calloc(n, sizeof(double*));
        for(int i=0; i<n; i++)
            a[i] = calloc(n, sizeof(double));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%lf", &a[i][j]);
        for(int i=0; i<n; i++)
            scanf("%lf", &b[i]);
        double**A=newmat(n, n+1);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                A[i][j] = a[i][j];
        for(int i=0; i<n; i++)
            A[i][n] = b[i];
        double*x = gauss(A);
        int state = 0;
        for(int i=0; i<n; i++){
            int j = 0;
            while(A[i][j] == 0 && j<=n)
                j++;
            if(j==n && (A[i][n] != 0))
                state = 2;
            if(j==n+1)
                state = 1;
        }
        switch(state){
          case 0:
            for(int i=0; i<n; i++){
                if(i)
                    printf(" ");
                printf("%lf", x[i]);
            }
            puts("");
            break;
          case 1: puts("multiple"    ); break;
          case 2: puts("inconsistent"); break;
        }
    }
    return 0;
}

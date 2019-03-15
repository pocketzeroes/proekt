#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) { typeof(a) tmp; tmp = a; a = b; b = tmp; }
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int n;
double epsilon = 1e-9;

int*gauss(double**A, double*B, double*X){
    int*where=calloc(n, sizeof(int));
    fill(where, n, -1);
    for(int r=0, c=0; r<n && c<n; c++){
        int p = r;
        for(int i=r+1; i<n; i++){
            if(fabs(A[i][c]) > fabs(A[p][c]))
                p = i;
        }
        if(fabs(A[p][c]) < epsilon)
            continue;
        swap(A[r], A[p]);
        swap(B[r], B[p]);
        where[c] = r;
        double x = 1.0 / A[r][c];
        for(int i = 0; i < n; i++){
            if(i != r){
                double y = A[i][c] * x;
                for(int j = c; j < n; j++)
                    A[i][j] = A[i][j] - A[r][j] * y;
                B[i] = B[i] - B[r] * y;
            }
        }
        r++;
    }
    for(int i = 0; i < n; i++)
        if(where[i] != -1)
           X[i] = B[where[i]] / A[where[i]][i];
    for(int i = 0; i < n; i++){
        double s = 0.0;
        for(int j = 0; j < n; j++)
            s = s + X[j] * A[i][j];
        if(fabs(s - B[i]) >= epsilon)
            return(int*)0xdeadbeef;
    }
    for(int i = 0; i < n; i++){
        if(where[i] != -1){
            for(int j = 0; j < n; j++){
                if(j != i && fabs(A[where[i]][j]) > epsilon){
                    where[i] = -1;
                    break;
                }
            }
        }
    }
    return where;
}
int equationsolverplus(){
    while(scanf("%d", &n)==1 && n){
        double**A=calloc(n,sizeof(double*));//[n][n];
        for(int i=0; i<n; i++)
            A[i] = calloc(n, sizeof(double));
        
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                scanf("%lf", &A[i][j]);
            }
        }
        double B[n];
        for(int i=0; i<n; i++){
            scanf("%lf", &B[i]);
        }
        double X[n]; memset(X, 0, sizeof(X));
        int*where = gauss(A, B, X);
        if(where == (int*)0xdeadbeef)
            puts("inconsistent");
        else{
            for(int i=0; i<n; i++){
                if (where[i] == -1)
                    printf("?");
                else
                    printf("%lf", X[i]);
                if (i + 1 < n)
                    printf(" ");
            }
            puts("");
        }
    }
}
int main() {
    equationsolverplus();
}

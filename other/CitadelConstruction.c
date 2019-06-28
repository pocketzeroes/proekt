#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
#define swap(a,b) do{int tmp; tmp = a; a = b; b = tmp; }while(0)

enum{ nmax = 1000};
int X[nmax], 
    Y[nmax];


int area2 (int a, int b, int c){
    return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
}
int convexhull (int n){
    int m, i, j = 0;
    for (i = 1; i < n; i++)
        if (X[i] < X[j])
            j = i;
    swap(X[0], X[j]);
    swap(Y[0], Y[j]);
    for (m = 1; true; m++){
        j = (m==1?1:0); 
        for (i = 0; i < n; i++)
            if (area2(m-1, i, j) > 0) 
                j = i;
        if (j == 0) 
            return m;
        swap(X[m], X[j]);
        swap(Y[m], Y[j]);
    }
}
int ternarysearch (int a, int b, int m, int lb, int ub){
    int c1 = ((2*lb+ub)/3), c2 = ((lb+2*ub)/3);
    if (ub - lb < 3)
        return area2(a, c2%m, b);
    else if (area2(a, c1%m, b) > area2(a, c2%m, b))
        return ternarysearch(a, b, m, lb, c2);
    else
        return ternarysearch(a, b, m, c1, ub);
}
int main(){
    int runs, run, n, i, j, m, amax;
    scanf("%d", &runs);
    for (run = 0; run < runs; run++){
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d %d", &X[i], &Y[i]);
        m = convexhull(n);
        amax = 0;
        for (i = 0; i < m; i++)
            for (j = i+1; j < m; j++)
                amax = max(amax, ternarysearch(i, j, m, i, j) + ternarysearch(j, i, m, j, i+m));
        if (amax % 2 == 0)
            printf("%d\n", amax/2);
        else
            printf("%d.5\n", amax/2);
    }
    return 0;
}

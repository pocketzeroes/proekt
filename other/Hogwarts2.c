#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    int*ptr;
    int sz;
}vec;
vec newVec() {
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}




int N, A[200][200],
       B[200][200];
vec ops;

void read(int M, int X[200][200]){
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            X[i][j] = i==j;
    for (int i = 0, a, b; i < M; ++i) {
        scanf("%d%d", &a, &b);
        X[a][b] = X[b][a] = 1;
    }
}
void doswap(int i, int j, int k){
    j += j >= i;
    k += k >= i;
    swap(A[i][j], A[i][k]);
    swap(A[j][i], A[k][i]);
}
void red(int i){
    pb(ops, i+1);
    for (int j = N-2, k = 0; j > 0; k = j--) 
        doswap(i, j, k);
}
void green(int i) {
    pb(ops, -(i+1));
    for (int j = 0, k = N-2; j < N-2; k = j++) 
        doswap(i, j, k);
}
void move(int i, int jsrc, int jdst) {
    if ((N+jdst-jsrc) % N < (N+jsrc-jdst) % N) {
        while (jsrc != jdst) {
            red(i);
            jsrc = (jsrc + 1) % N;
            if (jsrc == i) 
                jsrc = (jsrc+1) % N;
        }
    }
    else {
        while (jsrc != jdst) {
            green(i);
            jsrc = (N + jsrc - 1) % N;
            if (jsrc == i) 
                jsrc = (N + jsrc-1) % N;
        }
    }
}
void easyfix(int i1, int j1, int i2, int j2) {
    if (i2 == i1+1) { 
        if (j2 == i1) {
            green(i1+1);
            j2 = (N+j2-1) % N;
        }
        swap(i2, j2);
    }
    else {
        move(i2, j2, i1+1);
    }
    move(i1, j1, i1+1);
    move(i1+1, i2, i1);
    move(i1, i1+1, j1);
}
void messyfix(int i, int j1, int j2) {
    if (A[i][j1] == A[i-1][0]) {
        messyfix(i, j2, j1);
        return;
    }
    move(i, j1, 0);
    red(0);
    move(i, j2, j1);
    green(0);
    move(i, j1, j2);    
    move(i, 0, j1);
}
void fix(int i, int j) {
    for (int ii = i+1; ii < N; ++ii)
        for (int jj = 0; jj < ii; ++jj)
            if (A[ii][jj] == B[i][j]) {
                easyfix(i, j, ii, jj);
                return;
            }
    for (int jj = j+1; jj < i; ++jj) {
        if (A[i][jj] == B[i][j]) {
            messyfix(i, j, jj);
            return;
        }
    }
}
int main(){
    int M;
    scanf("%d%d", &N, &M);
    read(M, A);
    read(M, B);
    for (int i = 1; i < N; ++i)
        for (int j = 0; j < i; ++j)
            if (A[i][j] != B[i][j])
                fix(i, j);
    printf("%d\n", ops.sz);
    for(int z=0;z<ops.sz;z++){int s = ops.ptr[z];
        printf("%c %d\n", s < 0 ? 'G' : 'R', s < 0 ? -s-1 : s-1);
    }
    return 0;
}

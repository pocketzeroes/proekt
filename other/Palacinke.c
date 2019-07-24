#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAXV = 25};
enum{ MAXE = 500};
enum{ SIZE = 1+2*MAXV};
enum{ MOD  = 5557};

int n;
int N, M, T;

typedef struct{
    int u, v, mask;
}edge;
edge E[MAXE];

void mult( int a[SIZE][SIZE], int b[SIZE][SIZE], int c[SIZE][SIZE] ){
    static int tmp[SIZE][SIZE];
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            tmp[i][j] = 0;
            for( int k = 0; k < n; ++k )
                tmp[i][j] += a[i][k] * b[k][j];
        }
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j )
            c[i][j] = tmp[i][j] % MOD;
}
int id( int u, int t ){
    return 1 + u*2 + t;
}
int solve( int mask ){
    static int A[SIZE][SIZE];
    static int B[SIZE][SIZE];
    for( int i = 0; i < n; ++i ){
        for( int j = 0; j < n; ++j ) {
            A[i][j] = 0;
            B[i][j] = i==j;
        }
    }
    A[0][0] = 1;
    for( int u = 0; u < N; ++u)
        A[id(u, 1)][id(u, 0)] = 1;
    for( int i = 0; i < M; ++i ) {
        ++A[id(E[i].v, 0)][id(E[i].u, 0)];
        if( !(E[i].mask & mask))
            ++A[id(E[i].v, 0)][id(E[i].u, 1)];
        if( E[i].v == 0 ){
            ++A[0][id(E[i].u, 0)];
            if( !(E[i].mask & mask) )
                ++A[0][id(E[i].u, 1)];
        }
    }
    for( int k = T;; ){
        if( k & 1 )
            mult( B, A, B );
        if( !(k >>= 1) )
            break;
        mult( A, A, A );
    }
    return B[0][id(0, 0)];
}
int main(){
    scanf("%d %d", &N, &M);
    n = 1 + 2*N;
    for(int i = 0; i < M; ++i){
        char*s;
        scanf("%d %d", &E[i].u, &E[i].v);
        s=getstr();
        --E[i].u; --E[i].v;
        E[i].mask = 0;
        if(strchr(s, 'B') != NULL) E[i].mask |= 1;
        if(strchr(s, 'J') != NULL) E[i].mask |= 2;
        if(strchr(s, 'M') != NULL) E[i].mask |= 4;
        if(strchr(s, 'P') != NULL) E[i].mask |= 8;
    }
    scanf("%d", &T);
    int ret = 0;
    for( int mask = 0; mask < 16; ++mask ){
        int sgn = 1;
        for( int i = 0; i < 4; ++i )
            if( (mask>>i)&1 )
                sgn = -sgn;
        ret += sgn * solve(mask);
    }
    printf("%d\n", (ret%MOD + MOD)%MOD );
    return 0;
}

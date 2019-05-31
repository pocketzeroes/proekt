#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

enum{ MAXN = 1000100};

int n, k;
int q;
int X  [ MAXN ];
int Niz[ MAXN ];
long long Prefix[ MAXN ];

int main(){
    memset( Niz, 0, sizeof Niz );
    scanf( "%d %d", &n, &k );
    for( int i = 0; i < k; ++i )         
        scanf( "%d", X + i );
    qsort(X, k, sizeof(int), cmp);
    for( int i = 0; i < k; ) {
        int temp = X[i];
        int cnt = 0;
        for( ; i < k && X[i] == temp; ++i )
            ++cnt;
        for( int iter = 0; iter < n; iter += temp )
            Niz[ iter ] += cnt;
    }
    Prefix[0] = 0;
    for( int i = 0; i < n; ++i )
        Prefix[i+1] = Prefix[i] + Niz[i];
    scanf( "%d", &q );
    for( int i = 0; i < q; ++i ) {
        int l, r; scanf( "%d %d", &l, &r );
        printf( "%lld\n", Prefix[r+1] - Prefix[l] );
    }
    return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

enum{ MOD = 10301};
int N, A, B;
int memoL[1024][1024][2];
int memoR[1024][1024][2];

void add(int*a, int b){
   (*a) += b;
   if(*a >= MOD )
     (*a)-= MOD;
}
int recR(int n, int rub, bool ok){
#define ret memoR[n][rub][ok]
    if(ret != -1)
       return ret;
    ret = ok;
    if(rub <= n)
        add(&ret, recR(n-rub, rub, true) );
    if( n )
        add(&ret, recR(n-1, rub+1, false) );
    return ret;
    #undef ret
}
int recL( int n, int rub, bool ok){
#define ret memoL[n][rub][ok]
    if(ret != -1 )
        return ret;
    ret = 0;
    if( ok )
        add(&ret, recR(n, B, true) );
    if( rub <= n )
        add(&ret, recL(n-rub, rub, true) );
    if( n )
        add(&ret, recL(n-1, rub+1, false) );
    return ret;
    #undef ret
}
int main(){
    memset( memoL, -1, sizeof memoL );
    memset( memoR, -1, sizeof memoR );
    scanf( "%d%d%d", &N, &A, &B );
    printf( "%d\n", recL( N-A-B, A, true ) );
    return 0;
}

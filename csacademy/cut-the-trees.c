#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int read(){
    int q;
    scanf("%d", &q);
    return q;
}
enum{ maxn =(int) 1e5 + 50};
int n , D , H[maxn] , G[maxn] , F[maxn] , bad[maxn];
int main( int argc , char * argv[] ){
    n = read() , D = read();
    for(int i = 1 ; i <= n ; ++ i) 
        H[i] = read();
    for(int i = 1 ; i <= n ; ++ i) 
        G[i] = read();
    int cnt = 0;
    for(int i = 1 ; i <= n ; ++ i){
        if( H[i] <= D ){
            int w = ( D - H[i] ) / G[i];
            if( w <= n ) ++ F[w];
            ++ cnt;
        }
        int w = D / G[i];
        if( w <= n ) 
            ++bad[w];
    }
    int ret = 0;
    for(int i = 0 , k = 0 ; i <= n ; ++ i){
        ret = max( ret , min( n , cnt + i + 1 ) );
        cnt -= F[i];
        ++ k;
        if( bad[i] >= k ){
            n -= ( bad[i] - k );
            k = 0;
        }
        else 
            k -= bad[i];
    }
    printf( "%d\n" , ret );
    return 0;
}

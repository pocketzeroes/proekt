#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void swap(int*nums, int i, int j){
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
/////////////////////
enum{ MAXN = 50005};
int a[MAXN] , b[MAXN] ;
int prea[MAXN][2] , preb[MAXN][2] ;
int sufa[MAXN][2] , sufb[MAXN][2] ;
int n ;

double getlog ( int x , int y ){
    return x * log ( 2.0 ) + y * log ( 3.0 ) ;
}
void getlcm (){
    int ansa = 0 , ansb = 0 ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        int tmpa = min ( prea[i - 1][1] , sufa[i + 1][1] ) ;
        int tmpb = min ( preb[i - 1][1] , sufb[i + 1][1] ) ;
        tmpa = max ( tmpa , a[i] ) ;
        tmpb = max ( tmpb , b[i] ) ;
        if ( getlog ( tmpa , tmpb ) > getlog ( ansa , ansb ) ) {
            ansa = tmpa ;
            ansb = tmpb ;
        }
    }
    printf ( "%d %d" , ansa , ansb ) ;
}
void getgcd (){
    int ansa = 1000 , ansb = 1000 ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        int tmpa = max ( prea[i - 1][0] , sufa[i + 1][0] ) ;
        int tmpb = max ( preb[i - 1][0] , sufb[i + 1][0] ) ;
        tmpa = min ( tmpa , a[i] ) ;
        tmpb = min ( tmpb , b[i] ) ;
        if ( getlog ( tmpa , tmpb ) < getlog ( ansa , ansb ) ) {
            ansa = tmpa ;
            ansb = tmpb ;
        }
    }
    printf ( "%d %d" , ansa , ansb ) ;
}
void solve (){
    for ( int i = 1 ; i <= n ; ++ i ) {
        scanf ( "%d%d" , &a[i] , &b[i] ) ;
    }
    if ( n == 1 ) {
        printf ( "%d %d %d %d\n" , a[1] , b[1] , a[1] , b[1] ) ;
        return ;
    }
    if ( n == 2 ) {
        if ( a[1] < a[2] ) 
            swap(a, 1, 2);
        if ( b[1] < b[2] ) 
            swap(b, 1, 2);
        printf ( "%d %d %d %d\n" , a[1] , b[1] , a[1] , b[1] ) ;
        printf ( "%d %d %d %d\n" , a[2] , b[2] , a[2] , b[2] ) ;
        return ;
    }
    prea[0][0] = preb[0][0] = 0 ;
    prea[0][1] = preb[0][1] = 1000 ;
    sufa[n + 1][0] = sufb[n + 1][0] = 0 ;
    sufa[n + 1][1] = sufb[n + 1][1] = 1000 ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        prea[i][0] = max ( prea[i - 1][0] , a[i] ) ;
        preb[i][0] = max ( preb[i - 1][0] , b[i] ) ;
        prea[i][1] = min ( prea[i - 1][1] , a[i] ) ;
        preb[i][1] = min ( preb[i - 1][1] , b[i] ) ;
    }
    for ( int i = n ; i >= 1 ; -- i ) {
        sufa[i][0] = max ( sufa[i + 1][0] , a[i] ) ;
        sufb[i][0] = max ( sufb[i + 1][0] , b[i] ) ;
        sufa[i][1] = min ( sufa[i + 1][1] , a[i] ) ;
        sufb[i][1] = min ( sufb[i + 1][1] , b[i] ) ;
    }
    for ( int i = 0 ; i < n ; ++ i ) {
        if ( i <= n - 3 ) {
            printf ( "%d %d" , prea[n][0] , preb[n][0] ) ;
        } 
        else if ( i == n - 2 ) {
            getlcm () ;
        } 
        else {
            printf ( "%d %d" , prea[n][1] , preb[n][1] ) ;
        }
        printf ( " " ) ;
        if ( i == 0 ) {
            printf ( "%d %d" , prea[n][0] , preb[n][0] ) ;
        } 
        else if ( i == 1 ) {
            getgcd () ;
        } 
        else {
            printf ( "%d %d" , prea[n][1] , preb[n][1] ) ;
        }
        puts ( "" ) ;
    }
}
int main () {
    while ( ~scanf ( "%d" , &n ) )
        solve () ;
    return 0 ;
}

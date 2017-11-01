#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 105};
int a[N];
int x[N] , y[N];

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int m[n]; memset(m, 0, sizeof(m));
    for( int i = 0 ; i < k ; i++ ){
        scanf("%d", &a[i]);
    }
    for( int i = 0 ; i < n; i++ ){
        scanf("%d %d", &x[i], &y[i]);
    }
    for( int i = 0 ; i < n ; i++ ){
        for( int j = 0 ; j < k ; j++ ){
            if( a[j] <= y[i] && a[j] >= x[i] ){
                m[i]++;
            }
        }
    }
    for( int i = 0 ; i < n ; i++ ){
        printf("%d\n", m[i]);
    }
    return 0;
}

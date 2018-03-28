#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

int nxt(){
    int x;
    scanf("%d", &x);
    return x;
}
enum{ N = 321};
int a[N][N];

int main(){
    int n = nxt();
    for(int i = 0; i < (n); ++i) 
        for(int j = 0; j < (n); ++j) 
            a[i][j] = nxt();
    int ans = 0, curr_p = 0;
    for(int i = 0; i < (n); ++i){
        for(int j = 0; j < (n); ++j) 
            curr_p += a[i][j];
        for(int j = 0; j < (i); ++j) 
            curr_p -= a[j][i];
        ans = max(ans, curr_p);
    }
    for(int i = 0; i < (n); ++i){
        for(int j = 0; j < (n); ++j) 
            curr_p += a[i][j];
        for(int j = 0; j < (n); ++j) 
            curr_p -= a[j][i];
        ans = max(ans, curr_p);
    }
    printf("%d\n", ans);
    return 0;
}

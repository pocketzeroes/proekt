#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
    int n;
    scanf("%d", &n);
    int mx = 0;
    int mn = 101;
    int sm = 0;
    for(int i = 1 ; i <= n ; ++i){
        int x;
        scanf("%d", &x);
        sm += x;
        mx = max(mx, x);
        mn = min(mn, x);
    }
    sm -= (mx + mn);
    printf("%d\n", sm/(n - 2));
}

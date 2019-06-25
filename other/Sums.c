#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;

bool good(int x){
    if (x==1)
        return 0;
    if ((2*n)%x)
        return 0;
    int y=2*n/x;
    if (y%2==x%2)
        return 0;
    return 1;
}
int main(){
    int test;
    scanf("%d", &test);
    while(test--){
        scanf("%d", &n);
        int L=n+1;
        for(int x=1; x*x<=2*n; x++){
            if(good(x)){
                L=x;
                break;
            }
        }
        if(L<=n){
            int K=(2*n/L-L+1)/2;
            printf("%d = ", n);
            for(int i=0; i<L-1; i++)
                printf("%d + ", K+i);
            printf("%d\n", K+L-1);
        }
        else
            puts("IMPOSSIBLE");
    }
    return 0;
}

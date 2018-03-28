#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll n;
bool A[30];

void hey(ll aa){
    if(aa==n+1){
        ll ii,h=0;
        for(ii=1;ii<=n;ii++)
            if(A[ii])
                h++;
        if(!h)
            return ;
        printf("%lld", h);
        for(ii=1; ii<=n; ii++)
            if(A[ii])
                printf(" %lld", ii);
        puts("");
    }
    else{
        A[aa]=1;
        hey(aa+1);
        A[aa]=0;
        hey(aa+1);
    }
}
int main(){
    scanf("%lld", &n);
    printf("%lld\n", (1<<(n))-1);
    hey(1);
}

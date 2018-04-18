#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}

ll a, b, k;
int main(){
    scanf("%lld %lld %lld", &a, &b, &k);
    if(a!=b){
        ll t = min(abs(a-b), k);
        if(a<b)
            a+=t;
        else
            b+=t;
        k-=t;
    }
    a+=k/2;
    b+=k/2;
    a+=k&1;
    printf("%f\n", a*b/2.0);
}

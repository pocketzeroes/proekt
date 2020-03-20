#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll n, m, a, b;


void ex_gcd(ll a, ll b, ll*g, ll*x, ll*y){//puts(__FUNCTION__);
    if(b==0){
       *x = 1;
       *y = 0;
       *g = a;
       return;
    }
    ex_gcd(b, a%b, g, y, x);
   (*y) -= (*x) * (a/b);
}
void slove(){//puts(__FUNCTION__);
    ll x=0;
    ll y=0;
    ll g=0;
    ex_gcd(m, -n, &g, &x, &y);
    x = ( x*(a-b)/g %(-n /g ) - n/g )%(-n/g);
    printf("%lld %lld\n" , ((x * m + b)%(n*m)+ n*m )%(n*m) , n*m);
}
int main(){//puts(__FUNCTION__);
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%lld %lld %lld %lld", &a, &n, &b, &m);
        slove();
    }
    return 0;
}

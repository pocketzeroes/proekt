#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct F{
    ll d, x, y;
}F;
F newF(ll d, ll x, ll y){
    return(F){d,x,y};
}

F euclid(ll a, ll b){
    if (!b)
        return newF(a, 1, 0);
    F r = euclid(b, a%b);
    return newF(r.d, r.y, r.x-(a/b)*r.y);
}
ll gcd(ll a, ll b){
    if (!b)
        return a;
    return gcd(b, a%b);
}
ll lcm(ll a, ll b){
    return a*(b/gcd(a, b));
}
int main(){
    int n, p;
    scanf("%d", &p);
    for(int t=0; t<p; t++){
        scanf("%d", &n);
        ll a1, b1, a2, b2;
        scanf("%lld%lld", &a1, &b1);
        bool c=true;
        for(int i=1; i<n; i++){
            scanf("%lld%lld", &a2, &b2);
            if(i%2)
                b2=(a2-b2)%a2;
            if(c){
                F x = euclid(a1, -a2);
                if((b2-b1)%x.d!=0){
                    c=false;
                    continue;
                }
                ll l=a2/gcd(a1, a2),
                   h=((b2-b1)/x.d)%l;
                ll e, r=x.x*h%l;
                if(r<0){
                    e=abs(r)/l+1;
                    r+=e*l;
                }
                r%=l;
                b1+=a1*r;
                a1=lcm(a1, a2);
            }
        }
        if(!c)
            puts("impossible");
        else
            printf("%lld\n", b1);
    }
    return 0;
}

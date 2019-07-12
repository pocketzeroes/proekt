#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll A,B,C;
char ss[1000];

ll gcd(ll u, ll v){
  return v != 0LL ? gcd(v, u%v) : u;
}

int main(){
    ll i,j,k;
    ll p,q,r;
    ll X,Y;
    scanf("%s",ss);
    scanf("%lld",&C);
    j = strlen(ss);
    r = 0;
    k = 0;
    A = 0;
    B = 0;
    for(i=0;i<j;i++) {
        k += r;
        if(ss[i] == '.') r = 1;
        else {
            if(r == 0) {
                A *= 10;
                A += (ss[i] - '0');
            } 
            else if(r == 1) {
                B *= 10;
                B += (ss[i] - '0');
            }
        }
    }
    j = B;
    for(i=0,p=1;i<k;i++,p*=10);
    for(j=0,q=1;j<C;j++,q*=10);
    for(i=0,r=1;i<(k-C);i++,r*=10);
    Y = p - r;
    X = (A*p + B) - (A*r + B/q);
    k = gcd(X,Y);
    printf("%lld/%lld\n",X/k,Y/k);
    return 0;
}

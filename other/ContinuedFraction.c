#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int n,m,a1[20],a2[20];

ll gcd(ll x,ll y){
    return y?gcd(y,x%y):x;
}
void dfs(ll*A, ll*B, int*arr, int cur, int dep){
    if(cur == dep-1){
       *A = arr[cur];
       *B = 1;
    }
    if(cur >= dep-1)
        return;
    ll tmpA,tmpB;
    dfs(&tmpA, &tmpB, arr, cur+1, dep);
    *A = arr[cur]*tmpA + tmpB;
    *B = tmpA;
    ll theGCD = gcd(*A, *B);
    (*A) /= theGCD;
    (*B) /= theGCD;
}
void print(ll x, ll y){
    ll GCD = gcd(x,y);
    ll tmp = (x /= GCD)/(y /= GCD),p = x - tmp*y;
    printf("%lld%c", tmp, p?' ':'\n');
    if(p)
        print(y,p);
}
int main(){
    while(~scanf("%d %d",&n,&m)){
        for(int i = 0; i < n; ++i)
            scanf("%d",a1+i);
        for(int i = 0; i < m; ++i)
            scanf("%d",a2+i);
        ll A1 = 0,B1 = 1,A2 = 0,B2 = 1;
        dfs(&B1, &A1, a1, 1, n);
        dfs(&B2, &A2, a2, 1, m);
        A1 += a1[0]*B1;
        A2 += a2[0]*B2;
        print(A1*B2 + A2*B1, B1*B2);
        print(A1*B2 - A2*B1, B1*B2);
        print(A1*A2, B1*B2);
        print(A1*B2, A2*B1);
    }
    return 0;
}

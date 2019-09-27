#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int unique(ll*a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
}
enum{  MAXN =(int)6e5+5};
ll gc [MAXN];
ll a  [MAXN];
ll ans[MAXN];

ll gcd(ll a, ll b){
    while (b != 0){
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int main(){
    ll n;
    ll k=0,cot=0;
    scanf("%lld", &n);
    for(int i=0; i<n; i++)
        scanf("%lld", &a[i]);
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            ll x = gcd(a[i],gc[j]);
            if(x!=gc[j]){
                ans[cot++]=gc[j];
                gc[j]=x;
            }
        }
        gc[k++]=a[i];
        k = unique(gc, k);
    }
    for(int i=0;i<k;i++)
        ans[cot++]=gc[i];
    qsort(ans, cot, sizeof(ll), cmpLL);
    ll res= unique(ans, cot);
    printf("%lld\n", res);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll n;
ll*bit;
void BIT(ll n){
  bit=calloc(n+2, sizeof(ll));
}
void add(ll i, ll v){
  for(++i; i <= n+1; i += i & -i)
    bit[i] += v;
}
ll getSum(ll i){
  ll res = 0;
  for(; i; i -= i & -i)
    res += bit[i];
  return res;
}
ll same(ll*a, ll*b){
  ll ai[n];
  for(ll i=0; i<n; i++) ai[a[i]] = i;
  for(ll i=0; i<n; i++) b[i] = ai[b[i]];
  ll res = 0;
  BIT(n);
  for(ll i=0; i<n; i++)
    res += getSum(b[i]), add(b[i],1);
  free(bit);
  return res;
}
int main(){
  scanf("%lld", &n);
  ll a[n], b[n], c[n];
  for(ll i=0; i<n; i++) scanf("%lld", &a[i]), a[i]--;
  for(ll i=0; i<n; i++) scanf("%lld", &b[i]), b[i]--;
  for(ll i=0; i<n; i++) scanf("%lld", &c[i]), c[i]--;
  printf("%lld\n", (same(a,b)+same(a,c)+same(b,c)-n*(n-1)/2)/2 );
  return 0;
}

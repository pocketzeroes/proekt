#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll sum_of_floors(ll p, ll q, ll n){
  if(p == 0 || n == 0) 
    return 0;
  if(n >= q)
    return p*(n/q)*(n+1) - (n/q)*((n/q)*p*q + p + q - 1)/2 + sum_of_floors(p,q,n%q);
  if(p >= q)
    return (p/q)*n*(n+1)/2 + sum_of_floors(p%q,q,n);
  return (n*p/q) * n - sum_of_floors(q,p,n*p/q);
}
ll gcd(ll a, ll b){
  return b == 0 ? a : gcd(b, a % b);
}
int main(){
  int C; 
  scanf("%d", &C);
  while(C--){
    ll p, q, n;
    scanf("%lld %lld %lld", &p, &q, &n);
    ll g = gcd(p, q);
    printf("%lld\n", (p * n * (n+1) / 2) - q * sum_of_floors(p/g, q/g, n) );
  }
  return 0;
}

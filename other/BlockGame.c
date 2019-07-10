#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

bool canplayeronewin(ll n, ll m){
  if(m == 0)
    return false; 
  if(n >= 2*m)
    return true;
  return !(canplayeronewin(m, n-m));
}
int main(){
  ll m, n;
  scanf("%lld %lld", &n, &m);
  if(m > n){
    ll temp = n;
    n = m;
    m = temp;
  }
  if(canplayeronewin(n,m))
    puts("win");
  else
    puts("lose");
  return 0;
}

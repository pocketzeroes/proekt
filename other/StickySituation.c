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
int main(){
  int n;
  scanf("%d", &n);
  assert(n >= 3); 
  assert(n <= 20000);
  ll sticks[n];
  for(int i = 0; i < n; i++){
    scanf("%lld", &sticks[i]);
    assert(n > 0);
    assert(n < llround(pow(2, 60)));
  }
  qsort(sticks, n, sizeof(ll), cmpLL);
  bool possible = false;
  for(int i = 0; i < n-2; i++)
    if(sticks[i] + sticks[i+1] > sticks[i+2])
      possible = true;
  if(possible)
    puts("possible");
  else
    puts("impossible");
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

int main(){
  ll money = 100, days, prev = 1<<30, cur;
  scanf("%lld", &days);
  for (int i = 0; i < days; ++i, prev=cur){
    scanf("%lld", &cur);
    if(cur > prev)
      money += min(money/prev, 100000LL)*(cur-prev);
  }
  printf("%lld\n", money );
  return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll comb(ll count){
  return count * (count + 1) / 2;
}
int main(){
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  ll full = n - m * (k - 1);
  if(full < 0)
     full = 0;
  if(full % k != 0)
     full += k - full % k;
  ll best_total = 0;
  for(int l=0; l<m; ++l){
    if(full > n)
      break;
    ll total = 0;
    ll times = full / k;
    total += (times + 1) * full / 2;
    ll reminders = n - full;
    total += times * reminders;
    ll bigger = reminders % m;
    total += (reminders / m + 1) * comb(bigger);
    ll smaller = m - bigger;
    total += reminders / m * (bigger * smaller + comb(smaller));
    best_total = fmaxl(total, best_total);
    full += k;
  }
  printf("%lld\n", best_total);
  return 0;
}

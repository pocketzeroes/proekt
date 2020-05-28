#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;

void test_case(){
  ll L, R;
  scanf("%lld%lld", &L, &R);
  ll low = 0, high = 2e9;
  ll nxt = 1;
  if(L != R){
    while(low < high){
      ll mid = (low + high + 1) / 2;
      ll total = mid * (mid + 1) / 2;
      if(total <= llabs(L - R)){
        low = mid;
      }
      else{
        high = mid - 1;
      }
    }
    ll eaten = low * (low + 1) / 2;
    nxt = low + 1;
    if(L > R){
      L -= eaten;
      assert(L >= R);
      assert(L - nxt < R);
    }
    else{
      R -= eaten;
      assert(R >= L);
      assert(R - nxt < L);
    }
  }
//  debug() << " [" << "nxt" ": " << (nxt) << "] ";
  low = 0, high = 1e9 + 50;
  while(low < high){
    ll mid = (low + high + 1) / 2;
    ll one = mid * (nxt + nxt + 2 * (mid - 1)) / 2;
    ll two = one + mid;
    bool ok;
    if(L >= R){
      ok = (L >= one && R >= two);
    }
    else{
      ok = (R >= one && L >= two);
    }
    if(ok){
      low = mid;
    }
    else{
      high = mid - 1;
    }
  }
  ll mid = low;
  ll one = mid * (nxt + nxt + 2 * (mid - 1)) / 2;
  ll two = one + mid;
  if(L >= R){
    L -= one;
    R -= two;
  }
  else{
    L -= two;
    R -= one;
  }
  nxt += 2 * mid;
  assert(L >= 0 && R >= 0);
  if(L >= R && L >= nxt){
    L -= nxt;
    nxt++;
  }
  else if(R > L && R >= nxt){
    R -= nxt;
    nxt++;
  }
  assert(L < nxt && R < nxt);
//  debug() << " [" << "L" ": " << (L) << "] " " [" << "R" ": " << (R) << "] ";
  printf("%lld %lld %lld\n", nxt - 1, L, R);
}
int main(){
  int T;
  scanf("%d", &T);
  for(int nr = 1; nr <= T; ++nr){
    printf("Case #%d: ", nr);
    test_case();
  }
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;

inline int cnt(ll n, int k) {
  int ans = 0;
  while (n % k == 0) {
    n /= k;
    ++ans;
  }
  return ans;
}
int main(){
  char buff[50];
  scanf("%s", buff);
  ll a = atoi(buff);
  ll b = atoi(buff + 2);
  int l = strlen(buff + 2);
  for (int i = 1; i <= l; ++i) 
    a *= 10;
  b += a;
  int n2 = cnt(b, 2);
  int n5 = cnt(b, 5);
  ll n = 1;
  while (n2 < l) {
    n *= 2;
    n2++;
  }
  while (n5 < l) {
    n *= 5;
    n5++;
  }
  ll sum = n * b;
  for (int i = 1; i <= l; ++i) 
    sum /= 10;
  ll ret[6] = {0};
  for (int i = 5; i >= 2; --i) {
    ll k = (sum - n) / (i - 1);
    n -= k;
    ret[i] = k;
    sum -= k * i;
  }
  ret[1] = n;
  for (int i = 1; i <= 5; ++i)
    printf("%lld%c", ret[i], (i < 5) ? ' ' : '\n');
  return 0;
}

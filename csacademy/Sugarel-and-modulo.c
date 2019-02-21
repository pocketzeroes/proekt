#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main() {
  ll a, b, c, m;
  scanf("%lld%lld%lld", &a, &b, &m);
  b -= a;
  a %= m;
  if(a + b >= m)
    c = m - 1;
  else
    c = a + b;
  printf("%lld\n", c);
  return 0;
}

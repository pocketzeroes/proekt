#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int f[10];

bool isprime(int x){
  if (x < 2)
    return false;
  for (int r = 2; r*r <= x; ++r)
    if (x % r == 0)
      return false;
  return true;
}
int gen(int x){
  int ans = isprime(x);
  for (int i = !x; i < 10; ++i)
    if (f[i])
      --f[i], ans += gen(10*x + i), ++f[i];
  return ans;
}
void solve(){
  char digs[10];
  scanf("%s", digs);
  memset(f, 0, sizeof(f));
  for (char *p = digs; *p; ++p)
    ++f[*p-'0'];
  printf("%d\n", gen(0));
}
int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i)
    solve();
  return 0;
}

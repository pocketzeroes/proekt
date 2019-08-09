#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 50000};

int  uf[2*MAXN];
bool fz[2*MAXN];

void init(int n){
  for (int i = 0; i < 2*n; ++i){
    uf[i] = i;
    fz[i] = false;
  }
}
int find(int i) {
  return uf[i] == i ? i : (uf[i] = find(uf[i]));
}
bool merge(int i, int j) {
  i = find(i);
  j = find(j);
  if (fz[i] && fz[j])
    return false;
  fz[j] |= (fz[i] || i == j);
  uf[i] = j;
  return true;
}
bool solve(){
  int n;
  scanf("%d", &n);
  init(n);
  bool ok = true;
  while (n--) {
    int u, v;
    scanf("%d %d", &u, &v);
    ok &= merge(u-1, v-1);
  }
  return ok;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    puts(solve() ? "possible" : "impossible");
  return 0;
}

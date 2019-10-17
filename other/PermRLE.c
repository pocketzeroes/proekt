#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int  S, k;
int  best[16][1<<16];
char text[60000];
int  gain[100][100];
int  first;

int Gain(int x, int y){
#define g gain[x][y]
  if(g == -1){
    g = 0;
    for(int i=0; i+y < S; i += k)
      g += (text[i+x] == text[i+y]);
  }
  return g;
  #undef g
}
int Best(int x, int L){
  if (!L)
    return Gain(x, k+first);
#define res best[x][L]
  if (res == -1) {
    res = 0;
    for (int y = 0; y < k; ++y)
      if (L & (1<<y))
        res = fmax(res, Best(y, L & ~(1<<y)) + Gain(x, y));
  }
  return res;
  #undef res
}
void solve(int P){
  scanf("%d%s", &k, text);
  S = strlen(text);
  memset(gain, -1, sizeof(gain));
  int res = 0;
  for (first = 0; first < k; ++first) {
    memset(best, -1, sizeof(best));
    res = fmax(res, Best(first, (1<<k)-1-(1<<first)));
  }
  printf("Case #%d: %d\n", P, S - res);
  fprintf(stderr, "Case #%d: %d\n", P, S - res);
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i)
    solve(i);
  return 0;
}

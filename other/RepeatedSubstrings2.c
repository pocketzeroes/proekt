#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

const int low(int x) { return x&-x; }
const double eps = 1e-8;
const int INF    = 0x7FFFFFFF;
const int mod    = 1e8;
enum{ N =(int) 5e5 + 10};

const int read(){
  char ch = getchar();
  while (ch<'0' || ch>'9') ch = getchar();
  int x = ch - '0';
  while ((ch = getchar()) >= '0'&&ch <= '9') x = x * 10 + ch - '0';
  return x;
}
int T;

//struct Sa{
char s[N];
int rk[2][N], sa[N], h[N], w[N], now, n;
int rmq[N][20], lg[N];

bool GetS(){
  scanf("%s", s + 1);
  return true;
}
void getsa2(int z, int*m){
  int x = now,
      y = now ^= 1;
  for (int i = 1; i <= z; i++)
    rk[y][i] = n - i + 1;
  for (int i = 1, j = z; i <= n; i++)
    if (sa[i] > z)
      rk[y][++j] = sa[i] - z;
  for (int i = 1; i <= *m; i++)
    w[i] = 0;
  for (int i = 1; i <= n; i++)
    w[rk[x][rk[y][i]]]++;
  for (int i = 1; i <= *m; i++)
    w[i] += w[i - 1];
  for (int i = n; i >= 1; i--)
    sa[w[rk[x][rk[y][i]]]--] = rk[y][i];
  for (int i = *m = 1; i <= n; i++){
    int *a = rk[x] + sa[i], *b = rk[x] + sa[i - 1];
    rk[y][sa[i]] = *a == *b&&*(a + z) == *(b + z) ? *m - 1 : (*m)++;
  }
}
void getsa(int m){
  n = strlen(s + 1);
  rk[1][0] = now = sa[0] = s[0] = 0;
  for (int i = 1; i <= m; i++) w[i] = 0;
  for (int i = 1; i <= n; i++) w[s[i]]++;
  for (int i = 1; i <= m; i++) rk[1][i] = rk[1][i - 1] + (bool)w[i];
  for (int i = 1; i <= m; i++) w[i] += w[i - 1];
  for (int i = 1; i <= n; i++) rk[0][i] = rk[1][s[i]];
  for (int i = 1; i <= n; i++) sa[w[s[i]]--] = i;
  rk[1][n + 1] = rk[0][n + 1] = 0;
  for (int x = 1, y = rk[1][m]; x <= n && y <= n; x <<= 1)
    getsa2(x, &y);
  for (int i = 1, j = 0; i <= n; h[rk[now][i++]] = j ? j-- : j){
    if (rk[now][i] == 1) continue;
    int k = n - fmax(sa[rk[now][i] - 1], i);
    while (j <= k && s[sa[rk[now][i] - 1] + j] == s[i + j]) ++j;
  }
}
void getrmq(){
  h[n + 1] = h[1] = lg[1] = 0;
  for (int i = 2; i <= n; i++)
    rmq[i][0] = h[i], lg[i] = lg[i >> 1] + 1;
  for (int i = 1; (1 << i) <= n; i++){
    for (int j = 2; j <= n; j++){
      if (j + (1 << i) > n + 1) 
        break;
      rmq[j][i] = fmin(rmq[j][i - 1], rmq[j + (1 << i - 1)][i - 1]);
    }
  }
}
int lcp(int x, int y){
  int l = fmin(rk[now][x], rk[now][y]) + 1, r = fmax(rk[now][x], rk[now][y]);
  return fmin(rmq[l][lg[r - l + 1]], rmq[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);
}
void work(){
  GetS();
  getsa(256);
  int ans = 0;
  for (int i = 2; i <= n; i++)
    ans += fmax(0, h[i] - h[i - 1]);
  printf("%d\n", ans);
}
//}sa;

int main(){
  T = read();
  while (T--)
    work();
  return 0;
}

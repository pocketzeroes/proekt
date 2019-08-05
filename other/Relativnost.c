#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAXN = 100005};
enum{ MAXC = 21    };
enum{ mod = 10007  };

int n, c, q;
int a[MAXN];
int b[MAXN];
int T[2 * MAXN][MAXC];

void update(int x){
  for (int i = 0; i <= c; ++i)
    T[x][i] = 0;
  for (int i = 0; i <= c; ++i)
    for (int j = 0; j <= c; ++j)
      T[x][min(i + j, c)] += (T[x * 2][i] * T[x * 2 + 1][j]) % mod;
  for(int i = 0; i <= c; ++i)
    T[x][i] %= mod;
}
void change(int x){
  x += n;
  memset(T[x], 0, sizeof T[x]);
  T[x][1] = a[x - n] % mod;
  T[x][0] = b[x - n] % mod;
  for (x /= 2; x > 0; x /= 2) 
    update(x);
}
int main(void) {
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  for (int i = 0; i < n; ++i){
    T[i + n][0] = b[i] % mod;
    T[i + n][1] = a[i] % mod;
  }
  for (int i = n-1; i >= 1; --i)
    update(i);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int p;
    scanf("%d", &p); --p;
    scanf("%d%d", &a[p], &b[p]); 
    change(p);
    printf("%d\n", T[1][c]);
  }
  return 0;
}

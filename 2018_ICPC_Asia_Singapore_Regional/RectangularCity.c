#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MOD =(int) 1e9 + 7};
int n, r, c, k;
int ways[5005];
int rows[5005],
    cols[5005];

int modPow(int base, int po){
  int ret = 1;
  while (po){
    if (po & 1)
      ret = 1ll * ret * base % MOD;
    po >>= 1;
    base = 1ll * base * base % MOD;
  }
  return ret;
}
int calc(int atas, int bawah, int kiri, int kanan){
  int w1 = ways[atas] - ways[atas-1];
  int w2 = ways[r-bawah+1] - ways[r-bawah];
  int w3 = ways[kiri] - ways[kiri-1];
  int w4 = ways[c-kanan+1] - ways[c-kanan];
  int ret = 1ll * w1 * w2 % MOD;
  ret = 1ll * ret * w3 % MOD;
  ret = 1ll * ret * w4 % MOD;
  ret = (ret + MOD) % MOD;
  return ret;
}
int calcSimple(int a, int b){
  int w1 = ways[a] - ways[a-1];
  int w2 = ways[b] - ways[b-1];
  int ret = 1ll * w1 * w2 % MOD;
  ret = (ret + MOD) % MOD;
  return ret;
}
int main(){
  scanf("%d%d%d%d", &n, &r, &c, &k);
  for (int i = 0; i < 5005; i++)
    ways[i] = modPow(i, n);
  for (int i = 1 ; i <= r ; i++)
    for (int j = i ; j <= r ; j++)
      rows[j - i + 1] = (rows[j - i + 1] + calcSimple(i, r - j + 1)) % MOD;
  for (int i = 1; i <= c; i++)
    for (int j = i ; j <= c; j++)
      cols[j - i + 1] = (cols[j - i + 1] + calcSimple(i, c - j + 1)) % MOD;
  int ret = 0;
  for (int i = 1 ; i <= r ; i++)
    for (int j = 1 ; j <= c ; j++)
      if (i * j >= k)
        ret = (ret + 1ll * rows[i] * cols[j]) % MOD;
  printf("%d\n", ret);
  return 0;
}

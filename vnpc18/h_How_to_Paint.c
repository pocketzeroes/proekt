#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpR(const void *b, const void *a){
  return ( *(int*)a - *(int*)b );
}

enum{ mod  = 100003};
enum{ maxn = 1005};
typedef long long ll;
ll numerator   = 1, 
   denominator = 1, 
   base        = 0;
int m, n;
int*a;
int*b;
bool filled[maxn][maxn];
int ups[maxn][maxn], rights[maxn][maxn];

void update_hook(int*w){
  memset(filled, false, sizeof filled);
  for (int i = 0; i < m; i++){
    for (int j = 0; j < w[i]; j++){
      filled[i][j] = true;
    }
  }
  memset(ups,    0, sizeof ups);
  memset(rights, 0, sizeof rights);
  for (int i = m - 1; i >= 0; i--){
    for (int j = n - 1; j >= 0; j--){
      if (filled[i][j]){
        ups   [i][j] = (filled[i + 1][j]) ? (1 + ups   [i + 1][j]) : 1;
        rights[i][j] = (filled[i][j + 1]) ? (1 + rights[i][j + 1]) : 1;
        int hook = ups[i][j] + rights[i][j] - 1;
        denominator *= hook;
        denominator %= mod;
      }
    }
  }
}
void multiply(int x){
  while (x % mod == 0){
    base++;
    x /= mod;
  }
  numerator *= x;
  numerator %= mod;
}
int main(){
  scanf("%d %d", &m, &n);
  a=calloc(m, sizeof(int));
  b=calloc(m, sizeof(int));
  int p = 0, 
      q = 0;
  for (int i = 0; i < m; i++){
    scanf("%d", &a[i]);
    b[i] = n - a[i];
    p += a[i];
    q += b[i];
  }
  qsort(b, m, sizeof(int), cmpR);
  update_hook(a);
  update_hook(b);
  for(int i=1; i<=p+q-2; i++)
    multiply(i);
  multiply(p);
  multiply(q);
  for(int i=0; i<mod-2; i++){
    numerator *= denominator;
    numerator %= mod;
  }
  printf("%lld %lld\n", base, numerator);
  return 0;
}

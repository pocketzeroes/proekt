#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char kattis  [100000][16];
char domjudge[100000][16];

int main(){
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%s", kattis[i]);
  for (int i = 0; i < n; ++i)
    scanf("%s", domjudge[i]);
  qsort(kattis  , n, sizeof(kattis[0]), (int (*)(const void*,const void*))&strcmp);
  qsort(domjudge, n, sizeof(kattis[0]), (int (*)(const void*,const void*))&strcmp);
  int res = 0;
  int k, d;
  for (k = d = 0; k < n && d < n; ){
    int cmpres = strcmp(kattis[k], domjudge[d]);
    if (cmpres == 0) ++res;
    if (cmpres <= 0) ++k;
    if (cmpres >= 0) ++d;
  }
  printf("%d\n", res);
  return 0;
}

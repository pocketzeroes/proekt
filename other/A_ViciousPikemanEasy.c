#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int comp(const void *p, const void *q) {
  int *a = (int *) p;
  int *b = (int *) q;
  return *a - *b;
}
int main(){
  long n, t, a, b, c, p, s, i, t_p;
  long ti[10000];
  scanf("%ld %ld %ld %ld %ld %ld", &n, &t, &a, &b, &c, &ti[0]);
  for (i = 1; i < n; i++)
    ti[i] = (a * ti[i-1] + b) % c + 1;
  qsort(ti, n, sizeof(long), comp);
  p = 0;
  s = 0;
  t_p = 0;
  for (i = 0; i < n; i++) {
    if (t_p + ti[i] <= t) {
      p = (p + ti[i] + t_p) % 1000000007;
      t_p += ti[i];
      s++;
    }
    else {
      break;
    }
  }
  printf("%ld %ld\n", s, p);
  return 0;
}

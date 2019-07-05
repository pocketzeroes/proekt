#include<stdio.h>
#include<stdlib.h>

int main(){
  int C, L;
  scanf("%d %d", &C, &L);
  int *p = malloc((C + 1) * sizeof(*p)),
      *n = malloc(C * sizeof(*n)),
      *q = malloc(C * sizeof(*q)),
      *r = malloc(C * sizeof(*r)),
      *e = malloc(2 * L * sizeof(*e)),
      *f = malloc(2 * L * sizeof(*f));
  for (int i = 0; i < C; i++)
    n[i] = 0;
  for (int i = 0; i < 2 * L; i++){
    scanf("%d", e + i);
    n[e[i]]++;
  }
  for (int i = 0, c = 0; i < C; i++)
    p[i] = c += n[i];
  p[C] = p[C - 1];
  for (int i = 0; i < L; i++){
    int u = e[2 * i], 
        v = e[2 * i + 1];
    f[--p[u]] = v;
    f[--p[v]] = u;
  }
  int x = -2, y = -2, z = -2, c = 0;
  for (int i = 0; i < C; i++){
    if (!n[i]){
      z = y; y = x; x = 0;
    }
    if (n[i] == 1){
      r[i] = c;
      q[c++] = i;
    }
  }
  for (int h = 1, d = 0; d < c; h++){
    for (int b = c; d < b; d++){
      n[q[d]] = -1;
      for (int i = p[q[d]]; i < p[q[d] + 1]; i++){
        int g = f[i];
        if (--n[g] == 1){
          r[g] = c;
          q[c++] = g;
        }
        else if (n[g] == 0){
          z = y; y = x; x = 2 * h - (r[g] < b ? 1 : 0);
        }
      }
    }
  }
  int m = (x + 1) / 2 + 1 + (y + 1) / 2;
  if (m > x)
    x = m;
  m = (y + 1) / 2 + 2 + (z + 1) / 2;
  if (m > x)
    x = m;
  printf("%d\n", x);
  return 0;
}
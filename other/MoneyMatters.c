#include<stdio.h>
#include<stdlib.h>

int *p, *o, *r;

int find(int i){
  if (p[i] == i)
    return i;
  return p[i] = find(p[i]);
}
void link(int i, int j){
  if (r[i] < r[j])
    link(j, i);
  else if (i != j) {
    p[j] = i;
    o[i] += o[j];
    if (r[i] == r[j])
      ++r[i];
  }
}
int main(){
  int i, n, m, x, y, ok=1;  
  scanf("%d%d", &n, &m);
  p = calloc(n, sizeof(int));
  o = calloc(n, sizeof(int));
  r = calloc(n, sizeof(int));
  for (i = 0; i < n; ++i)
    p[i] = i;
  for (i = 0; i < n; ++i)
    scanf("%d", o+i);
  while (m-->0) {
    scanf("%d%d", &x, &y);
    link(find(x), find(y));
  }
  for (i = 0; ok && i < n; ++i)
    ok = !(p[i] == i && o[i]);
  return !printf("%sPOSSIBLE\n", ok ? "" : "IM");
}

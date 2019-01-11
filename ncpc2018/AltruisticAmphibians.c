#include <stdio.h>
#include <stdlib.h>
#define MAXW (100000001)
#define MAXF (100000)
#define MIN(a,b) ((a)<(b)?(a):(b))

int T[MAXW];
int d, n;

typedef struct{
  int l, w, h;
}frog;
frog frogs[MAXF];

int cmp(const void *a, const void *b){
  int ia = ((frog*)a)->w;
  int ib = ((frog*)b)->w;
  return ib-ia;
}
int main(){
  int i, j;
  int esc = 0;
  int sw = 0;
  scanf("%d %d", &n, &d);
  for (i = 0; i < n; i++){
    scanf("%d %d %d", &frogs[i].l, &frogs[i].w, &frogs[i].h);
    sw += frogs[i].w;
  }
  for (i = 0; i < sw; i++)
    T[i] = 0;
  qsort(frogs, n, sizeof(frog), cmp);
  for (i = 0; i < n; i++) {
    if (T[frogs[i].w] + frogs[i].l > d)
      esc++;
    for (j = frogs[i].w; j < 2*frogs[i].w && j < MAXW; j++) {
      int val = T[j] + frogs[i].h;
      if (val > T[j-frogs[i].w]) {
        T[j-frogs[i].w] = MIN(d, val);
      }
    }
  } 
  printf("%d\n",esc);
  return 0;
}

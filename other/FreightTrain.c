#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

int N, W, L;
int wag[123456];

bool mag(int T){
  int nT = 1; 
  int bT = 1;
  if (wag[0] > T) {
    nT = 2;
    bT = wag[0];
  }
  for (int i = 0; i < W; i++) {
    if (wag[i] >= bT + 2*T) {
      nT += 2;
      bT = wag[i];
    }
    else if (wag[i] >= bT + T) {
      nT++;
      bT += T;
    }
  }
  if (N >= bT + T)
    nT++;
  return (nT > L);
}
void doit(){
  scanf("%d %d %d", &N, &W, &L);
  for(int i = 0; i < W; i++)
    scanf("%d", &wag[i]);
  qsort(wag, W, sizeof(int), cmp);
  int lo = -1;
  int hi = N;
  while (hi - lo > 1){
    int mid = (lo+hi)/2;
    if(mag(mid))
      lo=mid;
    else
      hi=mid;
  }
  printf("%d\n", lo+1);
}
int main (){
  int T;
  scanf("%d", &T);
  for(int t = 1; t <= T; t++)
    doit();
  return 0;
}

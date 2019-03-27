#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void*b, const void*a){//rev
  return ( *(int*)a - *(int*)b );
}
int main(){
  int N;
  scanf("%d", &N);
  int ps[N];
  for(int i=0; i<N; i++){
    scanf("%d", &ps[i]);
  }
  qsort(ps, N, sizeof(int), cmp);//rev
  int aans = 0, 
      bans = 0;
  for(int i=0; i<N; i++){
    if(i % 2 == 0)
      aans += ps[i];
    else
      bans += ps[i];
  }
  printf("%d %d\n", aans, bans);
  return 0;
}

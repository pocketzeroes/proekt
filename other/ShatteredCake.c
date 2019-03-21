#include<stdio.h>
int W;
int L;
long N;
long A;

int main(){
  scanf("%d %d", &W, &N);
  A = 0;
  for(int i=0; i<N; i++){
    int w,l;
    scanf("%d %d", &w, &l);
    A += w*l;
  }
  L = A/W;
  printf("%d\n", L);
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double eps1 = 1.23e-7;
double eps2 = 4.56e-7;

typedef struct{
  int idx;
  double x,y,angle;
}pt;
int cmpPt(const void*pa, const void*pb){
  pt*a=(pt*)pa;
  pt*b=(pt*)pb;
  return(a->angle < b->angle)?-1:1;
}
int main(){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    int N;
    scanf("%d", &N);
    pt p[N];
    double cx=0.,cy=0.;
    for(int i=0; i<N; i++){
      p[i].idx=i;
      scanf("%lf%lf", &p[i].x, &p[i].y);
      cx+=p[i].x/N;
      cy+=p[i].y/N;
    }
    for(int i=0; i<N; i++)
      p[i].angle = atan2(p[i].y-cy+eps1 , p[i].x-cx+eps2);
    qsort(p, N, sizeof(pt), cmpPt);
    for(int i=0; i<N; i++){
      if(i)
        printf(" ");
      printf("%d", p[i].idx);
    }
    puts("");
  }
  return 0;
}

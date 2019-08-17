#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
  int nC = in_nextInt();
  for (int loop=0; loop<nC; loop++) {
    int r = in_nextInt();
    int n = in_nextInt()%(360*3600);
    int deg = 3600*in_nextInt();
    deg += 60*in_nextInt();
    deg += in_nextInt();
    int vals[n]; memset(vals, 0, sizeof(vals));
    for(int i=1; i<n; i++)
      vals[i] = (vals[i-1]+deg)%(360*3600);
    qsort(vals, n, sizeof(int), cmp);
    int best = 360*3600 + vals[0] - vals[n-1];
    for(int i=1; i<n; i++)
      best = fmax(best, vals[i]-vals[i-1]);
    printf("%.6f\n", M_PI*r*r*best/(360.*3600.));
  }
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int t[17][1<<17];
int main(){
  int N;
  scanf("%d", &N);
  for(int c=1;c<=N;c++){
    int n,k,x[30],y[30];
    scanf("%d %d", &n, &k);
    for (int i=0; i<(int)(n); i++)
      scanf("%d %d", &x[i], &y[i]);
    for (int take=0; take<(int)(1<<n); take++)
      if(take){
        int minx=1000000,maxx=-1,miny=1000000,maxy=-1;
        for (int i=0; i<n; i++)
          if(take&1<<i){
            minx = fmin(minx, x[i]);
            maxx = fmax(maxx, x[i]);
            miny = fmin(miny, y[i]);
            maxy = fmax(maxy, y[i]);
          }
        t[1][take] = fmax((maxx-minx), (maxy-miny));
      }
    for(int kk=2;kk<=k;kk++){
      for(int take=0; take<(1<<n); take++){
        t[kk][take] = t[kk-1][take];
        for(int take2=take; take2; take2=(take2-1)&take)
          t[kk][take] = fmin(t[kk][take], fmax(t[kk-1][take-take2], t[1][take2]));
      }
    }
    printf("Case #%d: %d\n", c, t[k][(1<<n)-1]);
  }
  return 0;
}

#include <stdio.h>

enum{  MAXH = 1000};
enum{  MAXC = MAXH};
double HUGE = 1e16;
double dyn [MAXH][MAXC];
double cost[MAXH][MAXH];
int    pos [MAXH];
int    t;

int main(){
  int i, j, k, H, C;
  scanf("%d",&t);
  while(t--){
    scanf("%d %d", &H, &C);
    for(i=0; i<H; i++)
      scanf("%d", &pos[i]);
    for(i=0; i<H; i++)
      for(j=i+1; j<H; j++){
        double dx  = j-i;
        double dy  = pos[j]-pos[i];
        double sum = 0;
        for (k=i+1;k<j;k++){
          double tmp = (double)pos[k]-dy*(k-i)/dx-pos[i];
          if(tmp<0)
             tmp = -tmp;
          sum += tmp;
        }
        cost[i][j] = sum;
      }
    for(i=0; i<C; i++)
      for(j=0; j<H; j++)
        dyn[j][i] = HUGE;
    dyn[0][0] = 0;
    for(i=1; i<H; i++)
      for(j=1; j<C; j++){
        for(k=0; k<i; k++)
          if(cost[k][i]+dyn[k][j-1]<dyn[i][j])
             dyn[i][j]=cost[k][i]+dyn[k][j-1];
      }
    printf("%.4lf\n", dyn[H-1][C-1]/H);
  }
  return 0;
}

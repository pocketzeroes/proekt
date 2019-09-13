#include<stdlib.h>
#include<stdio.h>
#include<string.h>
enum{ MAX_SIZE = 100};
int main(){
  int n, x, y, histx[MAX_SIZE], histy[MAX_SIZE], pop, totpop, cumpop, xloc, yloc, dist;
  scanf("%d", &n);
  while (n--){
    scanf("%d %d", &x, &y);
    memset(histx, 0, x*sizeof(int));
    memset(histy, 0, y*sizeof(int));
    totpop = 0;
    for (int i=0; i<y; i++){
      for (int j=0; j<x; j++){
        scanf("%d", &pop);
        histx[j] += pop;
        histy[i] += pop;
        totpop += pop;
      }
    }
    cumpop = 0;
    for (int i=0; i<x; i++){
      cumpop += histx[i];
      if ((totpop+1) / 2 <= cumpop){
        xloc = i;
        break;
      }
    }
    cumpop = 0;
    for (int i=0; i<y; i++){
      cumpop += histy[i];
      if ((totpop+1) / 2 <= cumpop){
        yloc = i;
        break;
      }
    }
    dist = 0;
    for (int i=0; i<x; i++)
      dist += abs(i-xloc) * histx[i];
    for (int i=0; i<y; i++)
      dist += abs(i-yloc) * histy[i];
    printf("%d blocks\n", dist);
  }
  return 0;
}

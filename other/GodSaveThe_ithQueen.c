#include <stdio.h>
#include <string.h>
enum{ MAX_X = 20000};
int main(){
  int N, X, Y;
  int sloupec[MAX_X], radek[MAX_X];
  int leva_diagonala[2*MAX_X], prava_diagonala[2*MAX_X];
  int n, x, y, pocet;
  while (1){
    scanf("%d %d %d", &X, &Y, &N);
    if(!N && !X && !Y)  return 0;
    memset(sloupec, 0, sizeof(sloupec));
    memset(radek, 0, sizeof(radek));
    memset(leva_diagonala, 0, sizeof(leva_diagonala));
    memset(prava_diagonala, 0, sizeof(prava_diagonala));
    for(n=0; n<N; n++) {
      scanf("%d %d", &x, &y);
      x--, y--;
      sloupec[x]=1;
      radek[y]=1;
      prava_diagonala[ x-y  +(Y-1) ]=1;
      leva_diagonala[ x+y ]=1;
    }
    pocet = 0;
    for(x=0; x<X; x++)
     for(y=0; y<Y; y++)
      pocet += sloupec[x] | radek[y] | prava_diagonala[ x-y +(Y-1)] | leva_diagonala[ x+y ] ;
    printf("%d\n", X*Y - pocet);
  }
  return 0;
}

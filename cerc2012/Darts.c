#include<stdio.h>

int main(){
  int TT,n;
  scanf("%d",&TT);
  while(TT--){
    int score = 0;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
      int x,y;
      scanf("%d %d", &x, &y);
      for(int i=1; i<=10; i++){
        if (x*x+y*y<=400*i*i){
          score += 11-i;
          break;
        }
      }
    }
    printf("%d\n", score);
  }
  return 0;
}

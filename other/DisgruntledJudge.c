#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ M = 10001};

int main (){
  int N;
  scanf("%d", &N);
  int x[N];
  for(int i=0; i<N; i++)
    scanf("%d", &x[i]);
  for(int a=0; a<M; a++){
    for(int b=0; b<M; b++){
      int y=x[0], ok=1;
      for(int i=0; i<N && ok; i++){
        if(y!=x[i]){
          ok=0;
          break;
        }
        y = (a*y+b)%M;
        y = (a*y+b)%M;
      }
      if(ok){
        for(int i=0; i<N; i++)
          printf("%d\n", (a*x[i]+b)%M);
        return 0;
      }
    }
  }
  return 1;
}

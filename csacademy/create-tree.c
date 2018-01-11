#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int N;
  scanf("%d", &N);
  for(int u=1,v=1+N/2; u<1+N/2&&v<=N; ++u,++v){
    printf("Q %d %d\n", u, v); fflush(stdout);
    int x;
    scanf("%d", &x);
    if(x == 0){
      --u;
      --v;
    }
  }
  puts("A"); fflush(stdout);
  return 0;
}



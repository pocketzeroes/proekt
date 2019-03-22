#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool solve(){
  int N, M;
  scanf("%d %d", &N, &M);
  if(N == -1 && M == -1)
    return false;
  if(M == N){
    puts("YES");
    for(int i=1; i<=N; i++)
      printf("%d %d\n", i , (i==N?1: i+1) );
  }
  else if (M == N*(N-1)/2){
    puts("YES");
    for(int i=1;i<=N;i++)
      for(int j=i+1;j<=N;j++)
        printf("%d %d\n", i, j);
  }
  else if (N%2==0 && M==(N/2)*(N/2)){
    puts("YES");
    for (int i=1;i<=N/2;i++)
      for(int j=N/2+1;j<=N;j++)
        printf("%d %d\n", i, j);
  }
  else
    puts("NO");
  return true;
}
int main(){
  while(solve());
  return 0;
}

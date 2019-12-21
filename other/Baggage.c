#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void doit2(int N, int add){
  if     (N == 4){
    printf("%d to %d\n", 6+add , -1+add );
    printf("%d to %d\n", 3+add ,  6+add );
    printf("%d to %d\n", 0+add ,  3+add );
    printf("%d to %d\n", 7+add ,  0+add );
  }
  else if(N == 5){
    printf("%d to %d\n", 8+add , -1+add );
    printf("%d to %d\n", 3+add ,  8+add );
    printf("%d to %d\n", 6+add ,  3+add );
    printf("%d to %d\n", 0+add ,  6+add );
    printf("%d to %d\n", 9+add ,  0+add );
  }
  else if(N == 6){
    printf("%d to %d\n", 10+add , -1+add );
    printf("%d to %d\n",  7+add , 10+add );
    printf("%d to %d\n",  2+add ,  7+add );
    printf("%d to %d\n",  6+add ,  2+add );
    printf("%d to %d\n",  0+add ,  6+add );
    printf("%d to %d\n", 11+add ,  0+add );
  }
  else if(N == 7){
    printf("%d to %d\n",  8+add , -1+add );
    printf("%d to %d\n",  5+add ,  8+add );
    printf("%d to %d\n", 12+add ,  5+add );
    printf("%d to %d\n",  3+add , 12+add );
    printf("%d to %d\n",  9+add ,  3+add );
    printf("%d to %d\n",  0+add ,  9+add );
    printf("%d to %d\n", 13+add ,  0+add );
  }
  else{
    printf("%d to %d\n", 2*N-2+add , -1+add);
    printf("%d to %d\n", 3+add , 2*N-2+add ); doit2(N-4, 4+add);
    printf("%d to %d\n", 0+add , 2*N-5+add );
    printf("%d to %d\n", 2*N-1+add , 0+add );
  }
}
int main(){
  int N;
  while(scanf("%d", &N)==1){
    if(N == 3){
      puts("2 to -1");
      puts("5 to 2" );
      puts("3 to -3");
    }
    else
      doit2(N, 0);
  }
  return 0;
}

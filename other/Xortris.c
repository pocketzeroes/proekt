#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


bool solve1(__int128 board, int n){
  if(n<=3)
    return board==0;
  if(board&1)
    return solve1((board^0xf)>>1,n-1);
  return solve1(board>>1,n-1);
}
bool solve1s(char*board){
  int n = strlen(board);
  __int128 boardint=0;
  for(int z=0; z<n; z++){char c=board[z];
    boardint<<=1;
    if(c=='X')
      boardint|=1;
  }
  return solve1(boardint, n);
}
bool solve(){
  int m, n;
  scanf("%d %d", &m, &n);
  char*board;
  if(m==1){
    board = getstr();
    return solve1s(board);
  }
  else if(n==1){
    board = calloc(m+1, sizeof(char));
    for(int i=0; i<m; ++i){getchar();
      board[i] = getchar();
    }
    return solve1s(board);
  }
  else{
    int count=0;
    getchar();
    for(int i=0; i<m; ++i){
      for(int j=0; j<n; ++j){
        char c=getchar();
        count += (c=='X'?1:0);
      }
      getchar();
    }
    if(n==2 && m==2)
      return!(count&3);
    return!(count&1);
  }
}
int main() {
  puts(solve()?"possible":"impossible");
  return 0;
}

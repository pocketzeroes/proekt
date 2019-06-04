#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

const int dx[4] = {2,2,-2,-2};
const int dy[4] = {2,-2,2,-2};

enum{ bsize=10};

char*board[bsize+1];

int go(int x, int y){
  int m = 0;
  for(int q=0; q<4; q++){
    if (x+dx[q]<0 || x+dx[q]>=bsize || y+dy[q]<0 || y+dy[q]>=bsize)
      continue;
    if (board[x+dx[q]/2][y+dy[q]/2]=='B' && board[x+dx[q]][y+dy[q]]=='#'){
      board[x][y] = '#';
      board[x+dx[q]/2][y+dy[q]/2]='#';
      board[x+dx[q]][y+dy[q]]='W';
      m = max(m,1+go(x+dx[q],y+dy[q]));
      board[x][y] = 'W';
      board[x+dx[q]/2][y+dy[q]/2]='B';
      board[x+dx[q]][y+dy[q]]='#';
    }
  }
  return m;
}
int main(){
  int TT;
  scanf("%d", &TT);
  getchar();
  while(TT--){
    getchar();
    for(int i=0; i<bsize; i++){
      board[i]=getstr();
    }
    int m = 0;
    for(int i=0; i<bsize; i++)
      for(int j=0; j<bsize; j++)
        if (board[i][j]=='W')
          m = max(m, go(i,j));
    printf("%d\n", m);
  }
  return 0;
}

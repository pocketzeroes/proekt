#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX_R = 50000};
char*grid[MAX_R];

int main(){
  int R,C;
  scanf("%d %d", &R, &C);
  getchar();
  for(int i=0; i<R; i++){
    grid[i] = calloc(C, sizeof(char));
    for(int j=0; j<C; j++)
      grid[i][j]=getchar();
    getchar();
  }
  for(int c=0; c<C; c++){
    int open = -1;
    for(int r=R-1; r>=0; r--){
      if(grid[r][c] == '#')
        open = -1;
      else if (open == -1 && grid[r][c] == '.')
        open = r;
      else if(open != -1 && grid[r][c] == 'a'){
        grid[open][c] = 'a';
        grid[r][c] = '.';
        open--;
      }
    }
  }
  for(int j=0; j < R; j++){
    for(int c=0; c < C; c++)
      putchar(grid[j][c]);
    puts("");
  }
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define WALL_PROB      0.05
#define MAX_ATTEMPTS 500
#define RAND_SEED     42

enum{ N = 300};
bool wall[N][N];

char moves[100000];
int main(){
  scanf("%s", &moves);
  srand(RAND_SEED);
  int attempts = MAX_ATTEMPTS;
  while(attempts--){
    int count = 0;
    for(int x = 0; x < N; x++){
      for(int y = 0; y < N; y++){
        wall[x][y] = min(x,y) == 0 || max(x,y) == N-1 || (double)(rand())/RAND_MAX < (double)(WALL_PROB);
        count += wall[x][y];
      }
    }
    int sx = 0,
        sy = 0;
    while(wall[sx][sy])
      sx = rand() % N,
      sy = rand() % N;
    bool ok = true;
    int x = sx,
        y = sy;
    for(int i=0;moves[i];i++){char c = moves[i];
      int dx = (c == 'R') - (c == 'L');
      int dy = (c == 'U') - (c == 'D');
      if(wall[x+dx][y+dy])
        ok = false;
      while(!wall[x+dx][y+dy])
        x += dx,
        y += dy;
    }
    int tx = x,
        ty = y;
    x = sx,
    y = sy;
    for(int i=0;moves[i];i++){char c = moves[i];
      int dx = (c == 'R') - (c == 'L');
      int dy = (c == 'U') - (c == 'D');
      while (!wall[x+dx][y+dy]){
        if (x == tx && y == ty)
          ok = false;
        x += dx,
        y += dy;
      }
    }
    if (ok){
      printf("%d %d\n", sx-tx, sy-ty);
      printf("%d\n", count);
      for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
          if (wall[x][y])
            printf("%d %d\n", x-tx, y-ty);
        }
      }
      return 0;
    }
  }
  puts("impossible");
  return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int W, H;
char maze[200][200];

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

bool sensetraps(int r, int c){ 
  return maze[r-1][c] == 'T' || maze[r+1][c] == 'T' || maze[r][c-1] == 'T' || maze[r][c+1] == 'T'; 
}
int main(){
  scanf("%d %d", &W, &H);
  int gold = 0;
  for (int i = 0; i < H; ++i) 
    scanf("%s", maze[i]);
  bool changing = true;
  while (changing){
    changing = false;
    for (int r = 0; r < H; ++r)
      for (int c = 0; c < W; ++c)
        if (maze[r][c] == 'P' && !sensetraps(r, c)){
          for (int d = 0; d < 4; ++d){
            int nr = r + dr[d], nc = c + dc[d];
            changing |= maze[nr][nc] != '#' && maze[nr][nc] != 'P'; 
            gold += maze[nr][nc] == 'G';
            if (maze[nr][nc] != '#') 
              maze[nr][nc] = 'P';
          }
        }
  }
  printf("%d\n", gold);
  return 0;
}

#include <stdio.h>

const int errorDistance = 0x3fffffff;
int w,h;
int map[101][101];

typedef struct{
  int x,y,d;
}entry;
entry q[10201];
int qf, qb;

void ResetMap(){
  for(int y = 0; y < h; ++y)
    for(int x = 0; x < w; ++x)
      map[y][x] = -1;
}
int FindPath(int x1, int y1, int x2, int y2){
  qf = 0;
  q[0] = (entry){x1, y1, 0};
  qb = 1;
  map[y1][x1] = 0;
  int dx[] = { -1, 0, 1, 0 };
  int dy[] = { 0, -1, 0, 1 };
  while(qf != qb){
    entry e = q[qf++];
    if(e.x == x2 && e.y == y2){
      for(int i; e.x != x1 || e.y != y1; e.x -= dx[i], e.y -= dy[i]){
        i = map[e.y][e.x];
        map[e.y][e.x] = -2;
      }
      map[y1][x1] = -2;
      for(int y = 0; y < h; ++y){
        for(int x = 0; x < w; ++x){
          if(map[y][x] >= 0)
            map[y][x] = -1;
        }
      }
      return e.d;
    }
    for(int i = 0; i < 4; ++i){
      int x = e.x+dx[i];
      int y = e.y+dy[i];
      if(x < 0 || x >= w || y < 0 || y >= h)
        continue;
      if(map[y][x] != -1)
        continue;
      map[y][x] = i;
      q[qb++] = (entry){x, y, e.d+1};
    }
  }
  return errorDistance;
}
int main(){
  int ax1,ay1,ax2,ay2;
  int bx1,by1,bx2,by2;
  scanf("%d %d", &w, &h);
  ++w; ++h;
  scanf("%d %d %d %d", &ax1, &ay1, &ax2, &ay2);
  scanf("%d %d %d %d", &bx1, &by1, &bx2, &by2);
  ResetMap();
  map[by1][bx1] = -2;
  map[by2][bx2] = -2;
  int d1 = FindPath(ax1, ay1, ax2, ay2);
  map[by1][bx1] = -1;
  map[by2][bx2] = -1;
  d1 += FindPath(bx1, by1, bx2, by2);
  ResetMap();
  map[ay1][ax1] = -2;
  map[ay2][ax2] = -2;
  int d2 = FindPath(bx1, by1, bx2, by2);
  map[ay1][ax1] = -1;
  map[ay2][ax2] = -1;
  d2 += FindPath(ax1, ay1, ax2, ay2);
  int ret = (d1 < d2 ? d1 : d2);
  if(ret >= errorDistance)
    printf("IMPOSSIBLE\n");
  else
    printf("%d\n", ret);
  return 0;
}

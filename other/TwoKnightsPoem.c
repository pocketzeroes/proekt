#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];

char*getstr(){
  char line[2000];
  gets(line);
  return strdup(line);
}

char*lo[4]= { "qwertyuiop",
              "asdfghjkl;",
              "zxcvbnm,./",
              "++      ++" };
char*hi[4]= { "QWERTYUIOP",
              "ASDFGHJKL:",
              "ZXCVBNM<>?",
              "++      ++" };
int h = 4;
int w = 10;
char*a;
typedef struct{
  bool b;
  bool isset;
}Bool;
Bool memo[101][4][4][10][10];
int dx[8]={ -2, -2, -1, -1, 1, 1, 2, 2 };
int dy[8]={ -1, 1, -2, 2, -2, 2, -1, 1 };

typedef struct{
  int x,y;
}Point;
Point newPoint(int x, int y){
  Point rez;
  rez.x = x;
  rez.y = y;
  return rez;
}
///////////////
bool dfs(int i, Point p, Point q);

bool advance(int i, Point p, Point q){
  Point t = newPoint(0, 0);
  for(int k = 0; k < 8; k++){
    t.x = q.x + dx[k];
    if (0 <= t.x && t.x < h){
      t.y = q.y + dy[k];
      if (0 <= t.y && t.y < w)
        if(dfs(i + (lo[t.x][t.y] == '+' ? 0 : 1), t, p))
          return true;
    }
  }
  return false;
}
bool dfs(int i, Point p, Point q){
  if (i > strlen(a))
    return true;
  if(memo[i][p.x][q.x][p.y][q.y].isset != false)
    return memo[i][p.x][q.x][p.y][q.y].b;
  if (i > 0){
    bool ok = !(p.x == q.x && p.y == q.y);
    ok &= lo[p.x][p.y] == '+' || a[i - 1] == (lo[q.x][q.y] == '+' ? hi[p.x][p.y] : lo[p.x][p.y]);
    if (!ok){
      memo[i][p.x][q.x][p.y][q.y].isset = true;
      return memo[i][p.x][q.x][p.y][q.y].b = false;
    }
  }
  bool rv = (advance(i, q, p) || advance(i, p, q));
  memo[i][p.x][q.x][p.y][q.y].isset = true;
  memo[i][p.x][q.x][p.y][q.y].b = rv;
  return rv;
}
int main(){
  Point left = newPoint(h - 1, 0), 
       right = newPoint(h - 1, w - 1);
  for(char*s = getstr(); strcmp("*", s)!=0; s = getstr()){
    memset(memo, 0, sizeof(memo));
    a = s;
    printf("%d\n", dfs(0, left, right) ? 1 : 0);
  }
  return 0;
}

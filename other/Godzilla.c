#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};
int gdy[]={-1,0,1,0};
int gdx[]={0,1,0,-1};
char bord[1005][1005];

void solve(){
  int h,w;
  if(scanf("%d %d", &w, &h)!=2)
    exit(0);
  for(int i=0;i<h;i++)
    scanf("%s", bord[i]);
  int Gx,Gy;
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      if(bord[i][j]=='G')
        Gy=i, Gx=j;
  static int d[1005][1005];
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      d[i][j] = 1e9;
  static int q[1000005];
  int ql=0,qd=0;
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      if(bord[i][j]=='M') {
        d[i][j] = 0;
        q[ql++] = w*i + j;
      }
  int answer = 0;
  for(int it=0; ; it++){
    for(int dir=0;dir<4;dir++){
      int y2=Gy+dy[dir], x2=Gx+dx[dir];
      if(y2<0 || y2>=h || x2<0 || x2>=w)
        continue;
      if(bord[y2][x2]=='R'){
        answer++;
        Gy=y2, Gx=x2;
        goto moved;
      }
    }
    for(int dir=0;dir<4;dir++){
      int y2=Gy+dy[dir], x2=Gx+dx[dir];
      if(y2<0 || y2>=h || x2<0 || x2>=w)
        continue;
      if(bord[y2][x2]=='.'){
        Gy=y2, Gx=x2;
        goto moved;
      }
    }
  moved:;
    bord[Gy][Gx]='G';
    int ql_before=ql;
    while(qd<ql_before){
      int y=q[qd]/w, x=q[qd]%w;
      qd++;
      for(int dir=0;dir<4;dir++){
        int y2=y+dy[dir], x2=x+dx[dir];
        if(y2<0 || y2>=h || x2<0 || x2>=w) 
          continue;
        if(bord[y2][x2]=='R') 
          continue;
        if(d[y2][x2] == 1e9){
          d[y2][x2] = d[y][x]+1;
          q[ql++] = w*y2 + x2;
        }
      }
    }
    for(int dir=0;dir<4;dir++){
      int y=Gy, x=Gx;
      while(1){
        y+=dy[dir], x+=dx[dir];
        if(y<0 || y>=h || x<0 || x>=w) 
          break;
        if(bord[y][x]=='R') 
          break;
        if(d[y][x] != 1e9){
          printf("%d\n", answer);
          return;
        }
      }
    }
  }
}
int main(){
  int T;
  scanf("%d", &T);
  while(T){
    solve();
      T--;
  }
  return 0;
}

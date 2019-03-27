#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

int main(){
  int x,y,t,n,d,m;
  int best  [11][30][30];
  int ismole[11][30][30];
  scanf("%d %d %d", &n, &d, &m);
  while(n){
    memset(ismole, 0, sizeof(ismole));
    memset(best  , 0, sizeof(best  ));
    for(int i=0; i<m; i++){
      scanf("%d %d %d", &x, &y, &t);
      if (t<=10)
        ismole[t][y+5][x+5]=1;
    }
    n+=10;
    for(t=1;t<=10;t++)
      for(y=0;y<n;y++)
        for(x=0;x<n;x++)
          for(int dx=-d;dx<=d;dx++)
            for(int dy=-d;dy<=d;dy++) {
              int mx=0,my=0,cx=x,cy=y,cnt=best[t-1][y][x];              
              while (true) {
                cnt+=ismole[t][cy][cx];
                best[t][cy][cx] = max(best[t][cy][cx], cnt);
                cx+=dx, cy+=dy;
                mx+=dx, my+=dy;
                if(cx<0 || cy<0 || cx>=n || cy>=n) 
                  break;
                if(mx*mx+my*my>d*d || (!dx&&!dy)) 
                  break;
              }
            }
    int b=0;
    for(y=0;y<n;y++)
      for(x=0;x<n;x++){
        b = max(b, best[10][y][x]);
      }
    printf("%d\n", b);
    scanf("%d %d %d", &n, &d, &m);
  }
  return 0;
}

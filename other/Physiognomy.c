#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) { typeof(a) tmp; tmp = a; a = b; b = tmp; }
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


typedef struct{
  double first;
  int    second;
}pair;
///////////////////
double inf = 1e70L;
enum{ MAXN = 12};
int dx[4]={-1,-1, 1, 1};
int dy[4]={-1, 1, 1,-1};
double dp[MAXN*4][1<<MAXN];
pair dist[MAXN*4][MAXN*4];

typedef struct Lamp{
  int x,y;
  int energy;
}Lamp;

bool intersects(Lamp a, Lamp b, Lamp mid){
  a.x-=mid.x, a.y-=mid.y;
  b.x-=mid.x, b.y-=mid.y;
  for(int rot=4; rot--; ){
    if ((a.y>=1)!=(b.y>=1)){
      if (abs(a.x*abs(b.y-a.y) + (b.x-a.x)*abs(1-a.y)) < abs(b.y-a.y))
        return true;
    }
    if ((a.y>=0)!=(b.y>=0)){
      if (abs(a.x*abs(b.y-a.y) + (b.x-a.x)*abs(0-a.y)) < abs(b.y-a.y))
        return true;
    }
    a.y = -a.y;
    b.y = -b.y;
    swap(a.x, a.y);
    swap(b.x, b.y);
  }
  return false;
}
bool passes(Lamp a, Lamp b, Lamp mid){
  a.x-=mid.x, a.y-=mid.y;
  b.x-=mid.x, b.y-=mid.y;
  if(a.y>=0 == b.y>=0)
      return false;
  if(a.x*abs(b.y-a.y) + (b.x-a.x)*abs(0-a.y) < 0)
    return true;
  return false;
}
int main(){
  int n;
  scanf("%d", &n);
  Lamp lamp[n];
  for(int i=0; i<n; i++)
    scanf("%d %d %d", &lamp[i].x, &lamp[i].y, &lamp[i].energy);
  for(int i=0; i<n; i++){
    for (int iz=0; iz<4; iz++){
      for(int j=0; j<n; j++){
        for (int jz=0; jz<4; jz++){
          dist[i*4+iz][j*4+jz].first=hypotl( (lamp[i].x+dx[iz])-(lamp[j].x+dx[jz]), (lamp[i].y+dy[iz])-(lamp[j].y+dy[jz]));
          for (int k=0; k<n; k++){
            if(intersects((Lamp){lamp[i].x+dx[iz],lamp[i].y+dy[iz]}, (Lamp){lamp[j].x+dx[jz],lamp[j].y+dy[jz]}, lamp[k])){
              dist[i*4+iz][j*4+jz].first=inf;
            }
            else if(passes((Lamp){lamp[i].x+dx[iz],lamp[i].y+dy[iz]},(Lamp){lamp[j].x+dx[jz],lamp[j].y+dy[jz]}, lamp[k])){
              dist[i*4+iz][j*4+jz].second|=1<<k;
            }
          }
        }
      }
    }
  }
  double res=inf;
  for(int sp=0; sp<n*4; sp++){
    for(int i=n*4; i--;)
      for(int j=1<<n; j--;)
        dp[i][j]=inf;
    dp[sp][0]=0;
    for(int rep=n*4; rep-->sp;){
      bool changed=false;
      for(int x=n*4; x-->sp;){
        for(int mask=1<<n; mask--;){
          if (dp[x][mask]<inf) {
            for (int y=n*4; y-->sp;){
              if (dist[x][y].first<inf){
                if (dp[y][mask^dist[x][y].second] > dp[x][mask]+dist[x][y].first + 1e-10L){
                  dp[y][mask^dist[x][y].second] = dp[x][mask]+dist[x][y].first;
                  changed=true;
                }
              }
            }
          }
        }
      }
      if(!changed)
        break;
    }
    for(int mask=1<<n; mask--;){
      int value=0;
      for(int i=n; i--;)
        value += lamp[i].energy*(mask&(1<<i)?1:-1);
      if(!value)
        res = min(res, dp[sp][mask]);
    }
  }
  if(res<inf)
    printf("%.10lf\n", res);
  else
    puts("IMPOSSIBLE");
  return 0;
}

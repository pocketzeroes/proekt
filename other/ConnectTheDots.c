#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef long long ll;
typedef struct{
  ll x, y;
}pt;
pt newpt(ll a, ll b){
  return(pt){a,b};
}
pt sub(pt P, pt Q){
  return newpt(P.x-Q.x, P.y-Q.y);
}
ll dot(pt P, pt Q){
  return P.x*Q.x + P.y*Q.y;
}
ll cross(pt P, pt Q){
  return P.x*Q.y - P.y*Q.x;
}
bool parallel(pt P, pt Q){
  return dot(P, Q) >= 0 && 
       cross(P, Q) == 0;
}
bool between(pt P1, pt Q, pt P2, bool P1_closed, bool P2_closed){
  if(parallel(P1, Q))
    return P1_closed;
  if(parallel(Q, P2))
    return P2_closed;
  return(cross(P1, Q) > 0) + 
        (cross(Q, P2) > 0) +
        (cross(P1,P2) < 0) >= 2;
}
pt seq[16];
ll grid[4][4];
int main(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      scanf("%lld", &grid[i][j]);
      seq[grid[i][j]-1] = newpt(j, i);
    }
  }
  pt delta[15]; clr(delta);
  for(int i=0; i<15; i++)
    delta[i] = sub(seq[i+1], seq[i]);
  ll ans = 1;
  pt lo_dir = delta[0];
  pt hi_dir = delta[0];
  bool lo_closed = true;
  bool hi_closed = true;
  for(int at=1; at<15; at++){
    if(between(lo_dir, delta[at], hi_dir, lo_closed, hi_closed)){
      lo_dir = hi_dir = delta[at];
      lo_closed = hi_closed = true;
    }
    else{
      ans++;
      pt new_lo = newpt(-lo_dir.x, -lo_dir.y);
      pt new_hi = newpt(-hi_dir.x, -hi_dir.y);
      lo_closed = hi_closed = false;
      if(!between(new_lo, delta[at], new_hi, false, false)){
        if(between(hi_dir, delta[at], new_lo, true, true)){
          new_lo = delta[at];
          lo_closed = true;
        }
        else{
          new_hi = delta[at];
          hi_closed = true;
        }
      }
      lo_dir = new_lo;
      hi_dir = new_hi;
    }
  }
  printf("%lld\n", ans);
  return 0;
}

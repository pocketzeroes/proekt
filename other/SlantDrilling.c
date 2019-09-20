#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  double first;
  double second;
}pdd;
typedef struct{
  ll     first;
  double second;
}pld;

int compP(pld a, pld b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
int compP2(pdd a, pdd b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pld maxP(pld a,pld b){return compP (a,b)>0?a:b;}
pdd minP(pdd a,pdd b){return compP2(a,b)<0?a:b;}

/////////////////////////////////////////////////////////////
typedef struct{
  ll x,y;
}pt;
pt opAdd(pt t, pt a){
  return(pt){t.x+a.x, t.y+a.y};
}
ll dot(pt a, pt b){
  return a.x*b.x + a.y*b.y;
}
double clamp(double x, double a, double b){
  return fmax(fmin(x,b),a);
}
bool contains_zero(pt*v, int sz){
  bool does=false;
  for(int i=0,j=sz-1; i!=sz; j=i++){
    does^=(v[i].y>=0)!=(v[j].y>=0) && v[i].x*llabs(v[j].y - v[i].y) + (v[j].x - v[i].x)*llabs(0 - v[i].y)<=0;
  }
  return does;
}
ll area(pt*v, int sz){
  ll res=0;
  for(int i=0,j=sz-1; i!=sz; j=i++){
    res += v[i].y * v[j].x - v[i].x * v[j].y;
  }
  return llabs(res);
}
int main(){
  int n;
  scanf("%d", &n);
  double res=1e60L;
  bool inside_any=false;
  pdd origin = (pdd){1e60L,1e60L};
  pld biggest= (pld){-1ll, 1e60L};
  for(int i=0; i<n; i++){
    int h0, h1, m;
    scanf("%d%d%d", &h0, &h1, &m);
    static pt v[1000000];
    for(int j=m; j--;){
      scanf("%lld %lld", &v[j].x, &v[j].y);
    }
    biggest = maxP(biggest, (pld){area(v, m),h0});
    bool contained = contains_zero(v, m);
    for(int j=0,k=m-1; j<m; k=j++){
      pt a=v[j],
         b=v[k],
         w=(pt){b.x-a.x,b.y-a.y};
      double t = clamp(-1.L*dot(a,w)/(double)dot(w,w),0,1);
      double cdist = hypot(a.x+w.x*t,a.y+w.y*t);
      res = fmin(res, (double)hypot(cdist, fmin(h0,h1)));
      if(contained)
        origin = minP(origin,(pdd){cdist,h1});
    }
    inside_any |= contained;
  }
  if(inside_any)
    res = fmin(res, origin.second);
  else
    res = fmin(res, biggest.second);
  printf("%lf\n", res);
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

typedef struct{
  ll x, y;
}point;
ll area2(point a, point b, point c){
  return llabs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}
int main(){
  point p[4];
  for (;;){
    for (int i = 0; i < 4; ++i) {
      ll z;
      scanf("%lli%lli%lli", &p[i].x, &p[i].y, &z);
      if (p[i].x + p[i].y + z == 0) 
        return 0;
    }
    ll triang = area2(p[0], p[1], p[2]),
       a0     = area2(p[3], p[0], p[1]),
       a1     = area2(p[3], p[1], p[2]),
       a2     = area2(p[3], p[2], p[0]),
       sumareas = a0 + a1 + a2;
    bool inside = (triang == sumareas);
    if (triang == 0 && inside) {
      ll a = min(p[0].x, min(p[1].x, p[2].x)),
         b = max(p[0].x, max(p[1].x, p[2].x)),
         c = min(p[0].y, min(p[1].y, p[2].y)),
         d = max(p[0].y, max(p[1].y, p[2].y));
      inside = (a < p[3].x && p[3].x < b) || (c < p[3].y && p[3].y < d);
    }
    else
        inside &= (a0 != 0 && a1 != 0 && a2 != 0);
    puts(inside ? "YES" : "NO");
  }
  return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;

typedef long long ll;
enum{ MAXN = 300005};

ll ccw(pair a, pair b){
  return 1ll * a.first * b.second - 1ll * b.first * a.second;
}
int main(){
  int n;
  scanf("%d", &n);
  ll ans = 0;
  while(n--){
    int m;
    scanf("%d",&m);
    pair v[m];
    for(int z=0;z<m;z++)
      scanf("%d %d", &v[z].first, &v[z].second);
    ll ret=0;
    for(int j=0; j<m; j++)
      ret += ccw(v[j], v[(j + 1)%m]);
    ans += llabs(ret);
  }
  printf("%lld\n", ans/2);
  return 0;
}

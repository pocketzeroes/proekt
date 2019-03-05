#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;

typedef long long ll;
enum{ MOD = 1000000007};
int mul(int a, int b) {return (1LL*a*b)%MOD;}
int n, q;

int power(int x, int n, int MOD){
  int ans = 1;
  while (n) {
    if (n&1)
      ans = (1LL*ans*x)%MOD;
    x = (1LL*x*x)%MOD;
    n >>= 1;
  }
  return ans;
}
int inv(int x){
  return power(x, MOD-2, MOD);
}

pair*t;

void propagate(int id, int l, int r){
#define x t[id].second
  if (x != 0){
    int m = (l+r)/2;
    t[2*id].first    = (t[2*id].first + 1LL*(m-l+1)*x)%MOD;
    t[2*id].second   = (t[2*id].second + x)%MOD;
    t[2*id+1].first  = (t[2*id+1].first + 1LL*(r-m)*x)%MOD;
    t[2*id+1].second = (t[2*id+1].second + x)%MOD;
    x = 0;
  }
#undef x
}
void update(int id, int l, int r, int i, int j, int x){
  if (i > r || j < l)
    return;
  if (i <= l && r <= j) {
    t[id].first = (t[id].first + 1LL*(r-l+1)*x)%MOD;
    t[id].second = (t[id].second + x)%MOD;
    return;
  }
  propagate(id, l, r);
  int m = (l+r)/2;
  update(2*id, l, m, i, j, x);
  update(2*id+1, m+1, r, i, j, x);
  t[id].first = (t[2*id].first + t[2*id+1].first)%MOD;
}
int query(int id, int l, int r, int i, int j){
  if (i > r || j < l)
    return 0;
  if (i <= l && r <= j)
    return t[id].first;
  propagate(id, l, r);
  int m = (l+r)/2;
  return (query(2*id, l, m, i, j) + 
          query(2*id+1, m+1, r, i, j))%MOD;
}
int main(){
  scanf("%d %d", &n, &q);
  t = calloc(4*n+1, sizeof(pair));
  int ans = 0;
  for(int i=1; i<=q; ++i){
    int type;
    scanf("%d", &type);
    if(type == 1){
      int l, r;
      scanf("%d %d", &l, &r);
      int x = inv(r-l+1);
      ans = (ans + 1)%MOD;
      ans = (ans + 2LL*x*query(1, 1, n, l, r))%MOD;
      update(1, 1, n, l, r, x);
    }
    else
      printf("%d\n", ans);
  }
  return 0;
}

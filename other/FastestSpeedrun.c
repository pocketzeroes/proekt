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

int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

void fill_l(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
  int n;
  scanf("%d", &n);
  int p[n+1];
  fill(p, n+1, -1);
  vec c[n+1]; memset(c,0,sizeof(c));
  ll a[n+1][n+1]; memset(a, 0, sizeof(a));
  ll ans = 0;
  for(int i=1; i<=n; ++i){
    scanf("%d", &p[i]);
    c[p[i]].ptr = pushback(c[p[i]].ptr, &c[p[i]].sz, i);
    ll x;
    scanf("%lld", &x);
    ans += x;
    for(int q=0;q<n+1;q++){
      scanf("%d", &a[i][q]), a[i][q]-=x;
    }
  }
  for(int u = 0; u <= n; ++u){
    int t = u,
        h = p[u];
    while(h >= 0 && p[h] >= 0 && t != h)
      t=p[t], h=p[p[h]];
    if(h < 0 || p[h] < 0)
      continue;
    vec cycle = newVec();
    do{
      cycle.ptr = pushback(cycle.ptr, &cycle.sz, t);
      t = p[t];
    }
    while(t != h);
    int m = max_element(cycle.ptr, cycle.sz);
    for(int z=0;z<cycle.sz;z++){int x = cycle.ptr[z];
      p[x] = -3;
      for(int i = 0; i <= n; ++i)
        a[m][i] = min(a[m][i], a[x][i]);
      for(int q=0;q<c[x].sz;q++){int y = c[x].ptr[q];
        p[y] = m;
      }
    }
    p[m] = -2;
    ans += a[m][n];
    for(int _=0;_<n+1;_++){
      a[m][_] -= a[m][n];
    }
  }
  int mc[n+1];
  fill(mc, n+1, -1);
  vec order = newVec();
  void dfs(int v, int u){
    if(v>=0 && p[v] >= -2 && mc[v] == -1)
      mc[v] = u, dfs(p[v], u),
      order.ptr = pushback(order.ptr, &order.sz, v);
  }
  for(int u=n; u >= 0; --u)
    dfs(u, u);
  ll cost[order.sz];
  fill_l(cost, order.sz, (ll)1e18);
  for(int i = order.sz-1; i >= 0; --i){
    int u = order.ptr[i];
    cost[i] = a[u][0];
    for(int j = i+1; j < order.sz; ++j)
      cost[i] = min(cost[i], cost[j]+a[u][mc[order.ptr[j]]]);
  }
  printf("%lld\n", ans+cost[0]);
  return 0;
}

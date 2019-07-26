#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}

//////////////////////////////
typedef long long ll;
enum{ MAXN = 1010};
int  n, m;
int  a[MAXN][MAXN],
     b[MAXN][MAXN];
int  cnt    [MAXN],
     done   [MAXN];
pair where_a[MAXN*MAXN],
     where_b[MAXN*MAXN];
vecp same   [MAXN];
vec  edges  [MAXN];


void load(int a[MAXN][MAXN]){
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);
}
ll solve_same_shelf(vecp*a){
  ll ret = 0;
  vec lis = newVec();
  qsort(a->ptr, a->sz, sizeof(pair), cmpP);
  for(int z=0; z<a->sz; z++){pair x = a->ptr[z];
    int it = lower_bound(lis.ptr, lis.sz, x.second);
    if(it == lis.sz)
      lis.ptr = pushback(lis.ptr, &lis.sz, x.second);
    else
      lis.ptr[it] = x.second;
  }
  if(lis.sz == a->sz)
    return 0;
  if(a->sz == m)
    ret = 1;
  ret += a->sz - lis.sz;
  return ret;
}
int dfs(int x){
  int ret = (cnt[x] == m);
  done[x] = 1;
  for(int z=0; z<edges[x].sz; z++){int y = edges[x].ptr[z];
    if(done[y])
      continue;
    ret &= dfs(y);
  }
  return ret;
}
ll solve(){
  int empty_cell    = 0;
  int everything_ok = 1;
  memset(where_a, -1, sizeof where_a);
  memset(where_b, -1, sizeof where_b);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < m; ++j) {
      empty_cell |= !a[i][j];
      everything_ok &= (a[i][j] == b[i][j]);
      where_a[a[i][j]] =(pair){ i, j };
      where_b[b[i][j]] =(pair){ i, j };
      cnt[i] += (a[i][j] > 0);
    }
  }
  if (everything_ok)
    return 0;
  if (empty_cell == 0)
    return -1;
  ll ans = 0;
  for (int i = 1; i < MAXN*MAXN; ++i) {
    if (where_a[i].first == -1)
      continue;
    if (where_a[i].first == where_b[i].first) {
      same[where_a[i].first].ptr = pushbackP(same[where_a[i].first].ptr, &same[where_a[i].first].sz, (pair){where_a[i].second, where_b[i].second});
    }
    else{
      edges[where_a[i].first].ptr = pushback(edges[where_a[i].first].ptr, &edges[where_a[i].first].sz, where_b[i].first);
      edges[where_b[i].first].ptr = pushback(edges[where_b[i].first].ptr, &edges[where_b[i].first].sz, where_a[i].first);
      ++ans;
    }
  }
  for (int i = 0; i < n; ++i)
    ans += solve_same_shelf(&same[i]);
  for (int i = 0; i < n; ++i)
    if (done[i] == 0 && edges[i].sz != 0)
      ans += dfs(i);
  return ans;
}
int main(){
  scanf("%d%d", &n, &m);
  load(a);
  load(b);
  printf("%lld\n", solve());
  return 0;
}

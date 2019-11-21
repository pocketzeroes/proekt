#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

///////////////////////////////////
typedef long long ll;
ll INF = LLONG_MAX/2;

typedef struct Edge{
  int a, b, length;
}Edge;
Edge newEdge(int a, int b, int l){
  return(Edge){a,b,l};
}
typedef struct Line{
  ll slope, intercept;
  bool null;
}Line;
Line newLine(ll s, ll i){
  return(Line){s,i,1};
}
double intersect(Line t, Line l){
  return(double)(t.intercept - l.intercept) / (l.slope - t.slope);
}

int main(){
  int n = in_nextInt();
  int m = in_nextInt();
  Edge edges[m];
  for(int i=0; i<m; i++){
    int a = in_nextInt() - 1;
    int b = in_nextInt() - 1;
    int length = in_nextInt();
    edges[i] = newEdge(a, b, length);
  }
  ll dist[n][n]; dfill(dist, n, n, INF);
  dist[0][0] = 0;
  for(int k = 0; k+1 < n; k++){
    for(int z=0;z<m;z++){Edge e = edges[z];
      dist[k+1][e.b] = fminl(dist[k+1][e.b], dist[k][e.a] + e.length);
      dist[k+1][e.a] = fminl(dist[k+1][e.a], dist[k][e.b] + e.length);
    }
  }
  Line lines[n]; clr(lines);
  for(int k=0; k<n; k++){
    if(dist[k][n-1] == INF)
      continue;
    lines[k] = newLine(k, dist[k][n-1]);
  }
  bool onOptimalPath[n][n]; clr(onOptimalPath);
  for(int i=0; i<n; i++){
    if(lines[i].null==0)continue;
    double hi = 1e18;
    for(int j=0; j<i; j++){
      if(lines[j].null==0)continue;
      hi = fmin(hi, intersect(lines[i], lines[j]));
    }
    double lo = 0;
    for(int j=i+1; j<n; j++){
      if(lines[j].null==0)continue;
      lo = fmax(lo, intersect(lines[i], lines[j]));
    }
    onOptimalPath[i][n-1] = lo <= hi;
  }
  for(int k=n-2; k>=0; k--){
    for(int z=0;z<m;z++){Edge e = edges[z];
      if(dist[k+1][e.b] == dist[k][e.a] + e.length && onOptimalPath[k+1][e.b])
        onOptimalPath[k][e.a] = true;
      if(dist[k+1][e.a] == dist[k][e.b] + e.length && onOptimalPath[k+1][e.a])
        onOptimalPath[k][e.b] = true;
    }
  }
  vec res = newVec();
  for(int i=0; i<n; i++){
    bool isRedundant = true;
    for(int k=0; k<n; k++){
      if(onOptimalPath[k][i])
        isRedundant = false;
    }
    if(isRedundant)
      pb(res, i);
  }
  printf("%d\n", res.sz);
  for(int z=0;z<res.sz;z++){
    printf("%d ", res.ptr[z]+1);
  }
  puts("");
  return 0;
}

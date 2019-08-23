#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
inline int min(int a, int b){return a<b?a:b;}
inline int min3(int a, int b, int c){ return min(a, min(b, c)); }
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
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

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char line[200000];
char*getln(){
  gets(line);
  return strdup(line);
}
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
/////////////////////////////////////////////


vec Cpos;
vec Cv;
int S, b[100][100];
int**Cd1;
int**Cd2;
int**Cd3;
bool seen[100][100];

vec TokenizeInt(){
  vec rez=newVec();
  char*s=getln();
  int n;
  while(1){
    sscanf(s, "%d", &n);
    rez.ptr = pushback(rez.ptr, &rez.sz, n);
    s = strchr(s, ' ');
    if(s==NULL)
      break;
    s++;
  }
  return rez;
}
int BipartiteMatch(int**m){
  int V = S * 2 + 2;
  int d[V][V]; dfill(d, V, V, 1000000000);
  for(int i = 0; i < S; i++)
    d[V-2][i] = 0;
  for(int i = 0; i < S; i++)
    d[i+S][V-1] = 0;
  for(int i = 0; i < S; i++)
    for(int j = 0; j < S; j++)
      d[i][j+S] = m[i][j];
  int ret = 0;
  for(int i = 0; i < S; i++){
    int dist[V]; fill(dist, V, 1000000000);
    int prev[V]; fill(prev, V, 1000000000);
    dist[V-2] = 0;
    bool change = true;
    while(change){
      change = false;
      for(int x = 0; x < S*2+2; x++){
        for(int y = 0; y < S*2+2; y++){
          if(d[x][y] < 1000000000){
            if(dist[x] + d[x][y] < dist[y]){
              dist[y] = dist[x] + d[x][y];
              prev[y] = x;
              change = true;
            }
          }
        }
      }
    }
    ret += dist[V-1];
    for(int x = V-1; x != V-2; x = prev[x]){
      d[x][prev[x]] = -d[prev[x]][x];
      d[prev[x]][x] = 1000000000;
    }
  }
  return ret;
}
int main(){
  int N, prob = 1;
  scanf("%d", &N);
  getchar();
  for(int z=0; z<N; z++){
    Cpos = TokenizeInt();
    Cv   = TokenizeInt();
    S = Cpos.sz;
    memset(b, 0, sizeof(b));
    int cur = 1;
    for(int y = 1; y <= (S+1)/2; y++)
      for(int x = 1; x <= y + S/2; x++)
        b[y][x] = cur++;
    for(int y = 1; y < (S+1)/2; y++)
      for(int x = y+1; x <= S; x++)
        b[y+(S+1)/2][x] = cur++;
    Cd1 = newmat(S, S);
    Cd2 = newmat(S, S);
    Cd3 = newmat(S, S);
    for(int i = 0; i < S; i++){
      int y, x;
      for(y = 1; y <= S; y++)
        for(x = 1; x <= S; x++)
          if(b[y][x] == Cpos.ptr[i])
            goto found;
  found:
      memset(seen, 0, sizeof(seen));
      vecp q = newVecP();
      q.ptr = pushbackP(q.ptr, &q.sz, newPair(x, y));
      int dist=0;
      while(q.sz>0){
        vecp q2=newVecP();
        while(q.sz>0){
          x = q.ptr[q.sz-1].first;
          y = q.ptr[q.sz-1].second;
          q.sz--;
          if(seen[y][x] || !b[y][x])
            continue;
          seen[y][x] = true;
          if(y == (S+1)/2) Cd1[i][x-1] = dist * Cv.ptr[i];
          if(x == (S+1)/2) Cd2[i][y-1] = dist * Cv.ptr[i];
          if(x == y)       Cd3[i][x-1] = dist * Cv.ptr[i];
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x+1, y)  );
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x-1, y)  );
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x, y+1)  );
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x, y-1)  );
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x+1, y+1));
          q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x-1, y-1));
        }
        swap(q, q2);
        dist++;
      }
    }
    printf("Case #%d: ", prob++);
    printf("%d", min3(BipartiteMatch(Cd1), BipartiteMatch(Cd2), BipartiteMatch(Cd3)) );
    puts("");
  }
  return 0;
}

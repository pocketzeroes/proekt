#define _GNU_SOURCE 1
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
char*mkmv(char a, int b){
  char*ptr=NULL;
  asprintf(&ptr, "%c %d", a, b);
  return ptr;
}

enum{ MAXB = 400005};
int r[MAXB], 
    c[MAXB];
char DSTR[4] = {'>', '<', 'v', '^'};
char*s   [MAXB];
int face [MAXB];
int visit[MAXB];
int link [MAXB][4];
vecp rows[MAXB], 
     cols[MAXB];
vec  deps[MAXB];
vec  solution;
bool no_solution;
enum{
  LEFT  = 0,
  RIGHT = 1,
  UP    = 2,
  DOWN  = 3
};
inline bool IsNeighbor(int x, int y){
  return abs(r[x]-r[y]) + abs(c[x]-c[y]) == 1;
}
void dfs(int x){
  visit[x] = 1;
  for(int dir = 0; dir < 4; dir++){
    int y = link[x][dir];
    if(IsNeighbor(x, y) && !visit[y]){
      face[y] = (dir^1);
      s[y] = mkmv(DSTR[dir], (dir/2?c[y]:r[y]));
      dfs(y);
    }
  }
}
inline void AddLink(int x, int y){
  if (x == -1 || y == -1)
    return;
  deps[x].ptr = pushback(deps[x].ptr, &deps[x].sz, y);
}
void topological_sort(int x){
  visit[x] = 1;
  for(int z=0;z<deps[x].sz;z++){int y = deps[x].ptr[z];
    if(visit[y] == 0)
      topological_sort(y);
    else if(visit[y] == 1)
      no_solution = 1;
  }
  solution.ptr = pushback(solution.ptr, &solution.sz, x);
  visit[x] = 2;
}
int main(){
  int N, M, B;
  scanf("%d %d %d", &N, &M, &B);
  for(int i=0; i<B; i++){
    scanf("%d %d", &r[i], &c[i]);
    rows[r[i]].ptr = pushbackP(rows[r[i]].ptr, &rows[r[i]].sz, (pair){c[i], i});
    cols[c[i]].ptr = pushbackP(cols[c[i]].ptr, &cols[c[i]].sz, (pair){r[i], i});
  }
  for(int i = 1; i < MAXB; i++){
    qsort(rows[i].ptr, rows[i].sz, sizeof(pair), cmpP);
    qsort(cols[i].ptr, cols[i].sz, sizeof(pair), cmpP);
  }
  memset(link, -1, sizeof(link));
  for(int i = 1; i < MAXB; i++){
    for(size_t j = 1; j < rows[i].sz; j++){
      int prev = rows[i].ptr[j-1].second;
      int now  = rows[i].ptr[j  ].second;
      link[prev][RIGHT] = now;
      link[now ][LEFT ] = prev;
    }
    for(size_t j = 1; j < cols[i].sz; j++){
      int prev = cols[i].ptr[j-1].second;
      int now  = cols[i].ptr[j  ].second;
      link[prev][DOWN] = now;
      link[now ][UP  ] = prev;
    }
  }
  dfs(0);
  for (int x = 1; x < B; x++) {
    AddLink(x, link[x][face[x]]);
    AddLink(link[x][face[x]^1], x);
  }
  memset(visit, 0, sizeof(visit));
  for (int x = 0; x < B; x++) {
    if (!visit[x])
      topological_sort(x);
  }
  if (no_solution)
    puts("impossible");
  else{
    puts("possible");
    for(int z=0; z<solution.sz; z++){int x = solution.ptr[z];
      if(x != 0)
        puts(s[x]);
    }
  }
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

typedef long long ll;

int  R,C;
char buf[16];
int  deg[16][16];
int  nod[16][16][4];
enum{ MAXV = 514};
bool mark[MAXV];
int  cap[MAXV][MAXV];
vec  edg[MAXV];
enum{ s=MAXV-2};
enum{ t=MAXV-1};
int dr[] = { -1, 0, 1, 0 },
    dc[] = { 0, 1, 0, -1 };
enum{ inf = 123456789};

void connect(int v, int w, int u){
  cap[v][w] = u;
  cap[w][v] = 0;
  edg[v].ptr = pushback(edg[v].ptr, &edg[v].sz, w);
  edg[w].ptr = pushback(edg[w].ptr, &edg[w].sz, v);
}
int dfs(int v, int flocap){
  if (v==t)
    return flocap;
  if (mark[v])
    return 0;
  mark[v] = 1;
  for(int i=(0);i<edg[v].sz;++i){
    int w = edg[v].ptr[i];
    if (cap[v][w]) {
      int f = dfs(w, min(flocap, cap[v][w]));
      if (f) {
        cap[v][w] -= f;
        cap[w][v] += f;
        return f;
      }
    }
  }
  return 0;
}
void doit() {
  scanf("%d%d",&R,&C);
  if (R==0) exit(0);
  for(int v=(0);v<(MAXV);++v)
    edg[v].sz=0;
  memset(cap,0,sizeof(cap));
  for(int r=(0); r<(R); ++r){
    for(int c=(0); c<(C); ++c){
      scanf(" %s", buf);
      if (0==strcmp("x",buf))
        deg[r][c]=0;
      else
        deg[r][c] = strlen(buf);
    }
  }
  int next = 0;
  for(int r=(0); r<(R); ++r){
    for(int c=(0);c<(C);++c){
      if (deg[r][c] != 2) {
        for(int k=(0);k<(4);++k)
          nod[r][c][k] = next;
        if ((r+c)%2)
          connect(s, next, deg[r][c]);
        else
          connect(next, t, deg[r][c]);
        ++next;
      }
      else {
        for(int k=(0);k<(4);++k)
          nod[r][c][k] = next + (k%2);
        if ((r+c)%2)
          for(int k=(0);k<(2);++k)
            connect(s, next+k, 1);
        else
          for(int k=(0);k<(2);++k)
            connect(next+k, t, 1);
        next += 2;
      }
    }
  }
  for(int r=(0);r<(R);++r){
    for(int c=(0);c<(C);++c){
      if ((r+c)%2){
        for(int k=(0);k<(4);++k){
          int r2 = r+dr[k], c2 = c+dc[k];
          if (r2<0||r2>=R||c2<0||c2>=C)
            continue;
          int k2 = (k+2)%4;
          connect(nod[r][c][k], nod[r2][c2][k2], 1);
        }
      }
    }
  }
  while (1){
    memset(mark,0,sizeof(mark));
    int f = dfs(s, inf);
    if (f == 0)
      break;
  }
  int ed=0,od=0;
  for(int r=(0);r<(R);++r){
    for(int c=(0);c<(C);++c){
      if ((r+c)%2)
        od += deg[r][c];
      else
        ed += deg[r][c];
    }
  }
  bool happy = 1;
  for(int v=(0);v<(MAXV);++v)
    if (cap[s][v] || cap[v][t])
      happy = 0;
  printf("%s\n", happy ? "SOLVABLE" : "UNSOLVABLE");
}
int main() {
  while (1)
    doit();
}

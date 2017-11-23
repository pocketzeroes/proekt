#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
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
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

typedef long long ll;
ll W, P, sources[1000][2], endp[1000][2], pipes[1000], color[1000];
vec adjList[1000];

ll ccw(ll* a, ll *b, ll *p){
  ll c = (b[0] - a[0]) * (p[1] - a[1]) - (p[0] - a[0]) * (b[1] - a[1]);
  return (c == 0 ? 0 : (c > 0) ? 1 : -1);
}
bool intersects(ll*S, ll*T, ll*A, ll*B){
  return (ccw(A,B,S) * ccw(A,B,T) <= 0);
}
bool intersects2(ll*S, ll*T, ll*A, ll*B){
  return intersects(S, T, A, B) &&
         intersects(A, B, S, T);
}
bool twoc(int pipe, int curCol){
  if(color[pipe] != 0)
    return color[pipe] == curCol;
  color[pipe] = curCol;
  for(int z=0;z<adjList[pipe].sz;z++){int next = adjList[pipe].ptr[z];
    if(!twoc(next, -1*curCol))
      return false;
  }
  return true;
}
int main(){
  scanf("%lld %lld", &W, &P);
  for(int i=0; i<W; i++)
    scanf("%lld %lld", &sources[i][0], &sources[i][1]);
  for(int i=0; i<P; i++){
    scanf("%lld %lld %lld", &pipes[i], &endp[i][0], &endp[i][1]);
    pipes[i]--;
  }
  for(int i=0; i<P; i++){
    for(int j=i+1; j<P; j++){
      if(pipes[i] != pipes[j] && intersects2(sources[pipes[i]], endp[i], sources[pipes[j]], endp[j])){
        adjList[i].ptr = pushback(adjList[i].ptr, &adjList[i].sz, j);
        adjList[j].ptr = pushback(adjList[j].ptr, &adjList[j].sz, i);
      }
    }
  }
  bool possible = true;
  for(int i=0; i<P; i++)
    if(!color[i])
      possible &= twoc(i, 1);
  puts( possible ? "possible" : "impossible" );
  return 0;
}




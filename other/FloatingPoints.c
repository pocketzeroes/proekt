#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
///////////////////
typedef struct{
  int lx, ly, ux, uy;
  double slope;
}Edge;
Edge newEdge(int x1, int y1, int x2, int y2){
  Edge r;
  if(y1 <= y2){
    r.lx = x1;
    r.ly = y1;
    r.ux = x2;
    r.uy = y2;
  }
  else{
    r.lx = x2;
    r.ly = y2;
    r.ux = x1;
    r.uy = y1;
  }
  r.slope = (y1 - y2 + 0.0)/(x1 - x2 + 0.0);
  return r;
}

int N, B;
Edge*edges;
int*next;
int Intersect(int xpos, int ypos){
  double yintersect = 100000;
  int index = -1;
  for(int i = 0; i < N; i++){
    Edge cur = edges[i];
    int minx = min(cur.lx, cur.ux);
    int maxx = max(cur.lx, cur.ux);
    if(minx < xpos && maxx > xpos){
      double y = (xpos - minx) * cur.slope + ((minx == cur.lx) ? cur.ly : cur.uy);
      if((y < yintersect) && y > ypos){
        yintersect = y;
        index = i;
      }
    }
  }
  return index;
}
void FindNext(int i){
  if(edges[i].uy > 0){
    next[i] =  -1;
    return;
  }
  if(edges[i].uy == edges[i].ly){
    next[i] = -2;
    return;
  }
  if(edges[i].lx < edges[i].ux){
    if(edges[(i+1)%N].lx > edges[i].ux){
      next[i] = -2;
      return;
    }
    if(edges[(i+1)%N].ux > edges[i].ux){
      next[i] = ((i+1)%N);
      return;
    }
    if(edges[(i+1)%N].slope < edges[i].slope){
      next[i] = Intersect(edges[i].ux, edges[i].uy);
      return;
    }
    if(edges[(i+1)%N].slope > edges[i].slope){
      next[i] = -2;
      return;
    }
    return;
  }
  if(edges[i].lx > edges[i].ux){
    int j = (i - 1 + N) % N;
    if(edges[j].ux < edges[i].ux){
      next[i] = j;
      return;
    }
    if(edges[j].lx < edges[i].ux){
      next[i] = -2;
      return;
    }
    if(edges[j].slope > edges[i].slope){
      next[i] = Intersect(edges[i].ux, edges[i].uy);
      return;
    }
    if(edges[j].slope < edges[i].slope){
      next[i] = -2;
      return;
    }
  }
  return;
}
int main(){
  N = in_nextInt();
  B = in_nextInt();
  edges = calloc(N, sizeof(Edge));
  next = calloc(N, sizeof(int));
  int balls[B];
  int x,y;
  int prevx  = 0, prevy  = 0;
  int firstx = 0, firsty = 0;
  for(int i = 0; i < N; i++){
    x = in_nextInt();
    y = in_nextInt();
    if(i == 0){
      firstx = x;
      firsty = y;
    }
    if(i != 0)
      edges[i - 1] = newEdge(x, y, prevx, prevy);
    prevx = x;
    prevy = y;
  }
  edges[N - 1] = newEdge(prevx, prevy, firstx, firsty);
  for(int b = 0; b < B; b++)
    balls[b] = in_nextInt();
  for(int i = 0; i < N; i++)
    FindNext(i);
  for(int a = 0; a < N; a++)
    for(int i = 0; i < N; i++)
      if(next[i] != -1 && next[i] != -2)
        next[i] = next[next[i]];
  int total = 0;
  for(int b = 0; b < B; b++){
    int start = balls[b];
    int edge = Intersect(start, -100000000);
    if(edge == -1)
      total++;
    else if(next[edge] == -1)
      total++;
  }
  printf("%d\n", B-total);
  return 0;
}

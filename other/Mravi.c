#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 100000};

typedef struct pipe{
  int next, flow, square;
}pipe;
pipe newpipe(int next, int flow, int square){
  pipe rez;
  rez.next  = next;
  rez.flow  = flow;
  rez.square= square;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pipe*pushbackP(pipe*array, int *size, pipe value){
  pipe*output = resizeArray(array, pipe, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pipe*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vecp tree[MAXN];
int K[MAXN];

bool calc(int node, int dad, double current){
  if(current < K[node])
    return false;
  int d = tree[node].sz;
  for(int i=0; i<d; i++){
    int next = tree[node].ptr[i].next;
    if(next == dad)
      continue;
    double new_current = (current*tree[node].ptr[i].flow)/100;
    if(tree[node].ptr[i].square && new_current >= 1)
      new_current *= new_current;
    if(!calc(next, node, new_current))
      return false;
  }
  return true;
}
int main(){
  int n;
  scanf ("%d", &n);
  for(int i=0; i<n-1; i++){
    int a, b, c, t;
    scanf("%d %d %d %d", &a, &b, &c, &t);
    a--, b--;
    tree[a].ptr = pushbackP(tree[a].ptr, &tree[a].sz, newpipe(b, c, t));
    tree[b].ptr = pushbackP(tree[b].ptr, &tree[b].sz, newpipe(a, c, t));
  }
  for(int i=0; i<n; i++)
    scanf("%d", &K[i]);
  double lo = 0,
         hi = 2e9;
  for(int i=0; i<100; i++){
    double mid = (lo + hi) / 2;
    if(calc(0, -1, mid))
      hi = mid;
    else
      lo = mid;
  }
  printf("%.4lf\n", lo);
  return 0;
}

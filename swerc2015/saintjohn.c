#include <stdio.h>
#include <stdlib.h>

#define BOUNDINGBOX  1
#define MAXLARGE 10000
#define FALSE        0
#define TRUE         1

typedef struct point{
  long long x, y;
} POINT;

POINT L[MAXLARGE];
int   C[MAXLARGE], N, Nhull;

#ifdef BOUNDINGBOX
long long Xmin,Xmax,Ymin,Ymax;
#endif

void read_points();
void swap(int k, int j);
void maxheapify(int k, int size);
void sort_for_GrahamScan();
void convex_hull();
int cmp_turn(POINT p,POINT q, POINT r);
int turn(POINT p,POINT q, POINT r);
int in_edge_degenerate(long long kx,long long dy, long long ky);
int in_edge(POINT p, int a, int b);
int in_wedge(POINT p, int u, int v, int *below, int *above);
int checkpoint(POINT p);

void read_points(){
  int i;
  for (i=0;i<N;i++)
    scanf("%lli%lli",&L[i].x,&L[i].y);
}
void swap(int k, int j) {
  POINT aux;
  aux = L[k];
  L[k] = L[j];
  L[j] = aux;
}
int cmp_turn(POINT p, POINT q, POINT r) {
  long long aux;
  int t;
  if((t = turn(p,q,r)))
    return t;
  aux = (q.x-p.x)*(r.x-q.x)+(q.y-p.y)*(r.y-q.y);
  if (aux > 0) return 1;
  if (aux < 0) return -1;
  return 0;
}
int turn(POINT p, POINT q, POINT r) {
  long long aux = (q.x-p.x)*(r.y-p.y)-(r.x-p.x)*(q.y-p.y);
  if (aux > 0)  return 1;
  if (aux < 0)  return -1;
  return 0;
}
void maxheapify(int k, int size) {
  int leftson = 2*k, rightson = 2*k+1,  largest = k;
  if (leftson <= size && cmp_turn(L[0],L[largest],L[leftson]) > 0)
    largest = leftson;
  if (rightson <= size && cmp_turn(L[0],L[largest],L[rightson]) > 0)
    largest = rightson;
  if(largest != k) {
    swap(k,largest);
    maxheapify(largest,size);
  }
}
void sort_for_GrahamScan() {
  int  kmin = 0, i, size;
#ifdef BOUNDINGBOX
  Xmin = Xmax = L[0].x;
  Ymin = Ymax = L[0].y;
#endif
  for(i=1; i< N;i++) {
    if (L[i].y < L[kmin].y || (L[i].y == L[kmin].y && L[i].x < L[kmin].x))
      kmin = i;
#ifdef BOUNDINGBOX
    if (L[i].y < Ymin) Ymin = L[i].y;
    else if (L[i].y > Ymax) Ymax = L[i].y;
    if (L[i].x < Xmin)  Xmin = L[i].x;
    else if (L[i].x > Xmax) Xmax = L[i].x;
#endif
  }
  if (kmin != 0)  swap(0,kmin);
  for(i = (N-1)/2; i > 0; i--)
    maxheapify(i,N-1);
  size = N-1;
  while(size > 1) {
    swap(1,size);
    size--;
    maxheapify(1,size);
  }
}
void convex_hull() {
  int i, t;
  C[0] = 0;  C[1] = 1;
  for (i = 2; i < N && turn(L[0],L[1],L[i])==0; i++)
    C[1] = i;
  C[2] = i;
  Nhull = 3;
  for(++i; i < N; i++) {
    while ((t = turn(L[C[Nhull-2]],L[C[Nhull-1]],L[i])) < 0 || t == 0)
      Nhull--;
    C[Nhull++] = i;
  }
  if (turn(L[C[Nhull-2]],L[C[Nhull-1]],L[0]) == 0) Nhull--;
}
int in_edge_degenerate(long long kx,long long dy, long long ky){
  if (kx != 0) return FALSE;
  if (dy < 0) {
    if (ky < 0 && dy < ky) return TRUE;
    return FALSE;
  }
  if (ky > 0 && dy > ky) return TRUE;
  return FALSE;
}
int in_edge(POINT p, int a, int b) {
  long long dx = L[C[b]].x-L[C[a]].x, dy = L[C[b]].y-L[C[a]].y;
  long long kx = p.x -L[C[a]].x,  ky = p.y -L[C[a]].y;
  if (dx == 0) return in_edge_degenerate(kx,dy,ky);
  if (dy == 0) return in_edge_degenerate(ky,dx,kx);
  if (kx*dy != ky*dx) return FALSE;
  if (kx > 0 && dx > kx) return TRUE;
  if (kx < 0 && dx < kx) return TRUE;
  return FALSE;
}
int in_wedge(POINT p, int u, int v, int *left, int *right) {
  *left = turn(L[C[0]],L[C[u]],p);
  *right = turn(L[C[0]],L[C[v]],p);
  if (*left < 0) return FALSE;
  if (*right > 0) return FALSE;
  return TRUE;
}
int checkpoint(POINT p) {
  int  wm, wa, wb, left, right;
  left = turn(L[C[0]],L[C[Nhull-1]],p);
  if (left > 0) return FALSE;
  if (left == 0) return in_edge(p,0,Nhull-1);
  right = turn(L[C[0]],L[C[1]],p);
  if (right < 0) return FALSE;
  if (right == 0) return in_edge(p,0,1);
  wa = 1; wb = Nhull-2;
  while (wa <= wb) {
    wm = (wa+wb)/2;
    if (in_wedge(p,wm,wm+1,&left,&right)) {
      if (turn(L[C[wm]],L[C[wm+1]],p) < 0)
      	return FALSE;
      return TRUE;
    }
    if (right > 0)
      wa = wm+1;
    else
      wb = wm-1;
  }
  return FALSE;
}
int main() {
  int m, count = 0;
  POINT p;
  scanf("%d",&N);
  read_points();
  sort_for_GrahamScan();
  convex_hull();
  scanf("%d",&m);
  while(m-- > 0) {
    scanf("%lli%lli",&p.x,&p.y);
#ifdef BOUNDINGBOX
    if (p.x >= Xmin && p.x <= Xmax && p.y >= Ymin && p.y <= Ymax)
      count += checkpoint(p);
#endif
#ifndef BOUNDINGBOX
    count += checkpoint(p);
#endif
  }
  printf("%d\n",count);
  return 0;
}






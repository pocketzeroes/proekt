#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
enum{ N = 100010};
typedef struct nodeS{
  int a, b;
  int*data;
  int dataSz;
  struct nodeS*lf;
  struct nodeS*rg;
}node;
node*newNode(int _a, int _b){
  node*rez=malloc(sizeof(node));
  rez->a      = _a  ;
  rez->b      = _b  ;
  rez->lf     = NULL;
  rez->rg     = NULL;
  rez->data   = NULL;
  rez->dataSz = 0   ;
  return rez;
}
typedef struct pointS {
  long long x, y;
}point;
point newPoint(long long _x, long long _y){
  point rez;
  rez.x=_x;
  rez.y=_y;
  return rez;
}
long long dis(point pt){
  return pt.x*pt.x + pt.y*pt.y;
}
node*head;
point P[N];
int*V=NULL;int VSz=0;
int idx[N];
int n, k;
int isleft(point p1, point p2, point p3) {
  int rv = 0;
  rv = (p2.x - p1.x) * (p3.y - p1.y) < (p3.x - p1.x) * (p2.y - p1.y);
  return rv;
}
int cmpSlope(point p1, point p2, point q1, point q2) {
  return (p1.y - p2.y) * (q1.x - q2.x) > (q1.y - q2.y) * (p1.x - p2.x);
}
node*init(int a, int b){
  node*p = newNode(a, b);
  if(a < b){
    int mid = (a + b) / 2;
    p->lf = init(a, mid);
    p->rg = init(mid+1, b);
  }
  for(int i = a;i <= b;i++){
    while(p->dataSz >= 2){
      point pp = P[ p->data [p->dataSz - 1]];
      point qq = P[ p->data [p->dataSz - 2]];
      if(isleft(pp, P[V[i]], qq)){
        --p->dataSz;
      }
      else{
        break;
      }
    }
    p->data = pushback(p->data, &p->dataSz, V[i]);
  }
  return p;
}
int query(node *p, int l, int r, point p1, point p2){
  int rv=0;
  int r1=0;
  int r2=0;
  if(r < p->a || p->b < l) {
    return 0;
  }
  if(l <= p->a && p->b <= r) {
    int*v = p->data;
    int a = 0, b = p->dataSz - 1;
    while(a < b) {
      int mid = (a + b) / 2;
      if(cmpSlope(P[v[mid]], P[v[mid+1]], p1, p2)) {
        b = mid;
      }
      else {
        a = mid + 1;
      }
    }
    int index=v[a];
    point pc = P[index];
    return isleft(p2, pc, p1);
  }
  return  query(p->lf, l, r, p1, p2) ||
          query(p->rg, l, r, p1, p2);
}
int lambda(const void*pa,const void*pb){
  int*pid1=(int*)pa;
  int*pid2=(int*)pb;
  int id1= *pid1;
  int id2= *pid2;
  int r1 = isleft(newPoint(0ll, 0ll), P[id1], P[id2]);
  int r2 = isleft(newPoint(0ll, 0ll), P[id2], P[id1]);
  if(r1 == 0 && r2 == 0) {
    return dis(P[id1]) < dis(P[id2])?-1:1;
  }
  else
    return r1?-1:1;;
}
void printarr(int*arr,int sz){
    for( int i=0;i<sz;i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
  scanf("%d%d", &n, &k);
  for(int i = 0;i < n;i++) {
    scanf("%lld %lld", &P[i].x, &P[i].y);
    idx[i] = i;
  }
  qsort(idx, n, sizeof(int), lambda);
  for(int i = 0;i < n;i++) {
    if(i == 0 || isleft(newPoint(0ll, 0ll), P[idx[i-1]], P[idx[i]]))
      V=pushback(V,&VSz,idx[i]);
  }
  head = init(0, VSz-1);
  for(int i = 0;i < k;i++) {
    point p1, p2, tt;
    scanf("%lld %lld", &p1.x, &p1.y);
    scanf("%lld %lld", &p2.x, &p2.y);
    if(!isleft(newPoint(0ll, 0ll), p1, p2)){
        memcpy( &tt, &p1, sizeof(point));
        memcpy( &p1, &p2, sizeof(point));
        memcpy( &p2, &tt, sizeof(point));
    }
    if(isleft(newPoint(0ll, 0ll), p2, P[V[0]]))
      printf("N\n");
    else if(isleft(newPoint(0ll, 0ll), P[V[VSz-1]], p1))
      printf("N\n");
    else {
      int a = 0, b = VSz - 1;
      while(a < b) {
        int mid = (a + b) / 2;
        if(isleft(newPoint(0ll, 0ll), P[V[mid]], p1))
          a = mid + 1;
        else
          b = mid;
      }
      int l = a;
      a = 0,b = VSz - 1;
      while(a < b) {
        int mid = (a + b) / 2 + 1;
        if(!isleft(newPoint(0ll, 0ll), p2, P[V[mid]]))
          a = mid;
        else
          b = mid - 1;
      }
      int r = a;
      if(l <= r)
        printf("%c\n", query(head, l, r, p1, p2) ? 'Y' : 'N');
      else
        printf("N\n");
    }
  }
  return 0;
}










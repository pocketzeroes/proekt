#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;

typedef struct{
  int first,
      second,
      third;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpTr(const void*pb, const void*pa){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third )return(a->third  < b->third )?-1:1;
  return 0;
}
///////////////////
enum{ N=100010,inf=1000000010};
int Case,n,cl,ce,cp,i,j,k,xmi,xma,ymi,yma,ama,ami,sma,smi;
vect ans;//of trip

struct Rect{
  int xl,xr,yl,yr;
}rect[N];
typedef struct{
  int x1, y1, x2, y2;
}Line;
Line a[N<<2],b[N<<2];

Line fix(Line l){
  if(l.x1 > l.x2){
    swap(l.x1, l.x2);
    swap(l.y1, l.y2);
  }
  if(l.x1==l.x2 && l.y1>l.y2)
    swap(l.y1, l.y2);
  return l;
}
Line newLine(int a, int b, int c, int d){
  return fix((Line){a, b, c, d});
}

int cmpl(const void*pa, const void*pb){
  Line*a=(Line*)pa;
  Line*b=(Line*)pb;
  if(a->x1!=b->x1) return(a->x1 < b->x1)?-1:1;
  if(a->y1!=b->y1) return(a->y1 < b->y1)?-1:1;
  if(a->x2!=b->x2) return(a->x2 < b->x2)?-1:1;
  return(a->y2 < b->y2)?-1:1;
}
typedef struct{
  int x, y, t;
}E;
E e[N<<2];

E newE(int a, int b, int c){
  return(E){a,b,c};
}

typedef struct{
  int l,r;
}P;
P pool[N];
P newP(int a, int b){
  return(P){a,b};
}


int cmpe(const void*pa, const void*pb){
  E*a=(E*)pa;
  E*b=(E*)pb;
  if(a->x != b->x)
    return(a->x<b->x)?-1:1;
  return(a->y<b->y)?-1:1;
}
inline void umin(int*a, int b){
  *a > b?(*a=b):0;
}
inline void umax(int*a, int b){
  *a < b ? (*a = b):0;
}


void solve(int l, int r){
  int i,j,s=0,L=-inf,R=-inf;
  for(cp=0,i=l;i<=r;i=j){
    if(s==1)
      R=e[i].y;
    else{
      if(L<R)
        pool[++cp] = newP(L, R);
      L=e[i].y;
    }
    for(j=i;j<=r&&e[i].y==e[j].y;j++)
      s+=e[j].t;
  }
  if(L<R)
    pool[++cp] = newP(L, R);
}
void check(ll A, ll B, ll C){
  int i,d=A*A+B*B;
  ll x, y, X, Y;
  for(i=1; i<=cl; i++){
    x=a[i].x1,
    y=a[i].y1;
    X=2*A*(A*x+B*y-C),
    Y=2*B*(A*x+B*y-C);
    if(X%d||Y%d)
      return;
    b[i].x1=x-X/d,
    b[i].y1=y-Y/d;
    x=a[i].x2,
    y=a[i].y2;
    X=2*A*(A*x+B*y-C),
    Y=2*B*(A*x+B*y-C);
    if(X%d||Y%d)
      return;
    b[i].x2=x-X/d,
    b[i].y2=y-Y/d;
    b[i] = fix(b[i]);
  }
  qsort(b+1, cl, sizeof(Line), cmpl);
  for(i=1; i<=cl; i++){
    if(a[i].x1!=b[i].x1)
      return;
    if(a[i].y1!=b[i].y1)
      return;
    if(a[i].x2!=b[i].x2)
      return;
    if(a[i].y2!=b[i].y2)
      return;
  }
  if(C%2==0)
    C/=2;
  else
    A*=2,B*=2;
  pbt(ans, newtrip(A, B, C));
}
void up(int x, int y){
  umax(&xma, x);
  umin(&xmi, x);
  umax(&yma, y);
  umin(&ymi, y);
  umax(&ama, x+y);
  umin(&ami, x+y);
  umax(&sma, x-y);
  umin(&smi, x-y);
}
int main(){
  scanf("%d", &Case);
  while(Case--){
    scanf("%d", &n);
    cl=0;
    xma=yma=ama=sma=-inf;
    xmi=ymi=ami=smi=inf;
    for(i=1;i<=n;i++){
      scanf("%d %d %d %d", &rect[i].xl, &rect[i].yl, &rect[i].xr, &rect[i].yr);
      rect[i].xl*=2;
      rect[i].yl*=2;
      rect[i].xr*=2;
      rect[i].yr*=2;
      up(rect[i].xl, rect[i].yl);
      up(rect[i].xl, rect[i].yr);
      up(rect[i].xr, rect[i].yl);
      up(rect[i].xr, rect[i].yr);
    }
    ce=0;
    for(i=1;i<=n;i++){
      e[++ce]=newE(rect[i].xl, rect[i].yl, 1);
      e[++ce]=newE(rect[i].xl, rect[i].yr,-1);
      e[++ce]=newE(rect[i].xr, rect[i].yl, 1);
      e[++ce]=newE(rect[i].xr, rect[i].yr,-1);
    }
    qsort(e+1, ce, sizeof(E), cmpe);
    for(i=1;i<=ce;i=j){
      for(j=i;j<=ce&&e[i].x==e[j].x;j++);
      solve(i,j-1);
      for(k=1;k<=cp;k++)
        a[++cl] = newLine(e[i].x,pool[k].l,e[i].x,pool[k].r);
    }
    ce=0;
    for(i=1;i<=n;i++){
      e[++ce]=newE(rect[i].yl,rect[i].xl,1);
      e[++ce]=newE(rect[i].yl,rect[i].xr,-1);
      e[++ce]=newE(rect[i].yr,rect[i].xl,1);
      e[++ce]=newE(rect[i].yr,rect[i].xr,-1);
    }
    qsort(e+1, ce, sizeof(E), cmpe);
    for(i=1;i<=ce;i=j){
      for(j=i;j<=ce&&e[i].x==e[j].x;j++);
      solve(i,j-1);
      for(k=1;k<=cp;k++)
        a[++cl]=newLine(pool[k].l,e[i].x,pool[k].r,e[i].x);
    }
    qsort(a+1, cl, sizeof(Line), cmpl);
    ans.sz=0;
    check(1, 1,(ami+ama)/2);
    check(1, 0,(xmi+xma)/2);
    check(1,-1,(smi+sma)/2);
    check(0, 1,(ymi+yma)/2);
    printf("%d\n", ans.sz);
    qsort(ans.ptr, ans.sz, sizeof(trip), cmpTr);//rev
    for(i=0; i<ans.sz; i++)
      printf("%d %d %d ", ans.ptr[i].first, ans.ptr[i].second, ans.ptr[i].third);
    puts("");
  }
  return 0;
}

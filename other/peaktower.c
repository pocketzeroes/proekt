/*
Official time limit 2s
kattis TLE >1s
*/
#pragma GCC optimize "-O4"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define STB_(prefix,name)     stb__##prefix##name
#define stb_define_sort(FUNCNAME,TYPE,COMPARE) \
                       stb__define_sort(       void, FUNCNAME,TYPE,COMPARE)

#define stb__define_sort(MODE, FUNCNAME, TYPE, COMPARE)                       \
                                                                              \
static void STB_(FUNCNAME,_ins_sort)(TYPE *p, int n)                          \
{                                                                             \
   int i,j;                                                                   \
   for (i=1; i < n; ++i) {                                                    \
      TYPE t = p[i], *a = &t;                                                 \
      j = i;                                                                  \
      while (j > 0) {                                                         \
         TYPE *b = &p[j-1];                                                   \
         int c = COMPARE;                                                     \
         if (!c) break;                                                       \
         p[j] = p[j-1];                                                       \
         --j;                                                                 \
      }                                                                       \
      if (i != j)                                                             \
         p[j] = t;                                                            \
   }                                                                          \
}                                                                             \
                                                                              \
static void STB_(FUNCNAME,_quicksort)(TYPE *p, int n)                         \
{                                                                             \
   while (n > 12) {                                                           \
      TYPE *a,*b,t;                                                           \
      int c01,c12,c,m,i,j;                                                    \
      m = n >> 1;                                                             \
      a = &p[0];                                                              \
      b = &p[m];                                                              \
      c = COMPARE;                                                            \
      c01 = c;                                                                \
      a = &p[m];                                                              \
      b = &p[n-1];                                                            \
      c = COMPARE;                                                            \
      c12 = c;                                                                \
      if (c01 != c12) {                                                       \
         int z;                                                               \
         a = &p[0];                                                           \
         b = &p[n-1];                                                         \
         c = COMPARE;                                                         \
         z = (c == c12) ? 0 : n-1;                                            \
         t = p[z];                                                            \
         p[z] = p[m];                                                         \
         p[m] = t;                                                            \
      }                                                                       \
      t = p[0];                                                               \
      p[0] = p[m];                                                            \
      p[m] = t;                                                               \
      i=1;                                                                    \
      j=n-1;                                                                  \
      for(;;) {                                                               \
         b = &p[0];                                                           \
         for (;;++i) {                                                        \
            a=&p[i];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         a = &p[0];                                                           \
         for (;;--j) {                                                        \
            b=&p[j];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         if (i >= j) break;                                                   \
         t = p[i];                                                            \
         p[i] = p[j];                                                         \
         p[j] = t;                                                            \
         ++i;                                                                 \
         --j;                                                                 \
      }                                                                       \
      if (j < (n-i)) {                                                        \
         STB_(FUNCNAME,_quicksort)(p,j);                                       \
         p = p+i;                                                             \
         n = n-i;                                                             \
      } else {                                                                \
         STB_(FUNCNAME,_quicksort)(p+i, n-i);                                  \
         n = j;                                                               \
      }                                                                       \
   }                                                                          \
}                                                                             \
                                                                              \
MODE FUNCNAME(TYPE *p, int n)                                                 \
{                                                                             \
  STB_(FUNCNAME, _quicksort)(p, n);                                           \
  STB_(FUNCNAME, _ins_sort)(p, n);                                            \
}



inline double min(double a, double b){return a<b?a:b;}
inline double max(double a, double b){return a>b?a:b;}

stb_define_sort(sort_dbl, double, *a < *b)


enum{ N=2000};
#define eps 1e-9
double W,H,E,ans=1e9;
int n,i,j;

typedef struct{
  double w, h, sx, sy, vx, vy;
}Rec;
Rec a[N];

inline int sgn(double x){
  if(x<-eps)
    return -1;
  if(x>eps)
    return 1;
  return 0;
}
int m,cnt;
double vipy[N];
int cov[N];
double ct[1000000];
int cntt;

typedef struct Ev{
  double x,l,r;
  int p;
}Ev;
Ev e[N];

stb_define_sort(sort_ev, Ev, a->x < b->x)

Ev newEv(double _x, double _l, double _r, int _p){
  Ev rez;
  rez.x=_x;
  rez.l=_l;
  rez.r=_r;
  rez.p=_p;
  return rez;
}

double cal(double Time){
  int i,j;
  m=0;
  for(i=1;i<=n;i++){
    double xl=a[i].sx+a[i].vx*Time,
           xr=xl+a[i].w,
           yl=a[i].sy+a[i].vy*Time,
           yr=yl+a[i].h;
    xl=min(max(xl,0.0),W);
    xr=min(max(xr,0.0),W);
    yl=min(max(yl,0.0),H);
    yr=min(max(yr,0.0),H);
    if(xl+eps>xr||yl+eps>yr)
      continue;
    vipy[++m]=yl;
    e[m] = newEv(xl,yl,yr,1);
    vipy[++m]=yr;
    e[m] = newEv(xr,yl,yr,-1);
  }
  double ret=0;
  if(!m){
    ans=0;
    return 0;
  }
  sort_dbl(vipy+1, m);
  sort_ev(e+1, m);
  for(i=1;i<m;i++)cov[i]=0;
  for(i=1;i<=m;i++){
    if(i>1){
      for(j=1;j<m;j++){
        if(cov[j]>0)
          ret+=(vipy[j+1]-vipy[j])*(e[i].x-e[i-1].x);
      }
    }
    if(ret>ans)
      return ret;
    double l=e[i].l,r=e[i].r;
    for(j=1;j<m;j++){
      double A=vipy[j],B=vipy[j+1];
      if(sgn(A-l)>=0&&sgn(B-r)<=0){
        cov[j]+=e[i].p;
      }
    }
  }
  ans=min(ans,ret);
  return ret;
}
inline bool check(double Time){
  if(Time<-eps||Time>E+eps)
    return 0;
  return 1;
}
void deal(double A, double B, double C, double D){
  A-=C;
  B-=D;
  A=-A;
  if(!sgn(B))
    return;
  if(check(A/B))
    ct[++cntt]=A/B;
}
void search(double l, double r){
  cal(r);
  double m1,m2,s1,s2;
  int step=0;
  while(l+1e-5<r&&step++<10){
    m1=l+(r-l)/3.0;
    m2=r-(r-l)/3.0;
    s1=cal(m1);
    s2=cal(m2);
    if(s1<s2)
      r=m2-eps;
    else
      l=m1+eps;
  }
}
int main(){
  scanf("%d %lf %lf %lf", &n, &W, &H, &E);
  for(i=1; i<=n; i++)
    scanf("%lf %lf %lf %lf %lf %lf", &a[i].w, &a[i].h, &a[i].sx, &a[i].sy, &a[i].vx, &a[i].vy);
  ct[++cntt] = 0;
  ct[++cntt] = E;
  a[n+1].w = W;
  a[n+1].h = H;
  for(i=1; i<=n+1; i++)
    for(j=i+1; j<=n+1; j++){
      deal(a[i].sx       , a[i].vx,a[j].sx       , a[j].vx);
      deal(a[i].sx+a[i].w, a[i].vx,a[j].sx       , a[j].vx);
      deal(a[i].sx       , a[i].vx,a[j].sx+a[j].w, a[j].vx);
      deal(a[i].sx+a[i].w, a[i].vx,a[j].sx+a[j].w, a[j].vx);
      deal(a[i].sy       , a[i].vy,a[j].sy       , a[j].vy);
      deal(a[i].sy+a[i].h, a[i].vy,a[j].sy       , a[j].vy);
      deal(a[i].sy       , a[i].vy,a[j].sy+a[j].h, a[j].vy);
      deal(a[i].sy+a[i].h, a[i].vy,a[j].sy+a[j].h, a[j].vy);
    }
  sort_dbl(ct+1, cntt);
  cal(0);
  for(i=1; i<=cntt; i++)
    if(ct[i]>ct[i-1]+eps){
      search(ct[i-1], ct[i]);
    }
  printf("%.10f", ans);
  return 0;
}

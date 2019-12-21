#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=260,
      M=N*2};
const double inf=1e20,
             eps=1e-9;
int _,n,i,j,k,x,y,X,ret,cnt[N],cg;
double vy,ma,l,r,vl,vr;

typedef struct P{
  int x,y,p;
}P;
P a[N];
typedef struct E{
  double l,r;
  int f;
}E;
E f[N][M],g[N*M],h[N*M];
E newE(double l, double r, int f){
  return(E){l, r, f};
}

int cmp(const void*pa, const void*pb){
  P*a=(P*)pa;
  P*b=(P*)pb;
  return(a->y==b->y?a->p<b->p:a->y<b->y)?-1:1;
}
int cmpE(const void*pa, const void*pb){
  E*a=(E*)pa;
  E*b=(E*)pb;
  return(a->l<b->l)?-1:1;
}
void NO(){
  puts("Cannot visit any targets");
  exit(0);
}
inline int sgn(double x){
  if(x>eps)
    return 1;
  if(x<-eps)
    return -1;
  return 0;
}
void cal(int dy, int d, double L, double R){
  if(!dy){
    if(d){
      l=inf,
      r=-inf;
      return;
    }
    l=L,
    r=R;
    return;
  }
  double t=dy/vy;
  L = fmax(L,1.0*d/t-ma*t/2);
  R = fmin(R,1.0*d/t+ma*t/2);
  if(sgn(L-R)>=0){
    l=inf,
    r=-inf;
    return;
  }
  double A=ma,B=-2.0*ma*t,C=0.5*ma*t*t+L*t-d;
  double x=(-B-sqrt(fmax(B*B-4.0*A*C,0.0)))/(A*2.0);
  r=L-ma*x+ma*(t-x);
  A=-ma,B=2.0*ma*t,C=-0.5*ma*t*t+R*t-d;
  x=(-B+sqrt(fmax(B*B-4.0*A*C,0.0)))/(A*2.0);
  l=R+ma*x-ma*(t-x);
}
void merge(){
  static int c[N],l[N],r[N];
  int i;
  for(i=0;i<=n;i++)
    c[i]=0;
  for(i=1;i<=cg;i++)
    c[n-g[i].f]++;
  l[0]=1,r[0]=c[0];
  for(i=1;i<=n;i++)
    l[i]=c[i-1]+1,r[i]=c[i]+=c[i-1];
  for(i=1;i<=cg;i++)
    h[c[n-g[i].f]--]=g[i];
  for(i=0;i<=n;i++)
    if(l[i]<r[i])
      qsort(h+l[i], r[i]-l[i]+1, sizeof(E), cmpE);
  int m=1;
  for(i=2;i<=cg;i++){
    if(h[i].f==h[m].f&&sgn(h[m].r-h[i].l)>=0)
      h[m].r=fmax(h[m].r,h[i].r);
    else
      h[++m]=h[i];
  }
  cg=m;
}
void go(int x){
  int Y,Z=n+1,i,j,k;
  for(i=n;i>X;i--){
    if(a[i].p<Z){
      bool flag=0;
      for(j=1;j<=cnt[i];j++)
        if(f[i][j].f==x-1)
          for(k=1;k<=cg;k++){
            cal(a[i].y-a[X].y,a[i].x-a[X].x,g[k].l,g[k].r);
            l=fmax(l,f[i][j].l);
            r=fmin(r,f[i][j].r);
            if(sgn(l-r)>=0)
              continue;
            flag=1;
            break;
          }
      if(flag)
        Y=i,Z=a[i].p;
    }
  }
  printf("%d",Z);
  if(x>1)
    putchar(' ');
  int m=0;
  for(j=1;j<=cnt[Y];j++)
    if(f[Y][j].f==x-1)
      for(k=1;k<=cg;k++){
        cal(a[Y].y-a[X].y,a[Y].x-a[X].x,g[k].l,g[k].r);
        l=fmax(l,f[Y][j].l);
        r=fmin(r,f[Y][j].r);
        if(sgn(l-r)>=0)
          continue;
        h[++m] = newE(l,r,0);
      }
  for(i=1; i<=m; i++)
    g[i]=h[i];
  cg=m;
  X=Y;
}
int main(){
  scanf("%d %lf %lf", &_, &vy, &ma);
  while(_--){
    scanf("%d %d", &x, &y);
    if(y<0)
      continue;
    a[++n].x=x;
    a[n].y=y;
  }
  if(!n)
    NO();
  for(i=1;i<=n;i++)
    a[i].p=i;
  qsort(a, n+1, sizeof(P), cmp);
  if(ma<0.5){
    for(_=0,i=1;i<=n;i++)
      if(a[i].x==0){
        if(_++)
          putchar(' ');
        printf("%d",a[i].p);
      }
    if(!_)
      NO();
    return 0;
  }
  for(i=n;~i;i--){
    g[cg=1] = newE(-inf,inf,0);
    for(j=n;j>i;j--)
      for(k=1;k<=cnt[j];k++){
        cal(a[j].y-a[i].y,a[j].x-a[i].x,f[j][k].l,f[j][k].r);
        if(sgn(l-r)>=0)
          continue;
        g[++cg]=newE(l,r,f[j][k].f+1);
      }
    merge();
    for(j=1;j<=cg;j++)
      f[i][j]=h[j];
    cnt[i]=cg;
  }
  for(i=1;i<=cnt[0];i++)
    if(f[0][i].l<eps&&f[0][i].r>-eps&&f[0][i].f){
      ret=f[0][i].f;
      break;
    }
  if(!ret)
    NO();
  g[cg=1]=newE(-eps,eps,0);
  for(i=ret;i;i--)
    go(i);
  return 0;
}

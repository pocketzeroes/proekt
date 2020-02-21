#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>



int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
#define pb(zpv, zvv) zpv.ptr = pushbackD(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double *pushbackD(double *array, int *size, double value) {
  double *output = resizeArray(array, double, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  double*ptr;
  int sz;
}vecd;
vecd newVecD(){
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int lowerbound(double*a, int n, double x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(x <= a[mid])
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
////////////////////////////////------------------------------------------------

int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
enum{MAXN = 2000};
int n;
double W, H, E, w[MAXN],h[MAXN],sx[MAXN],vx[MAXN],sy[MAXN],vy[MAXN];
const double eps = 1e-8;
vecd v;

void pre(int n){
    pb(v, 0.);
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            if(fabs(vx[j]-vx[i])>eps){
                double tt=(sx[i]-sx[j])/(vx[j]-vx[i]);
                if(tt>0 && tt<E)
                   pb(v, tt);
            }
            if(fabs(vy[j]-vy[i])>eps){
                double tt=(sy[i]-sy[j])/(vy[j]-vy[i]);
                if(tt>0 && tt<E)
                   pb(v, tt);
            }
        }
    }
    pb(v, E);
}
//namespace Rect_Union{
typedef struct{
    double x1,x2,y;
    int flag;
}data;
data   a   [3000];
    double Hash[3000];
    double sum[3000];
    int col[3000];

int cp(const void*pa, const void*pb){
    data*a=(data*)pa;
    data*b=(data*)pb;
    return(a->y < b->y)?-1:1;
    }
    void pushup(int size,int l,int r){
        if(col[size])
            sum[size]=Hash[r+1]-Hash[l];
        else if(l==r)
            sum[size]=0;
        else
            sum[size]=sum[size*2]+sum[size*2+1];
    }
    void update(int L,int R,int flag,int l,int r,int size){
        if(L<=l&&R>=r){
            col[size]+=flag;
            pushup(size,l,r);
            return;
        }
        int m=(l+r)/2;
        if(L<=m)
            update(L,R,flag,l,m,size*2);
        if(R>m)
            update(L,R,flag,m+1,r,size*2+1);
        pushup(size,l,r);
    }
    double work(double t,int n) {
        double x1,y1,x2,y2;
        int cnt=0;
        for(int i=1;i<=n;i++){
            x1=sx[i]+ t* vx[i];
            y1=sy[i]+ t* vy[i];
            x2=x1+w[i];
            y2=y1+h[i];
            x1=fmax(x1,0.),x2=fmin(x2,W);
            x2=fmax(x2,0.),x1=fmin(x1,W);
            y1=fmax(y1,0.),y2=fmin(y2,H);
            y2=fmax(y2,0.),y1=fmin(y1,H);
            if(x1>=x2 || y1>=y2)
                continue;
            ++cnt;
            a[2*cnt-1].x1=a[2*cnt].x1=x1;
            a[2*cnt-1].x2=a[2*cnt].x2=x2;
            a[2*cnt-1].y=y1;a[2*cnt].y=y2;
            a[2*cnt-1].flag=1;a[2*cnt].flag=-1;
            Hash[2*cnt-1]=x1;Hash[2*cnt]=x2;
        }
        qsort(a   +1, 2*cnt, sizeof(data), cp);
        qsort(Hash+1, 2*cnt, sizeof(double), cmpDbl);
        memset(col,0,sizeof(col));
        memset(sum,0,sizeof(sum));
        double ans=0;
        for(int i=1;i<=2*cnt;i++){
            int l = lowerbound(Hash+1, 2*cnt, a[i].x1)+1;
            int r = lowerbound(Hash+1, 2*cnt, a[i].x2);
            if(l<=r)
                update(l,r,a[i].flag,1,2*cnt,1);
            ans+=sum[1]*(a[i+1].y-a[i].y);
        }
        return ans;
    }
//};
int main(){
    n = read();
    scanf("%lf %lf %lf", &W, &H, &E);
    for(int i=1; i<=n; i++)
        scanf("%lf %lf %lf %lf %lf %lf", &w[i], &h[i], &sx[i], &sy[i], &vx[i], &vy[i]);
    for(int i=n+1; i<=2*n; i++){
        sx[i] = sx[i-n]+w[i-n];
        vx[i] = vx[i-n];
        sy[i] = sy[i-n]+h[i-n];
        vy[i] = vy[i-n];
    }
    sx[n*2+1]=0,vx[n*2+1]=0;
    sy[n*2+1]=0,vx[n*2+1]=0;
    sx[n*2+2]=W,vy[n*2+2]=0;
    sy[n*2+2]=H,vy[n*2+2]=0;
    pre(n*2+2);
    double ans = work(0,n);
    qsort(v.ptr, v.sz, sizeof(double), cmpDbl);
    for(int z=0;z<v.sz;z++){double t = v.ptr[z];
        double p = work(t, n);
        ans = fmin(ans, p);
    }
    for(double t=0; t<=E; t+=0.01){
        double p = work(t,n);
        ans = fmin(ans, p);
    }
    printf("%.10lf\n", ans);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}



int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}






typedef long long ll;
typedef unsigned long long ull;
ll gcd(ll a,ll b) {
    return b==0?a:gcd(b,a%b);
}
enum { MAXN=100000};
typedef struct P {
    int x,y;
} P;
typedef struct R {
    int lx,ly,hx,hy;
} R;
typedef struct E {
    int x,ly,hy,idx,by;
} E;
int cmpE(const void*pa, const void*pb){//(const E &a,const E &b) {
    E*a=(E*)pa;
    E*b=(E*)pb;
    return (a->x < b->x)?-1:1;
}
int n;
P p[MAXN];
R r[MAXN];
E e[2*MAXN];
int ne;
int xx[MAXN],nxx;
int yy[MAXN],nyy;
pair*ax[MAXN];int sz1[MAXN];
pair*ay[MAXN];int sz2[MAXN];
int cnt[MAXN];
int bit[MAXN+1];



int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
void bmod(int idx) {
    ++idx;
    while(idx<=nyy) {
        bit[idx]++;
        idx+=idx&-idx;
    }
}
int bget(int idx) {
    ++idx;
    int ret=0;
    while(idx>0) {
        ret+=bit[idx];
        idx-=idx&-idx;
    }
    return ret;
}
int calc(int ly,int hy) {
    return bget(hy)-bget(ly-1);
}
int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
void run() {
    scanf("%d",&n);
    for(int i=(0); i<(n); ++i)
        scanf("%d%d",&p[i].x,&p[i].y);
    nxx=0;
    for(int i=(0); i<(n); ++i)
        xx[nxx++]=p[i].x;
    qsort(xx, nxx,sizeof(int),cmp);
    nxx=unique(xx,  nxx) ;
    for(int i=(0); i<(n); ++i)
        p[i].x=lower_bound(xx, nxx,p[i].x);
    nyy=0;
    for(int i=(0); i<(n); ++i)
        yy[nyy++]=p[i].y;
    qsort(yy, nyy, sizeof(int), cmp);
    nyy=unique(yy, nyy) ;
    for(int i=(0); i<(n); ++i)
        p[i].y=lower_bound(yy, nyy,p[i].y);
    for(int i=(0); i<(nxx); ++i)
        sz2[i]=0;//.clear();
    for(int i=(0); i<(n); ++i){
        int index=p[i].x;
        ay[index]=pushbackP(ay[index], sz2+index, newPair(p[i].y,i));
    }
    for(int i=(0); i<(nxx); ++i)
        qsort(ay[i], sz2[i],sizeof(pair), cmpP );
    for(int i=(0); i<(nyy); ++i)
        sz1[i]=0;//.clear();
    for(int i=(0); i<(n); ++i){
        int index=p[i].y;
        ax[index]=pushbackP(ax[index], sz1+index, newPair(p[i].x,i));
    }
    for(int i=(0); i<(nyy); ++i)
        qsort(ax[i] ,sz1[i], sizeof(pair),cmpP );
    for(int i=(0); i<(nxx); ++i){
        for(int j=(0); j < sz2[i]; ++j) {
            int idx=ay[i][j].second;
            r[idx].ly=j==0?0:ay[i][j-1].first+1;
            r[idx].hy=j+1>= sz2[i] ? nyy-1:ay[i][j+1].first-1;
        }
    }
    for(int i=(0); i<(nyy); ++i){
        for(int j=(0); j < sz1[i]; ++j) {
            int idx=ax[i][j].second;
            r[idx].lx=j==0?0:(ax[i][j-1].first+1);
            r[idx].hx=j+1 >= sz1[i] ? nxx-1:ax[i][j+1].first-1;
        }
    }
    ne=0;
    for(int i=(0); i<(n); ++i)
        e[ne].x=r[i].lx-1,e[ne].ly=r[i].ly,e[ne].hy=r[i].hy,e[ne].idx=i,e[ne].by=-1,++ne;
    for(int i=(0); i<(n); ++i)
        e[ne].x=r[i].hx,e[ne].ly=r[i].ly,e[ne].hy=r[i].hy,e[ne].idx=i,e[ne].by=+1,++ne;
    qsort(e, ne,sizeof(E),cmpE);
    int at=0;
    memset(cnt,0,sizeof(cnt));
    memset(bit,0,sizeof(bit));
    for(int x=(0); x<=(nxx); ++x) {
        while(at<ne&&e[at].x<x)
            cnt[e[at].idx]+=e[at].by*calc(e[at].ly,e[at].hy),++at;
        if(x<nxx)
            for(int j=(0); j <  sz2[x] ; ++j)
                bmod(ay[x][j].first);
    }
    bool ok=true;
    for(int i=(0); i<(n); ++i)
        if(cnt[i]!=1)
            ok=false;
    printf("%d\n",ok?1:0);
}
int main() {
    int n;
    scanf("%d",&n);
    for(int i=(1); i<=(n); ++i) 
        run();
    return 0;
}
























































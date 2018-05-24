#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef long long ll;
enum{ MAXN=1<<19};
enum{ MAXK=19   };
int n,nq,k;
int p   [MAXN];
int wins[MAXN];
int best[2*MAXN-1];
int off [MAXK+2];
int cur [MAXN],tmp[MAXN];

void merge(int *a,int na,int *b,int nb,int *c){
    int ntmp=0,ai=0,bi=0;
    while(ai<na||bi<nb) {
        if(ai<na&&(bi>=nb||a[ai]>b[bi])) tmp[ntmp++]=a[ai++]; else tmp[ntmp++]=b[bi++];
    }
    for(int i=(0);i<(ntmp);++i) c[i]=tmp[i];
}
bool can(int x,int w,int mxswap){
    if(w>k) return false;
    if(w==k) return x==n-1;
    if(x<(1<<w)-1) return false;
    if(mxswap>=(1<<w)-1) return true;
    return best[off[w]+mxswap]<=x;
}
int solve(int x,int mxswap){
    if(mxswap==0) return wins[x];
    for(int ret=1;;++ret) if(!can(x,ret,mxswap)) return ret-1;
}
int main(){
    scanf("%d%d",&n,&nq);
    k=2; while((1<<k)!=n) ++k; assert((1<<k)==n);
    for(int i=(0);i<(n);++i) scanf("%d",&p[i]);
    off[0]=0; for(int i=(0);i<=(k);++i) off[i+1]=off[i]+(1<<i);
    for(int i=(0);i<=(k);++i) for(int j=(0);j<(1<<i);++j) best[off[i]+j]=INT_MAX;
    for(int i=(0);i<(n);++i) cur[i]=p[i];
    for(int i=(0);i<=(k);++i) {
        for(int pos=0;pos<n;pos+=(1<<i)) for(int j=(0);j<(1<<i);++j) best[off[i]+j]=min(best[off[i]+j],cur[pos+j]);
        if(i==k) break;
        for(int pos=0;pos<n;pos+=(2<<i)) merge(cur+pos,(1<<i),cur+pos+(1<<i),(1<<i),cur+pos);
    }
    for(int i=(0);i<(n);++i) wins[i]=0;
    for(int i=(0);i<(n);++i) cur[i]=p[i];
    for(int i=k;i>=1;--i) {
        for(int j=(0);j<(1<<(i-1));++j) {
            int a=cur[2*j+0],b=cur[2*j+1];
            if(a<b)
                swap(a, b);
            ++wins[a];
            cur[j]=a;
        }
    }
    int last=0;
    for(int qi=(0);qi<(nq);++qi) {
        int x,y; scanf("%d%d",&x,&y); x=(x+last)%n; y=(y+last)%n;
        int ans=solve(x,y);
        printf("%d\n",ans);
        last=ans;
    }
}




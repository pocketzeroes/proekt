#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=100009};
enum{ INF=1000000000};
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef pair P;

typedef struct{
  pair first;
  int second;
}PP;
PP newPP(pair a, int b){
  return(PP){a,b};
}

int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
int cmpPP(const void*pa, const void*pb){
  PP*a = (PP*)pa;
  PP*b = (PP*)pb;
  int rv = cmpP(a->first, b->first);
  if(rv!=0)return rv;
  if(a->second != b->second)return(a->second < b->second )?-1:1;
  return 0;
}

typedef long long ll;
#define x first
#define y second
int R[N*2],len,qw;
char S[N];
char a[N*2];
int x[N],y[N];
ll aa[N];
PP p[N];
int ca[N<<3];
ll s[N<<3];
int num[N<<3];
int nj[N<<3];
int de[N<<3];
int d[N<<3];

void down(int rt){
    if(de[rt]){
        de[rt<<1]+=de[rt];
        ca[rt<<1]-=de[rt];
        s[rt<<1]-=num[rt<<1]*de[rt];
        de[rt<<1|1]+=de[rt];
        ca[rt<<1|1]-=de[rt];
        s[rt<<1|1]-=num[rt<<1|1]*de[rt];
        de[rt]=0;
    }
}
void up(int rt){
    ca [rt] = fmin(ca[rt<<1],ca[rt<<1|1]);
    s  [rt] = s[rt<<1]+s[rt<<1|1];
    num[rt] = num[rt<<1]+num[rt<<1|1];
    nj [rt] = nj[rt<<1]+nj[rt<<1|1];
}
void init(int rt, int l, int r){
    de[rt]=0;
    if(l==r){
        if(d[l]<=R[l]){
            s[rt]=d[l];
            num[rt]=1;
            nj[rt] = d[l]&1;
            ca[rt] = INF;
        }
        else{
            s[rt]=R[l];
            num[rt]=0;
            nj[rt]=R[l]&1;
            ca[rt]=d[l]-R[l];
        }
        return;
    }
    int mid=(l+r)>>1;
    init(rt<<1,l,mid);
    init(rt<<1|1,mid+1,r);
    up(rt);
}
void add(int rt, int l, int r){
    if(ca[rt]>=0)return;
    if(l==r){
        d[l]-=de[rt];
        de[rt]=0;
        if(d[l]<=R[l]){
            s[rt]=d[l];
            num[rt]=1;
            nj[rt]=d[l]%2?1:0;
            ca[rt]=INF;
        }
        else{
            s[rt]=R[l];
            num[rt]=0;
            nj[rt]=R[l]&1;
            ca[rt]=d[l]-R[l];
        }
        return;
    }
    int mid=(l+r)>>1;
    if(de[rt]&1){
        nj[rt<<1]=mid-l+1-nj[rt<<1];
        nj[rt<<1|1]=r-mid-nj[rt<<1|1];
    }
    down(rt);
    add(rt<<1,l,mid);
    add(rt<<1|1,mid+1,r);
    up(rt);
}
ll query(int rt, int l, int r, int LL, int rr){
    if(LL<=l&&r<=rr){
        qw+=nj[rt];
        return s[rt];
    }
    int mid=(l+r)>>1;
    if(de[rt]&1){
        nj[rt<<1]=mid-l+1-nj[rt<<1];
        nj[rt<<1|1]=r-mid-nj[rt<<1|1];
    }
    down(rt);
    ll ans=0;
    if(mid>=LL)ans+=query(rt<<1,l,mid,LL,rr);
    if(mid<rr) ans+=query(rt<<1|1,mid+1,r,LL,rr);
    up(rt);
    return ans;
}
void dR(){
    int x=-1,p=-1;
    for(int i=0;i<len;++i){
        if(p>=i)R[i]=fmin(R[2*x-i],p-i);
        else R[i]=0;
        while(R[i]+i+1<len&&i-R[i]-1>=0&&a[R[i]+i+1]==a[i-R[i]-1])++R[i];
        if(R[i]+i>p)
        {
            p=R[i]+i;
            x=i;
        }
    }
}
int main(){
    while(~scanf("%s", S)){
        len=strlen(S);
        for(int i=0;i<len;++i){
            a[i<<1]='#';
            a[i<<1|1]=S[i];
        }
        a[len<<1]='#';
        len=len<<1|1;
        dR();
        int m;
        scanf("%d", &m);
        for(int i=0;i<m;++i){
            scanf("%d%d",&x[i],&y[i]);
            x[i]=(x[i]-1)<<1;
            y[i]=y[i]<<1;
            aa[i]=0;
        }
        for(int i=0;i<m;++i){
            p[i].x.x=x[i];
            p[i].x.y=(x[i]+y[i])>>1;
            p[i].y=i;
        }
        qsort(p, m, sizeof(PP), cmpPP);
        for(int i=0;i<len;++i)d[i]=i;
        init(1,0,len-1);
        for(int i=0,la=0;i<m;++i){
            if(p[i].x.x>la){
                int ddd=p[i].x.x-la;
                de[1]+=ddd;
                ca[1]-=ddd;
                s[1]-=num[1]*ddd;
                if(ddd&1){
                    nj[1]=len-nj[1];
                }
                add(1,0,len-1);
                la=p[i].x.x;
            }
            qw=0;
            ll as=query(1,0,len-1,p[i].x.x, p[i].x.y);
            as+=qw;
            as/=2;
            aa[p[i].y]+=as;
            //
        }
        for(int i=0;i<m;++i){
            p[i].x.x=y[i];
            p[i].x.y=(x[i]+y[i])/2+1;
            p[i].y=i;
        }
        qsort(p, m, sizeof(PP), cmpPP);
        for(int i=0;i<len;++i)d[len-i-1]=i;
        init(1,0,len-1);
        for(int i=m-1,la=len-1;i>=0;--i){
            if(p[i].x.x<la){
                int ddd=la-p[i].x.x;
                de[1]+=ddd;
                ca[1]-=ddd;
                s[1]-=num[1]*ddd;
                if(ddd&1){
                    nj[1]=len-nj[1];
                }
                add(1,0,len-1);
                la=p[i].x.x;
            }
            qw=0;
            ll as=query(1,0,len-1,p[i].x.y, p[i].x.x);
            as+=qw;
            as/=2;
            //--
            aa[p[i].y]+=as;
        }
        for(int i=0;i<m;++i){
            printf("%lld\n", aa[i]);
        }
    }
    return 0;
}





















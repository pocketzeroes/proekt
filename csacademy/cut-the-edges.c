#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

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
typedef struct{
    int a;
    int b;
    int c;
}trip;
trip newTrip(int _x, int _y, int _z){
    trip rez;
    rez.a =_x;
    rez.b =_y;
    rez.c =_z;
    return rez;
}


////////////////////
typedef long long ll;
enum{ MAXN = 100000  };
enum{ MAXS = 4*2*MAXN};


int n;
int a     [MAXN],b[MAXN];
vec adj   [MAXN];
bool been [MAXN];
int cyc   [MAXN+1],ncyc;
int cycidx[MAXN];
int mxpath[2*MAXN],globmxpath;
int mxcyc [MAXN];
int ret   [MAXN];
trip sval [MAXS];

bool dfscycle(int at,int par){
    been[at]=true;
    for(int i=(0);i< adj[at].sz; ++i){
        int to=adj[at].ptr[i];
        if(to==par)
            continue;
        if(been[to]){
            cyc[ncyc++] = to;
            cyc[ncyc++] = at;
            return true;
        }
        else{
            bool mecyc = dfscycle(to,at);
            if(mecyc)
                cyc[ncyc++]=at;
            if(ncyc!=0)
                return mecyc&&at!=cyc[0];
        }
    }
    return false;
}
pair dfspath(int at,int par){
    pair ret = newPair(0,0);
    for(int i=(0);i < adj[at].sz; ++i){
        int to=adj[at].ptr[i];
        if(to==par||cycidx[to]!=-1)
            continue;
        pair cur = dfspath(to,at);
        ret.second = max(ret.second,max(cur.second,ret.first+cur.first+1));
        ret.first  = max(ret.first,cur.first+1);
    }
    return ret;
}
trip combine(trip l,trip r){
    return newTrip(max(l.a,r.a), max(l.b,r.b), max(max(l.c,r.c),l.a+r.b));
}
void sinit(int x,int l,int r){
    if(l==r)
        sval[x] = newTrip(mxpath[l]-l, mxpath[l]+l, mxpath[l]);
    else{
        int m=l+(r-l)/2;
        sinit(2*x+1,l,m); sinit(2*x+2,m+1,r);
        sval[x]=combine(sval[2*x+1],sval[2*x+2]);
    }
}
trip sget(int x,int l,int r,int L,int R){
    if(L<=l&&r<=R)
        return sval[x];
    else {
        int m=l+(r-l)/2;
        trip ret = newTrip(INT_MIN, INT_MIN, 0);
        if(L<=m)
            ret = combine(ret,sget(2*x+1, l, m, L, R));
        if(m+1<=R)
            ret = combine(ret, sget(2*x+2, m+1, r, L, R));
        return ret;
    }
}
int main(){
    scanf("%d", &n);
    for(int i=(0);i<(n);++i) {
      scanf("%d %d", &a[i], &b[i]);
      --a[i], --b[i];
      int a_i = a[i];
      int b_i = b[i];
      adj[a_i].ptr = pushback(adj[a_i].ptr, &adj[a_i].sz, b_i);
      adj[b_i].ptr = pushback(adj[b_i].ptr, &adj[b_i].sz, a_i);
    }
    ncyc = 0;
    for(int i=(0);i<(n);++i)
        been[i] = false;
    dfscycle(0,-1);
    --ncyc;
    assert(ncyc!=0);
    for(int i=(0);i<(n);++i)
        cycidx[i]=-1;
    for(int i=(0);i<(ncyc);++i)
        cycidx[cyc[i]]=i;
    for(int i=(0);i<(n);++i)
        mxpath[i]=0;
    globmxpath=0;
    for(int i=(0);i<(ncyc);++i){
        pair cur = dfspath(cyc[i],-1);
        mxpath[i]=mxpath[ncyc+i]=cur.first;
        globmxpath=max(globmxpath,cur.second);
    }
    sinit(0,0,2*ncyc-1);
    for(int i=(0);i<(ncyc);++i){
        trip cur=sget(0,0,2*ncyc-1,i+1,ncyc+i);
        mxcyc[i]=max(globmxpath,cur.c);
    }
    for(int i=(0);i<(n);++i){
        if(cycidx[a[i]]==-1||cycidx[b[i]]==-1){
            ret[i]=-1;
            continue;
        }
        int ai=cycidx[a[i]],bi=cycidx[b[i]];
        if((ai+1)%ncyc!=bi)
            swap(ai, bi);
        assert((ai+1)%ncyc==bi);
        ret[i]=mxcyc[ai];
    }
    for(int i=(0);i<(n);++i)
        printf("%d\n",ret[i]);
}

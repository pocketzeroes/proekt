#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{ N_ = 101000};
enum{ SZ = 131072};
typedef struct{
  ll  first;
  int second;
}pli;
pli newpli(ll a, int b){
  return(pli){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pli*pushbackP(pli*array, int*size, pli val){
  pli*output = resizeArray(array, pli, *size + 1);
  output[(*size)++] = val;
  return output;
}
typedef struct{
	pli*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
    pli*a=(pli*)pa;
    pli*b=(pli*)pb;
    if(a->first  != b->first) return(a->first  < b->first )?-1:1;
    if(a->second != b->second)return(a->second < b->second)?-1:1;
    return 0;
}


typedef struct{
    int e, c, f;
}Edge;

Edge newedge(int e, int c, int f){
    return(Edge){e, c, f};
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////////////////////////////

vece E[N_];
vec  G[N_];
int n, par[N_], P[N_], C[N_], Num[N_], cnt, PPP[N_], ord[N_];
ll D[N_];
int INF =(int)1e9;

//struct Tree{
    int Mn[SZ+SZ], K[SZ+SZ];
    void UDT(int nd){
        Mn[nd] = fmin(Mn[nd*2],Mn[nd*2+1]);
    }
    void init(int nd, int b, int e){
        Mn[nd]=K[nd]=0;
        if(b==e){
            Mn[nd] = P[ord[b]];
            return;
        }
        int m = (b+e)>>1;
        init(nd*2,b,m);
        init(nd*2+1,m+1,e);
        UDT(nd);
    }
    void Add2(int nd, int x){
        Mn[nd]+=x;
        K[nd]+=x;
    }
    void Spread(int nd){
        Add2(nd*2,K[nd]);
        Add2(nd*2+1,K[nd]);
        K[nd]=0;
    }
    void Add(int nd, int b, int e, int s, int l, int x){
        if(s>l)
            return;
        if(s<=b&&e<=l){
            Add2(nd,x);
            return;
        }
        Spread(nd);
        int m = (b+e)>>1;
        if(s<=m)
            Add(nd*2,b,m,s,l,x);
        if(l>m)
            Add(nd*2+1,m+1,e,s,l,x);
        UDT(nd);
    }
    int Get(int nd, int b, int e, int s, int l){
        if(s>l)
            return INF;
        if(s<=b&&e<=l)
            return Mn[nd];
        Spread(nd);
        int m = (b+e)>>1, r1=INF,r2=INF;
        if(s<=m)
            r1=Get(nd*2,b,m,s,l);
        if(l>m)
            r2=Get(nd*2+1,m+1,e,s,l);
        return fmin(r1, r2);
    }
//};
void DFS(int a, ll s){
    D[a] = s;
    C[a]=1;
    for(int z=0;z<E[a].sz;z++){Edge t = E[a].ptr[z];
        P[t.e] = t.f;
        par[t.e] = a;
        DFS(t.e, s+t.c);
        C[a]+=C[t.e];
    }
}
void HLD(int a, int ppp){
    int Mx=-1,pv=-1;
    PPP[a]=ppp;
    Num[a]=++cnt;
    ord[cnt] = a;
    for(int z=0;z<G[a].sz;z++){int x = G[a].ptr[z];
        if(Mx<C[x]){
            Mx=C[x];
            pv=x;
        }
    }
    if(pv!=-1){
        HLD(pv,ppp);
    }
    for(int z=0;z<G[a].sz;z++){int x = G[a].ptr[z];
        if(x==pv)
            continue;
        HLD(x,x);
    }
}
int Calc(int a){
    int r = INF;
    while(1){
        if(PPP[a]==PPP[1]){
            r = fmin(r, Get(1, 1, n, 2, Num[a]));
            break;
        }
        r = fmin(r, Get(1, 1, n, Num[PPP[a]], Num[a]));
        a=par[PPP[a]];
    }
    return r;
}
void Del(int a, int d){
    while(1){
        if(PPP[a]==PPP[1]){
            Add(1, 1, n, 2, Num[a], -d);
            break;
        }
        Add(1, 1, n, Num[PPP[a]], Num[a], -d);
        a=par[PPP[a]];
    }
}
void Solve(){
    int i;
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        E[i].sz=0;
        G[i].sz=0;
    }
    for(i=1; i<n; i++){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        pbe(E[a], newedge(b, d, c));
        pb(G[a], b);
    }
    DFS(1, 0);
    cnt = 0;
    HLD(1, 1);
    vecp V = newVecP();
    for(i=2; i<=n; i++){
       pbp(V, newpli(D[i], i));
    }
    qsort(V.ptr, V.sz, sizeof(pli), cmpP);
    ll r1 = 0, r2 =0;
    init(1, 1, n);
    for(int z=0;z<V.sz;z++){pli t = V.ptr[z];
        int a = t.second, c = (int)1e9;
        int d = Calc(a);
        if(d){
            Del(a, d);
            r1 += d;
            r2 += d*D[a];
        }
    }
    printf("%lld %lld\n", r1, r2);
}
int main(){
    int TC, T;
    scanf("%d", &TC);
    for(T=1; T<=TC; T++){
        printf("Case #%d: ", T);
        Solve();
    }
    return 0;
}

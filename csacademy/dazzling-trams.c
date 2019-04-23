#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
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

typedef long long ll;

enum{ MAXSTATION=100000};
enum{ MAXROUTE  =100000};
enum{ MAXSTOP   =250000};
int nstation,nroute,lim;
int off[MAXROUTE+1],len[MAXROUTE];
int nstop;
int station[MAXSTOP],route[MAXSTOP],routeidx[MAXSTOP];
vec stops[MAXSTATION];

//struct UF{
int*par;
int*sz;
int*fst;
int*lst;
int n;
void init(int _n){
    n=_n;
    par = calloc(n, sizeof(int));
    sz  = calloc(n, sizeof(int));
    fst = calloc(n, sizeof(int));
    lst = calloc(n, sizeof(int));
    for(int i=(0); i<(n); ++i)
        par[i]=i,sz[i]=i,fst[i]=lst[i]=i;
}
int find(int x){
    if(par[x]==x)
        return x;
    return par[x]=find(par[x]);
}
void unite(int a,int b){
    a=find(a),b=find(b);
    if(a==b)
        return;
    if(sz[a]<sz[b])
        swap(a,b);
    par[b]=a,sz[a]+=sz[b],fst[a]=min(fst[a],fst[b]),lst[a]=max(lst[a],lst[b]);
}
//};

int d[MAXSTATION];
int q[MAXSTATION],qhead,qtail;

int solve(){
    for(int i=(0);i<(nstation);++i)
        stops[i].sz=0;
    for(int i=(0);i<(nstop);++i)
        stops[station[i]].ptr = pushback(stops[station[i]].ptr, &stops[station[i]].sz, i);
    init(nstop);
    qhead=qtail=0;
    for(int i=(0);i<(nstation);++i)
        d[i]=INT_MAX;
    d[0]=0,q[qhead++] = 0;
    while(qtail<qhead){
        int at=q[qtail++];
        for(int i=(0);i<(((int)(stops[at]).sz));++i){
            int atstop=stops[at].ptr[i];
            while(true){
                int id=find(atstop);
                vec opt = newVec();
                {
                    int tostop=fst[id]-1;
                    if(tostop>=0&&route[tostop]==route[atstop]&&routeidx[tostop]>=routeidx[atstop]-lim)
                        opt.ptr = pushback(opt.ptr, &opt.sz, tostop);
                }
                {
                    int tostop=lst[id]+1;
                    if(tostop<nstop&&route[tostop]==route[atstop]&&routeidx[tostop]<=routeidx[atstop]+lim)
                        opt.ptr = pushback(opt.ptr, &opt.sz, tostop);
                }
                if(((int)(opt).sz)==0)
                    break;
                for(int j=(0);j<(((int)(opt).sz));++j){
                    int tostop=opt.ptr[j],to=station[tostop];
                    if(d[to]==INT_MAX)
                        d[to]=d[at]+1,q[qhead++]=to;
                    unite(atstop,tostop);
                }
            }
        }
    }
    return d[nstation-1];
}
int main(){
    scanf("%d %d %d", &nstation, &nroute, &lim);
    off[0]=0;
    for(int i=(0);i<(nroute);++i){
        scanf("%d", &len[i]);
        off[i+1]=off[i]+len[i];
        for(int j=(0);j<(len[i]);++j){
            scanf("%d", &station[off[i]+j]);
            --station[off[i]+j];
            route[off[i]+j] = i;
            routeidx[off[i]+j] = j;
        }
    }
    nstop = off[nroute];
    printf("%d\n", solve());
    return 0;
}

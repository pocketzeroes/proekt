#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

/////////////////
enum{ N=10050};
enum{ M=2*N  };
vec x[M],y[M];
int ls[M], rs[M], clock, root[N];
int sol;
bool done[N*25];
vec E[N];
int p[N];
int par[N][15], dep[N], gsz[N];
int Chain[N], Index[N], time, CS[N];
vec Head;
vecp edges;



void Set(int*c, int ss, int se, int qs, int qe, int X){
    if(qs>qe)
        return;
    if(ss>qe || qs>se)
        return;
    if(!*c)
        *c=++clock;
    y[*c].ptr = pushback(y[*c].ptr, &y[*c].sz, X);
    if(qs<=ss && qe>=se){
        x[*c].ptr = pushback(x[*c].ptr, &x[*c].sz, X);
        return;
    }
    int mid = ss+se>>1;
    Set(&ls[*c], ss  , mid, qs, qe, X);
    Set(&rs[*c], mid+1, se, qs, qe, X);
}
void Get(int c, int ss, int se, int qs, int qe){
    if(qs>qe)
        return;
    if(ss>qe || qs>se)
        return;
    while(x[c].sz && done[x[c].ptr[x[c].sz-1]])
        x[c].sz--;
    while(y[c].sz && done[y[c].ptr[y[c].sz-1]])
        y[c].sz--;
    if(qs<=ss && qe>=se){
        if(y[c].sz)
            sol=y[c].ptr[y[c].sz-1];
        return;
    }
    if(x[c].sz)
        sol=x[c].ptr[x[c].sz-1];
    int mid=ss+se>>1;
    Get(ls[c], ss,mid,qs,qe);
    Get(rs[c], mid+1,se,qs,qe);
}
int Find(int x){
    if(p[x]==x)
        return x;
    else{
        p[x]=Find(p[x]);
        return p[x];
    }
}
void Union(int x, int y){
    p[Find(x)]=Find(y);
}
void DFS(int u, int p){
    gsz[u]=1;
    dep[u]=dep[p]+1;
    par[u][0]=p;
    for(int i=1;i<15;i++)
        par[u][i]=par[par[u][i-1]][i-1];
    for(int z=0;z<E[u].sz;z++){int v=E[u].ptr[z];
        if(v!=p)
            DFS(v,u), gsz[u]+=gsz[v];
    }
}
int LCA(int u, int v){
    if(dep[u]<dep[v])
        return LCA(v,u);
    int i;
    for(i=14;~i;i--)
        if(dep[par[u][i]]>=dep[v])
            u=par[u][i];
    for(i=14;~i;i--)
        if(par[u][i]!=par[v][i])
            u=par[u][i],v=par[v][i];
    if(u==v)
        return v;
    return par[v][0];
}
void HLD(int u, int p){
    if(!Chain[u]){
        Chain[u] = Head.sz;
        Head.ptr = pushback(Head.ptr, &Head.sz, u);
        time=0;
    }
    Index[u]=++time;
    CS[Chain[u]]=time;
    int HC=0;
    for(int z=0;z<E[u].sz;z++){int v=E[u].ptr[z];
        if(v!=p && gsz[v]>gsz[HC])
            HC=v;
    }
    if(HC){
        Chain[HC]=Chain[u];
        HLD(HC,u);
        for(int z=0;z<E[u].sz;z++){int v=E[u].ptr[z];
            if(v!=p && v!=HC)
                HLD(v,u);
        }
    }
}
void Set3(int u, int v, int X){
    int lca=LCA(u,v);
    while(Chain[u]!=Chain[lca]){
        Set(&root[Chain[u]], 1, CS[Chain[u]], 1, Index[u], X);
        u=par[Head.ptr[Chain[u]]][0];
    }
    Set(&root[Chain[u]], 1, CS[Chain[u]], Index[lca]+1, Index[u], X);
    while(Chain[v]!=Chain[lca]){
        Set(&root[Chain[v]], 1, CS[Chain[v]], 1, Index[v], X);
        v=par[Head.ptr[Chain[v]]][0];
    }
    Set(&root[Chain[v]], 1, CS[Chain[v]], Index[lca]+1, Index[v], X);
}
void Get2(int u, int v){
    sol=-1;
    int lca=LCA(u,v);
    while(Chain[u]!=Chain[lca]){
        Get(root[Chain[u]],1,CS[Chain[u]],1,Index[u]);
        u=par[Head.ptr[Chain[u]]][0];
    }
    Get(root[Chain[u]],1,CS[Chain[u]],Index[lca]+1,Index[u]);
    while(Chain[v]!=Chain[lca]){
        Get(root[Chain[v]],1,CS[Chain[v]],1,Index[v]);
        v=par[Head.ptr[Chain[v]]][0];
    }
    Get(root[Chain[v]],1,CS[Chain[v]],Index[lca]+1,Index[v]);
    if(~sol)
        done[sol]=1;
}
int main(){
    Head.ptr = pushback(Head.ptr, &Head.sz, 69);
    int n, m, q, u, v, i;
    scanf("%i %i %i", &n, &m, &q);
    for(i=1; i<=n; i++)
        p[i] = i;
    while(m--){
        scanf("%i %i", &u, &v);
        if(Find(u)==Find(v)){
            edges.ptr = pushbackP(edges.ptr, &edges.sz, newPair(u,v));
        }
        else{
            Union(u, v);
            E[u].ptr = pushback(E[u].ptr, &E[u].sz, v);
            E[v].ptr = pushback(E[v].ptr, &E[v].sz, u);
        }
    }
    DFS(1, 0);
    HLD(1, 0);
    for(i=0; i<edges.sz; i++){
        Set3(edges.ptr[i].first, edges.ptr[i].second, i);
    }
    while(q--){
        scanf("%i %i", &u, &v);
        Get2(u, v);
        if(~sol)
            printf("0 %i %i\n", edges.ptr[sol].first, edges.ptr[sol].second);
        else
            printf("1\n");
        fflush(stdout);
    }
    return 0;
}



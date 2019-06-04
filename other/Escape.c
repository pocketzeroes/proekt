#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

const ll INF = LLONG_MAX / 2;

typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int compP( pair a, pair b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}

typedef struct heap{
    pair v;
    struct heap*l;
    struct heap*r;
}heap;
heap*H; //vector of heaps
heap*nexth;

typedef struct vertex vertex;
typedef vertex* vertexp;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
vertexp*pushbackVP(vertexp*array, int *size, vertexp value){
  vertexp*output = resizeArray(array, vertexp, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	vertexp*ptr;
	int sz;
}vecvp;
vecvp newVecVP(){
	vecvp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
struct vertex{
    ll    w;
    vecvp N;//vec of vert ptr
};
vertex*G;//arr of vertexes

typedef heap* heapp;

void merge(heapp*x, heap*y){
    if(!*x)
        swap(*x, y);
    if(!y)
        return;
    if(compP(y->v, (*x)->v)>0)
        swap(*x, y);
    swap((*x)->l, (*x)->r);
    merge(&(*x)->r, y);
}
heap*dfs(vertex*u, vertex*p){
    heap*h = NULL;
    for(int z=0; z<u->N.sz; z++){vertexp v = u->N.ptr[z];
        if(v != p)
            merge(&h, dfs(v, u));
    }
    pair a = newPair(min(u->w, 0ll), max(u->w, 0ll));
    while(h){
        if (a.second +  h->v.first >= 0)
            a.second += h->v.first + h->v.second;
        else if(a.first + a.second <= 0){
            a.first += a.second + h->v.first;
            a.second = h->v.second;
        }
        else
            break;
        merge(&h->l, h->r);
        h = h->l;
    }
    if(a.first + a.second > 0){
        nexth->v = a;
        nexth->r = nexth->l = NULL;
        merge(&h, nexth++);
    }
    return h;
}
void testcase(){
    int n, t;
    scanf("%d %d", &n, &t);
    G = calloc(n+1, sizeof(vertex));
    G[0].w = INF;
    for (int i=1; i<=n; ++i)
        scanf("%lld", &G[i].w);
    G[0].N.ptr = pushbackVP(G[0].N.ptr, &G[0].N.sz, &G[t]);
    G[t].N.ptr = pushbackVP(G[t].N.ptr, &G[t].N.sz, &G[0]);
    for(int i=1; i<n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].N.ptr=pushbackVP(G[x].N.ptr, &G[x].N.sz, &G[y]);
        G[y].N.ptr=pushbackVP(G[y].N.ptr, &G[y].N.sz, &G[x]);
    }
    H = calloc(n+1, sizeof(heap));
    nexth = &H[0];
    heap * h = dfs(&G[1], NULL);
    puts(h && h->v.first >= 0 && h->v.second >= INF/2 ? "escaped" : "trapped");
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--)
        testcase();
    return 0;
}

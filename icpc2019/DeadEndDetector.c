#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
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
	vec rez;// = malloc(sizeof(vec));
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

#define forn(i,n) for(int i=0;i<(n);++i)
#define pb pushback
#define fi first
#define se second

enum{ maxn=510000};
vec e[maxn];
int d[maxn], xr[maxn];
int mark[maxn], in_tree[maxn];

void dfs(int v, int p){
    in_tree[v]=2;
    for(int z=0;z<e[v].sz;z++){int u = e[v].ptr[z];
        if(u!=p)
            dfs(u, v);
    }
}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        int v, u;
        scanf("%d %d", &v, &u);
        --v, --u;
        e[v].ptr = pb(e[v].ptr, &e[v].sz, u);
        e[u].ptr = pb(e[u].ptr, &e[u].sz, v);
        ++d[v], ++d[u];
    }
    vec q = newVec();
    forn(i, n) if(d[i]==1) q.ptr = pb(q.ptr, &q.sz, i);
    vec tree_rep = newVec();
    forn(cur, q.sz){
        int v = q.ptr[cur];
        mark[v]=1;
        bool any_unm = false;
        for(int z=0;z<e[v].sz;z++){int u=e[v].ptr[z];
            if(mark[u])continue;
            any_unm=true;
            --d[u];
            if(d[u]==1)q.ptr = pb(q.ptr, &q.sz, u);
        }
        if(!any_unm)tree_rep.ptr = pb(tree_rep.ptr, &tree_rep.sz, v);
    }
    for(int z=0;z<tree_rep.sz;z++){int v=tree_rep.ptr[z];
      dfs(v, -1);
    }
    vecp ans = newVecP();
    forn(v,n)
      for(int z=0;z<e[v].sz;z++){int u=e[v].ptr[z];
        if(!mark[v]&&mark[u]||in_tree[v]&&e[v].sz==1)
          ans.ptr = pushbackP(ans.ptr, &ans.sz, (pair){v,u});
      }
    qsort(ans.ptr, ans.sz, sizeof(pair), cmpP);
    printf("%d\n", ans.sz);
    for(int z=0;z<ans.sz;z++){pair w = ans.ptr[z];
        printf("%d %d\n", w.fi+1, w.se+1);
    }
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int lower_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
#define back(vv) vv.ptr[vv.sz-1]
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////////////
int*val;
int*comp;
vec z, cont;
int Time, ncomps;
int N, ans, g_sz;


int dfs(int j, vec*g){
    int low = val[j] = ++Time, x;
    pb(z, j);
    for(int q=0;q<g[j].sz;q++){int e = g[j].ptr[q];
      if(comp[e] < 0)
        low = fmin(low, val[e] ?: dfs(e, g));
    }
    if(low == val[j]){
        do{
            x = back(z);
            z.sz--;
            comp[x] = ncomps;
            pb(cont, x);
        }while(x != j);
        void f(){
            bool wc = 0;
            for(int w=0;w<cont.sz;w++){int it=cont.ptr[w];
                if(it < N)
                   wc = true;
            }
            ans += wc;
        }
        f();
        cont.sz=0;
        ncomps++;
    }
    return val[j] = low;
}
void scc(vec*g){
    int n = g_sz;
    val =calloc(n, sizeof(int));
    comp=calloc(n, sizeof(int)); fill(comp, n, -1);
    Time = ncomps = 0;
    for(int i=0; i<n; ++i)
      if(comp[i] < 0)
        dfs(i, g);
}
int main(){
    int K;
    scanf("%d %d", &N, &K);
    vec ed[3*N]; clr(ed);
    g_sz = 3*N;
    pair lranks[N]; clr(lranks);
    pair hranks[N]; clr(hranks);
    for(int i=0; i<N; ++i){
        scanf("%d", &lranks[i].first);
        lranks[i].second = i;
    }
    for(int i=0; i<N; ++i){
        scanf("%d", &hranks[i].first);
        hranks[i].second = i;
    }
    qsort(lranks, N, sizeof(pair), cmpP);
    qsort(hranks, N, sizeof(pair), cmpP);
    for(int i=0; i<N-1; ++i){
       pb(ed[((i)+N)], ((i + 1) + N));
       pb(ed[((i)+((N)+N))], ((i + 1) + ((N) + N)));
    }
    for(int i=0; i<N; ++i){
        pb(ed[((i) + N)], lranks[i].second);
        pb(ed[((i) + ((N) + N))], hranks[i].second);
        int lb = lranks[i].first + K + 1;
        int hb = hranks[i].first + K + 1;
        int lp = lower_bound(lranks, N, newpair(lb, 0));
        int hp = lower_bound(hranks, N, newpair(hb, 0));
        if(lp != N)
           pb(ed[lranks[i].second], ((lp) + N));
        if(hp != N)
           pb(ed[hranks[i].second], ((hp) + ((N) + N)));
    }
    ans = 0;
    scc(ed);
    printf("%d\n", ans);
    return 0;
}

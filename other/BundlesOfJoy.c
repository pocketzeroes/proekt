#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

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
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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

////////////////////////////////
typedef long long ll;

void solve(){
    int n, m;
    scanf("%d %d", &n, &m);
    vec bundle[m];  clr(bundle);
    int price [m];  clr(price );
    bool has[m][n]; clr(has);
    vecp sizeid=newVecP();
    for(int b=0; b<m; ++b){
        scanf("%d", &price[b]);
        int s;
        scanf("%d", &s);
        while(s--){
            int dessert;
            scanf("%d", &dessert);
            dessert--;
            has[b][dessert] = true;
            pb(bundle[b], dessert);
        }
        pbp(sizeid, newpair(bundle[b].sz, b));
    }
    int lastowner[n]; fill(lastowner, n, -1);
    vec roots=newVec();
    vec children[m]; clr(children);
    qsort(sizeid.ptr, sizeid.sz, sizeof(pair), cmpP);
    for(int j=sizeid.sz-1; j>=0; --j){
        int id = sizeid.ptr[j].second;
        int par = lastowner[bundle[id].ptr[0]];
        if(par == -1)
            pb(roots, id);
        else
            pb(children[par], id);
        for(int z=0;z<bundle[id].sz;z++){int item = bundle[id].ptr[z];
            lastowner[item] = id;
        }
    }
    ll fprice[m]; clr(fprice);
    for(int j=0; j<sizeid.sz; ++j){
        int id = sizeid.ptr[j].second;
        fprice[id] = price[id];
        ll cost   = 0LL;
        int items = 0;
        for(int z=0;z<children[id].sz;z++){int c = children[id].ptr[z];
            cost  += fprice[c];
            items += bundle[c].sz;
        }
        if(items == bundle[id].sz && cost < fprice[id])
            fprice[id] = cost;
    }
    ll ans = 0LL;
    for(int z=0;z<roots.sz;z++){int r = roots.ptr[z];
        ans += fprice[r];
    }
    printf("%lld\n", ans);
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
ll in_nextLong(){
  ll x;
  scanf("%lld", &x);
  return x;
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////
vec*v;
ll *d;
ll *b;
int*e;

void error(){
    puts("impossible");
    exit(0);
}
void dfs1(int x){
    bool ok = true;
    ll   s  = 0;
    int  c  = 0;
    for(int z=0; z<v[x].sz; z++){int u = v[x].ptr[z];
        if(u == e[x])
            continue;
        c++;
        dfs1(u);
        if(d[u] == 0)
            ok = false;
        s    += d[u];
        b[x] += b[u];
    }
    if(ok && c != 0){
        if(d[x] != 0 && d[x] != s)
            error();
        d[x] = s;
    }
    if(c == 0)
        b[x] = d[x] == 0 ? 1 : d[x];
    b[x] = fmaxl(d[x], b[x]);
}
void dfs2(int x){
    if(d[x] <= 0)
        error();
    int c = 0,
        k = 0,
        z = 0;
    ll  s = 0;
    int g = 0;
    for(int q=0; q<v[x].sz; q++){int u = v[x].ptr[q];
        if(u == e[x])
            continue;
        c++;
        if(d[u] == 0){
            z++;
            k = u;
            g += b[u];
        }
        s += d[u];
    }
    if(z == 0 && d[x] != s && c != 0)
        error();
    if(z == 1)
        d[k] = d[x]-s;
    if(z > 1 && g == d[x]-s){
        for(int q=0; q<v[x].sz; q++){int u = v[x].ptr[q];
            if(u == e[x])
                continue;
            if(d[u] == 0)
                d[u] = b[u];
        }
    }
    for(int q=0; q<v[x].sz; q++){int u = v[x].ptr[q];
        if(u == e[x])
            continue;
        dfs2(u);
    }
}
int main(){
    int n = in_nextInt();
    v = calloc(n+1, sizeof(vec));
    d = calloc(n+1, sizeof(ll ));
    b = calloc(n+1, sizeof(ll ));
    e = calloc(n+1, sizeof(int));
    for(int i=2; i<=n; i++){
        int a = in_nextInt();
        pb(v[a], i);
        e[i] = a;
    }
    for(int i=1; i<=n; i++)
        d[i] = in_nextLong();
    dfs1(1);
    dfs2(1);
    for(int i=1; i<=n; i++)
        printf("%lld\n", d[i]);
    return 0;
}

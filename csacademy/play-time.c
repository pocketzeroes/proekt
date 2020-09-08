#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
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
#define copyVec(best, vis) do{             \
  if(best.ptr)free(best.ptr);              \
  best.sz = vis.sz;                        \
  best.ptr = calloc(vis.sz, sizeof(int));  \
  for(int i=0; i<vis.sz; i++)              \
      best.ptr[i] = vis.ptr[i];            \
}while(0)
int unique(int*a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
}
///////////////////
enum{mxM=(int)1e6};
int n, m, c[mxM+1][26], e[mxM+1], dp[mxM+1], ans;
vec v[mxM+1];

void dfs(int u){
    for(int i=0; i<26; ++i){
        if(!c[u][i])
            continue;
        dfs(c[u][i]);
        dp[u]^=dp[c[u][i]];
    }
    for(int i=0; i<26; ++i){
        if(!c[u][i])
            continue;
        for(int z=0;z<v[c[u][i]].sz;z++){int j=v[c[u][i]].ptr[z];
           pb(v[u], j^dp[u]^dp[c[u][i]]);
        }
    }
    if(e[u]){
        pb(v[u], dp[u]);
        vec w=newVec(); copyVec(w, v[u]);
        qsort(w.ptr, w.sz, sizeof(int), cmp);
        w.sz = unique(w.ptr, w.sz);
        for(dp[u]=0; dp[u]<w.sz&&w.ptr[dp[u]]==dp[u]; ++dp[u]);
    }
}
int main(){
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        char*s=getstr();
        int u=0;
        for(int z=0;s[z];z++){char d=s[z];
            if(!c[u][d-'a'])
                c[u][d-'a']=++m;
            u=c[u][d-'a'];
        }
        e[u]=1;
    }
    dfs(0);
    for(int z=0;z<v[0].sz;z++){int a=v[0].ptr[z];
        ans+=!a;
    }
    printf("%d\n", ans);
    return 0;
}

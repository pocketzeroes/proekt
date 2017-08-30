#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

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
///////////////////

int p[100001];
int n, m;
int pos[100001];
bool done[100001];
vec g[100001];
int u, v;
int now=2;



int cmp(const void*pa, const void*pb){
    int*px=(int*)pa;
    int*py=(int*)pb;
    int x = *px;
    int y = *py;
    return (pos[x]<pos[y])?-1:1;
}

void dfs(int u){
    done[u]=1;
    for(int z=0;z<g[u].sz;z++){int x = g[u].ptr[z];
        if(done[x]) 
            continue;
        if(x != p[now]){
            puts("0");
            exit(0);
        }
        now++;
        dfs(x);
    }
}
int main(){
    scanf("%d %d", &n, &m);
    if(n==1){
        puts("1");
        return 0;
    }
    for(int i=1; i<=n; i++){
        scanf("%d", &p[i]);
        pos[p[i]]=i;
    }
    for(int i=1; i<=m; i++){
        scanf("%d %d", &u, &v);
        if(pos[u]>pos[v]) 
            swap(u, v);
        g[u].ptr = pushback(g[u].ptr, &g[u].sz ,v);
    }
    for(int i=1; i<=n; i++)
        qsort(g[i].ptr, g[i].sz, sizeof(int), cmp);
    dfs(1);
    puts("1");
}





























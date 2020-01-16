#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
///////////////////////////////////////
typedef long long ll;

void maximize(ll*x, ll y){
    if(*x<y)
       *x=y;
}
enum{ MAX = 100100};
ll INF = (long long)1e18 + 7LL;
int numNode, numEdge, sa, sb;
vec adj[MAX];
int value[MAX];
ll best[MAX];
char input[22];

void loadGraph(){
    scanf("%d%d", &numNode, &numEdge);
    scanf("%d", &sa);
    scanf("%d%d", &sa, &sb);
    for (int love=0,_n=(numEdge);love<_n;love=love+1){
        int u, v;
        scanf("%d%d", &u, &v);
        pb(adj[u], v);
    }
    for(int i=(1),_b=(numNode);i<=_b;i=i+1){
        scanf("%s", input);
        int x;
        scanf("%d", &x);
        if(input[0] == 'P'){
            scanf("%d", &x);
            value[i] = 0;
        }
        else
            value[i] = input[0] == 'S' ? x : -x;
    }
}
long long calcDist(int u){
    if(adj[u].sz==0)
        return 0;
    if(best[u] > -INF) 
        return best[u];
    for(int z=0;z<adj[u].sz;z++){int it=adj[u].ptr[z];
        maximize(&best[u], value[it] + calcDist(it));
    }
    return best[u];
}
void process(){
    memset(best, -0x3f, sizeof best);
    printf("%lld %lld\n", calcDist(sa), calcDist(sb) );
}
int main(){
    loadGraph();
    process();
    return 0;
}

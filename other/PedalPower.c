#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
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
int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
            a[++j] = a[i];
	return j + 1;
}
//////////////
enum{ N = 500};
const ll INF = 1ll<<60;
ll bike   [N][N];
ll nonbike[N][N];

void floyd_warshall(ll adj[N][N], int n){
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}
int main(){
    int n, x, y, z;
    scanf("%d %d", &n, &x);
    for(int i = 0; i < n; i++){
        fill(bike[i]   , n, INF);
        fill(nonbike[i], n, INF);
        bike[i][i] = nonbike[i][i] = 0;
    }
    for (int i = 0; i < x; i++){
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        bike[u][v] = bike[v][u] = t;
    }
    scanf("%d", &y);
    for(int i = 0; i < y; i++){
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        nonbike[u][v] = nonbike[v][u] = t;
    }
    scanf("%d", &z);
    vec a = newVec();
    for(int i=0; i<z; i++){
        int nextstop;
        scanf("%d", &nextstop);
        a.ptr = pushback(a.ptr, &a.sz, nextstop);
    }
    a.ptr = pushback(a.ptr, &a.sz, 0);
    a.sz = unique(a.ptr, a.sz);
    floyd_warshall(bike, n);
    floyd_warshall(nonbike, n);
    ll cost [n];
    ll ncost[n];
    fill(cost, n, INF);
    int from = 0;
    cost[from] = 0;
    for(int z=0;z<a.sz;z++){int nxtstop = a.ptr[z];
        fill(ncost, n, INF);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j)
                    ncost[j] = min(ncost[j], cost[i] + nonbike[from][i] + bike[i][j] + nonbike[j][nxtstop]);
                else
                    ncost[j] = min(ncost[j], cost[i] + nonbike[from][nxtstop]);
            }
        }
        from = nxtstop;
        ll tmp[n];
        memcpy(tmp  , ncost , sizeof(cost));
        memcpy(ncost, cost  , sizeof(cost));
        memcpy(cost , tmp   , sizeof(cost));
    }
    printf("%lld\n", cost[0]);
    return 0;
}

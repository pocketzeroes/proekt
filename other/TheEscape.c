#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
//////////////////////////////

int N, M, root = 0, dp1 [200010], dp2 [200010], dp3 [200010];
vec adjacency [200010];
bool isPig [200010];

void extendIt(int u, int v){
    if(isPig[u]){
        dp1[u] = dp3[v];
        dp2[u] = min(dp1[v], dp2[v]);
        dp3[u] = dp3[v];
    }
    else{
        dp1[u] = dp1[v];
        dp2[u] = min(dp1[v], dp2[v])+1;
        dp3[u] = dp3[v]+1;
    }
}
void chainIt(int u, int v){
    int ndp1 = dp1[u]+dp1[v];
    ndp1     = min(ndp1, min(dp2[u]+dp3[v], dp2[v]+dp3[u]));
    int ndp2 = dp2[u]+min(dp1[v], dp2[v]);
    int ndp3 = min(dp3[u]+min(dp1[v], dp2[v]), dp2[u]+dp3[v]);
    dp1[u] = ndp1;
    dp2[u] = ndp2;
    dp3[u] = ndp3;
}
void solveIt(int curr, int prevy){
    if(adjacency[curr].sz == 1){
        dp1[curr] = 0;
        dp2[curr] = dp3[curr] = isPig[curr] ? 0 : 1;
        return;
    }
    bool firsty = true;
    for(int z=0; z<adjacency[curr].sz; z++){int nexty = adjacency[curr].ptr[z];
        if(nexty == prevy)
            continue;
        solveIt(nexty, curr);
        if(firsty){
            extendIt(curr, nexty);
            firsty = false;
        }
        else
            chainIt(curr, nexty);
    }
}
int main(){
    scanf("%d %d", &N, &M);
    memset(isPig, false, sizeof(isPig));
    for(int i = 1; i < N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        adjacency[a].ptr = pushback(adjacency[a].ptr, &adjacency[a].sz, b);
        adjacency[b].ptr = pushback(adjacency[b].ptr, &adjacency[b].sz, a);
    }
    for(int i = 0; i < M; i++){
        int x;
        scanf("%d", &x);
        isPig[x] = true;
    }
    while(adjacency[root].sz == 1)
        root++;
    solveIt(root, -1);
    printf("%d\n", dp1[root]);
    return 0;
}

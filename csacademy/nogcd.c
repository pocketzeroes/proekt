#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>
#define maxN 100002
#define maxM 220002

typedef struct pair{
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
pair *pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int N, M;
int value[maxN];
vec G[maxN];
bool  used [maxN];
bool  usedE[maxM];
int v;

void dfs(int node){
    used[node]=1;
    for(int i=0;i<G[node].sz;i++){pair nxt = G[node].ptr[i];
        int son = nxt.first, idx = nxt.second;
        if(!usedE[idx]){
            printf("%d %d %d\n", node, son, v += 1);
            usedE[idx]=1;
        }
        if(!used[son])
            dfs(son);
    }
}
int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= M; ++ i){
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].ptr = pushbackP(G[x].ptr, &G[x].sz, newPair(y, i));
        G[y].ptr = pushbackP(G[y].ptr, &G[y].sz, newPair(x, i));
    }
    dfs(1);
    return 0;
}






















































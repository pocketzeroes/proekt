#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
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

// sol for tash I == red black tree
int N, K;
enum{MODO = 1000000007};
int preCount;
int*id;
int*pre;
int*next;
vec*adj;

void dfs(int i, int p){
    pre[i] = preCount++;
    id[pre[i]] = i;
    for(int z=0;z<adj[i].sz;z++){int j = adj[i].ptr[z];
        if(j != p)
          dfs(j, i);
    }
    next[i] = preCount;
}
int main(){
    N = in_nextInt();
    K = in_nextInt();
    adj = calloc(N, sizeof(vec));
    for(int j=1; j<N; j++){
       int i = in_nextInt()-1;
       adj[i].ptr = pushback(adj[i].ptr, &adj[i].sz, j);
    }
    bool isRed[N]; memset(isRed, 0, sizeof(isRed));
    for(int i=0; i<K; i++)
       isRed[in_nextInt()-1] = true;
    preCount = 0;
    id   = calloc(N, sizeof(int));
    pre  = calloc(N, sizeof(int));
    next = calloc(N, sizeof(int));
    dfs(0, 0);
    int curLevel[N+1]; memset(curLevel, 0, sizeof(curLevel));
    int nxtLevel[N+1]; memset(nxtLevel, 0, sizeof(nxtLevel));
    curLevel[0] = 1;
    for(int k=0; k<=K; k++){
        for(int i=0; i<N; i++){
            int cur = id[i];
            curLevel[i+1] += curLevel[i];
            curLevel[i+1] %= MODO;
            if(!isRed[cur]){
               int nxt = next[cur];
               curLevel[nxt] += curLevel[i];
               curLevel[nxt] %= MODO;
            }
        }
        printf("%d\n", curLevel[N]);
        fill(nxtLevel, N+1, 0);
        for (int i=N-1; i>=0; i--){
            int cur = id[i];
            if (isRed[cur]){
               int nxt = next[cur];
               nxtLevel[nxt] += curLevel[i];
               nxtLevel[nxt] %= MODO;
            }
        }
        for (int i=0; i<=N; i++)
           curLevel[i] = nxtLevel[i];
    }
    return 0;
}

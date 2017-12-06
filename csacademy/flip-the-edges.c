#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int compP( pair a, pair b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}
pair min(pair a,pair b){return compP(a,b)<0?a:b;}



////////////////////////////
enum{ MAXN =  100000};
enum{ INF  = 1000000};
vecp g   [1+MAXN];
bool seen[1+MAXN];
pair dp  [1+MAXN][2];


int Read(){
    int x;
    scanf("%d", &x);
    return x;
}
pair add(pair*a, pair*b){
    return newPair(a->first + b->first, a->second + b->second);
}
pair add3(pair*a, pair*b, pair c){
    pair ab = add(a, b);
    return add(&ab, &c);
}
void DFS(int node, int father){
    seen[node] = true;
    dp[node][0] = newPair(0, 0);
    dp[node][1] = newPair(INF, INF);
    for(int z=0;z<g[node].sz;z++){pair x = g[node].ptr[z];
        if (!seen[x.first]) {
            int son = x.first;
            DFS(x.first, node);
            pair new0, new1;
            if (x.second == 1) {
                new0 = min(min(add3(&dp[node][0], &dp[son][0], newPair(1,  1)), 
                               add3(&dp[node][0], &dp[son][1], newPair(0,  1))), 
                           min(add3(&dp[node][1], &dp[son][0], newPair(0,  1)), 
                               add3(&dp[node][1], &dp[son][1], newPair(-1, 1)))
                           );
                new1 = min(min(add3(&dp[node][1], &dp[son][0], newPair(1, 1)), 
                               add3(&dp[node][1], &dp[son][1], newPair(0, 1))), 
                           min(add3(&dp[node][0], &dp[son][0], newPair(1, 1)), 
                               add3(&dp[node][0], &dp[son][1], newPair(0, 1))));
            }
            else {
                new0 = min(add(&dp[node][0], &dp[son][0]), 
                           add3(&dp[node][1], &dp[son][1], newPair(-1, 1)));
                new1 = min(add3(&dp[node][0], &dp[son][1], newPair(0, 1)), 
                           add(&dp[node][1], &dp[son][0]));
            }
            dp[node][0] = new0;
            dp[node][1] = new1;
        }
    }
}
int main(){
    int n = Read();
    for (int i = 1; i < n; i++) {
        int a = Read(), b = Read(), c = Read(), d = Read();
        if (d != 2)
            if (c + d == 1)
                d = 1;
            else
                d = 0;
        if (d){
            g[a].ptr = pushbackP(g[a].ptr, &g[a].sz, newPair(b, d));
            g[b].ptr = pushbackP(g[b].ptr, &g[b].sz, newPair(a, d));
        }
    }
    int best = 0, sum = 0;
    for (int i = 1; i <= n; i++)
        if (!seen[i]) {
            DFS(i, 0);
            best += dp[i][0].first;
            sum  += dp[i][0].second;
        }
    printf("%d %d\n", best, sum);
    return 0;
}



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ MAX_N = 100000};
int n;
int*graph[MAX_N];
int sizes[MAX_N];
int vis  [MAX_N];
int dp   [MAX_N][3];

void checkMax(int*a, int b){
    *a = max(*a, b);
}
void dfs(int node){
    vis[node]   = true;
    dp[node][2] = -1;
    int*sons=NULL;int sonsSz=0;
    for(int i=0;i<sizes[node];i++){
        int it=graph[node][i];
        if (!vis[it]) {
            sons=pushback(sons,&sonsSz,it);
            dfs(it);
        }
    }
    for(int i=0;i<sonsSz;i++){int it=sons[i]; dp[node][0] += max(dp[it][1], dp[it][2] + 1); }
    int sonSum = 0;
    for(int i=0;i<sonsSz;i++){int it=sons[i]; sonSum += dp[it][1];}
    for(int i=0;i<sonsSz;i++){int it=sons[i]; checkMax(&dp[node][2], sonSum - dp[it][1] + max(dp[it][0], dp[it][2]));}
    for(int i=0;i<sonsSz;i++){int it=sons[i]; dp[node][1] += dp[it][1];}
    if(sonsSz < 2) 
        return;
    sonSum = 0;
    for(int i=0;i<sonsSz;i++){int it=sons[i]; sonSum += max(max(dp[it][0], dp[it][1]), dp[it][2]);};
    int*lostScore=NULL;int lostScoreSz=0;
    for(int i=0;i<sonsSz;i++){
        int it=sons[i]; 
        lostScore=pushback(lostScore,&lostScoreSz,max(max(dp[it][0], dp[it][1]), dp[it][2]) - max(dp[it][0], dp[it][2]));
    }
    qsort(lostScore, lostScoreSz,sizeof(int), cmp);
    checkMax(&dp[node][1], 1 + sonSum - lostScore[0] - lostScore[1]);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        assert(1 <= a && a <= n);
        assert(1 <= b && b <= n);
        assert(a != b);
        --a; --b;
        graph[a]=pushback(graph[a], sizes+a, b);
        graph[b]=pushback(graph[b], sizes+b, a);
    }
    dfs(0);
    int rez = max(max(dp[0][0], dp[0][1]), dp[0][2]);
    printf("%d\n", rez);
}






























































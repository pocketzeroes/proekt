#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>


typedef long long LL;
#define MAXN 335
int N, M;
bool adj[MAXN][MAXN];
int root;
int parent[MAXN];
bool visited[MAXN];

void solve(int v) {
    int p = parent[v];
    for (int i = 0; i < N; i++) {
        if (adj[v][i] && adj[p][i] && !visited[i]) {
            parent[i] = v;
            visited[i] = true;
        }
    }
    for (int i = 0; i < N; i++) {
        if (parent[i] == v) {
            solve(i);
        }
    }
}
int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        A--; B--;
        adj[A][B] = adj[B][A] = true;
    }
    for (int i = 0; i < N; i++) {
        bool ok = true;
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if (adj[i][j] && adj[i][k] && !adj[j][k]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) 
                break;
        }
        if (ok) {
            root = i;
            break;
        }
    }
    for(int i = 0; i < N; i++){
        if (i == root) 
            continue;
        memset(parent, -1, sizeof parent);
        memset(visited, 0, sizeof visited);
        visited[root] = visited[i] = true;
        parent[i] = root;
        solve(i);
        bool bad = false;
        for(int j = 0; j < N; j++){
            if (!visited[j]) 
                bad = true;
        }
        if (bad) 
            continue;
        break;
    }
    for(int i = 0; i < N; i++){
        if(~parent[i]){
            printf("%d %d\n", i+1, parent[i]+1);
        }
    }
    return 0;
}



















































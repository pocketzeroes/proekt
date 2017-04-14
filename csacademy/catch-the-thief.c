#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>

int min(int a,int b){return a<b?a:b;}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

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

int cmp( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}
pair max( pair a, pair b){
    if( cmp(a,b) > 0 )
        return a;
    else 
        return b;
}


enum{ MAXN = 2500      };
enum{ INF  = 1000000000};
int*g    [1+MAXN];
int sizes[1+MAXN];
int*solution;
int solutionSz;
int seen[1 + MAXN], color[1 + MAXN], depth[1 + MAXN], up[1 + MAXN];
bool bad;







pair DFS(int node, int number) {
    pair answer = newPair(0, node);
    seen[node] = number;
    for(int i=0;i<sizes[node];i++){ int son=g[node][i];
        if (seen[son] != number) {
            pair current = DFS(son, number);
            current.first++;
            answer = max(answer, current);
        }
    }
    return answer;
}
bool MakeTree(int node, int last) {
    bool ok = false;
    seen[node] = 3;
    if (node == last)
        ok = true;
    for(int i=0;i<sizes[node];i++){ int son=g[node][i];
        if (seen[son] != 3) {
            depth[son] = depth[node] + 1;
            if (MakeTree(son, last)) {
                color[node] = 1 ^ color[son];
                ok = true;
            }
        }
        if (abs(depth[node] - depth[son]) > 1)
            bad = true;
    }
    if (!ok)
        up[node] = INF;
    return ok;
}
void GetDistance(int node) {
    seen[node] = 4;
    for(int i=0;i<sizes[node];i++){ int son=g[node][i];
        if (seen[son] != 4) {
            up[son] = min(up[son], 1 + up[node]);
            GetDistance(son);
        }
    }
    if (up[node] > 2)
        bad = true;
}
void SolveChain(int node, int number, bool*current){
    seen[node] = number;
    for(int i=0;i<sizes[node];i++){ int son=g[node][i];
        if (up[son]) {
            if (color[node] == *current){
                solution=pushback(solution,&solutionSz,node);
                (*current) ^= 1;
            }
            solution=pushback(solution,&solutionSz,son);
            (*current) ^= 1;
        }
    }
    if (color[node] == *current) {
        solution=pushback(solution,&solutionSz,node);
        (*current) ^= 1;
    }
    for(int i=0;i<sizes[node];i++){ int son=g[node][i];
        if (!up[son] && seen[son] != number) {
            SolveChain(son, number, current);
            return;
        }
    }
}
void Solve(int node) {
    pair one = DFS(node, 1);
    pair two = DFS(one.second, 2);
    MakeTree(one.second, two.second);
    GetDistance(one.second);
    if (bad) {
        puts("-1");
        exit(0);
    }
    bool current = false;
    SolveChain(one.second, 5, &current);
    current ^= 1;
    SolveChain(one.second, 6, &current);
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a]=pushback(g[a], sizes+a, b);
        g[b]=pushback(g[b], sizes+b, a);
    }
    for (int i = 1; i <= n; i++)
        if (!seen[i])
            Solve(i);
    printf("%d\n", solutionSz);
    for(int i=0;i<solutionSz;i++){
        int it = solution[i];
        printf("%d\n", it);
    }
    return 0;
}



























































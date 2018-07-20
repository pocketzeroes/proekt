#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

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
///////////////////////////////////
typedef long long ll;
enum{ kMaxN =(int)3e5+5};

typedef struct{
    int oth, x, y;
}Edge;
Edge newEdge(int a, int b, int c){
    Edge rez;
    rez.oth = a;
    rez.x   = b;
    rez.y   = c;
    return rez;
}
Edge*pushbackE(Edge*array, int *size, Edge value){
    Edge*output = resizeArray(array, Edge, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    Edge*ptr;
    int sz;
}vece;
vece newVecE(){
    vece rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

vece vertex[kMaxN];
bool visited[kMaxN];
ll mx = 0;
Edge edge_to_parent[kMaxN];
int n;
ll dp[kMaxN];

ll GetCost(Edge*e, int time){
    return e->x+1LL*e->y*time;
}
void Relabel(){
    vec bfs_queue = newVec();
    bfs_queue.ptr = pushback(bfs_queue.ptr, &bfs_queue.sz, 1);
    visited[1] = true;
    int first = 0;
    while(first < bfs_queue.sz){
        int node = bfs_queue.ptr[first++];
        for(int z=0;z<vertex[node].sz;z++){Edge edge = vertex[node].ptr[z];
            int initial_node = edge.oth;
            if(visited[initial_node])
                continue;
            visited[initial_node] = true;
            edge.oth = first - 1;
            edge_to_parent[bfs_queue.sz] = edge;
            bfs_queue.ptr = pushback(bfs_queue.ptr, &bfs_queue.sz, initial_node);
        }
    }
}
ll FindDiameter(int time){
    memset(dp, 0, sizeof(dp));
    ll mx_ans = 0;
    for(int i=n-1; i>=0; i--){
        if(i == 0)
            break;
        Edge edge = edge_to_parent[i];
        int parent = edge.oth;
        ll current_cost = GetCost(&edge, time) + dp[i];
        mx_ans = max(mx_ans, dp[parent] + current_cost);
        dp[parent] = max(dp[parent], current_cost);
    }
    return mx_ans;
}
int main(){
    int d;
    scanf("%d %d", &n, &d);
    for(int i=1; i<n; i++){
        int a, b, x, y;
        scanf("%d %d %d %d", &a, &b, &x, &y);
        vertex[a].ptr = pushbackE(vertex[a].ptr, &vertex[a].sz, newEdge(b, x, y));
        vertex[b].ptr = pushbackE(vertex[b].ptr, &vertex[b].sz, newEdge(a, x, y));
    }
    Relabel();
    ll mn_diameter = (ll)1e18;
    int where = 0;
    void Update(int time, ll diameter){
        if(mn_diameter > diameter){
            mn_diameter = diameter;
            where = time;
        }
        else if(mn_diameter==diameter && time<where)
            where = time;
    }
    Update(0, FindDiameter(0));
    Update(d, FindDiameter(d));
    int a = 0;
    int b = d;
    while(b - a >= 5){
        int mid = (a + b) / 2;
        ll rezA = FindDiameter(mid);
        ll rezB = FindDiameter(mid + 1);
        Update(mid  , rezA);
        Update(mid+1, rezB);
        if(rezA > rezB)
            a = mid;
        else
            b = mid+1;
    }
    for(int i=a+1; i<=b; ++i)
        Update(i, FindDiameter(i));
    printf("%d\n%lld\n", where, mn_diameter);
    return 0;
}

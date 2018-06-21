#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef struct{
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
void erase(vec*v, int pos){
    for(int i=pos; i < v->sz-1; i++)
        v->ptr[i] = v->ptr[i+1];
    (v->sz)--;
}

////////////////////////////
typedef long long ll;
int tc, n, m, k, x, y, z, w;
ll ans, res;

typedef struct{
    int x, 
        y, 
        cost;
}node;
node edge[3000005];

node newNode(int x, int y, int cost){
    node rez;
    rez.x    = x;
    rez.y    = y;
    rez.cost = cost;
    return rez;
}
int cmpNode(const void*pa, const void*pb){
    node*a=(node*)pa;
    node*b=(node*)pb;
    return(a->cost < b->cost)?-1:1;
}

enum{ARR_SZ = 2005};
int  p        [ARR_SZ],
     f        [ARR_SZ],
     max_edge [ARR_SZ];
pair edge_pair[ARR_SZ];
vec  tree_edge[ARR_SZ],
     cost     [ARR_SZ];

int find(int x){
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}
void add(int x, int y, int c){
    tree_edge[x].ptr = pushback(tree_edge[x].ptr, &tree_edge[x].sz, y);
    tree_edge[y].ptr = pushback(tree_edge[y].ptr, &tree_edge[y].sz, x);
    cost     [x].ptr = pushback(cost     [x].ptr, &cost     [x].sz, c);
    cost     [y].ptr = pushback(cost     [y].ptr, &cost     [y].sz, c);
    ans += 1ll * c;
}
void delete_edge(pair p, int c){
    int x = p.first;
    int y = p.second;
    for(int i=0; i<tree_edge[x].sz; i++){
        if (tree_edge[x].ptr[i] != y)
            continue;
        erase(&tree_edge[x], i);
        erase(&cost[x], i);
        break;
    }
    for(int i = (0); i < tree_edge[y].sz; i++){
        if(tree_edge[y].ptr[i] != x)
            continue;
        erase(&tree_edge[y], i);
        erase(&cost[y], i);
    }
    ans -= 1ll * c;
}
void DFS(int x, int y, int max_val, pair p){
    max_edge[x] = max_val;
    edge_pair[x] = p;
    for(int i = (0); i < tree_edge[x].sz; i++){
        if (tree_edge[x].ptr[i] == y)
            continue;
        if (x == 0)
            DFS(tree_edge[x].ptr[i], x, max_val, p);
        else{
            if (cost[x].ptr[i] > max_val)
                DFS(tree_edge[x].ptr[i], x, cost[x].ptr[i], newPair(x, tree_edge[x].ptr[i]));
            else
                DFS(tree_edge[x].ptr[i], x, max_val, p);
        }
    }
}
int main (){
    scanf("%d", &tc);
    while (tc--){
        scanf("%d %d", &n, &m);
        w = 0;
        for(int i = (1); i <= (n); i++)
            scanf("%d", &x), 
            edge[w++] = newNode(0, i, x),
            f[i] = x;
        for(int i = (1); i <= (n); i++)
            for(int j = (1); j <= (n); j++){
                scanf("%d", &x);
                if (i < j)
                    edge[w++] = newNode(i, j, x);
            }
        qsort(edge, w, sizeof(node), cmpNode);
        for(int i = (0); i <= (n); i++)
            tree_edge[i].sz=0, 
            cost[i].sz=0;
        for(int i = (1); i <= (n); i++)
            p[i] = i;
        ans = 0ll;
        for(int i = (0); i < (w); i++){
            if (edge[i].x == 0 || edge[i].y == 0)
                continue;
            x = find(edge[i].x);
            y = find(edge[i].y);
            if (x == y)
                continue;
            add(edge[i].x, edge[i].y, edge[i].cost);
            p[x] = y;
        }
        x = 0;
        for(int i = (1); i <= (n); i++)
            if (x == 0 || f[i] < f[x])
                x = i;
        add(0, x, f[x]);
        res = ans;
        for(int trial = (2); trial <= (m); trial++){
            DFS(0, -1, 0, newPair(-1, -1));
            x = 0;
            for(int i = (1); i <= (n); i++){
                if (max_edge[i] == 0)
                    continue;
                if (x == 0 || f[i] - max_edge[i] < f[x] - max_edge[x])
                    x = i;
            }
            delete_edge(edge_pair[x], max_edge[x]);
            add(0, x, f[x]);
            res = min(res, ans);
        }
        printf("%lld\n", res);
    }
    return 0;
}




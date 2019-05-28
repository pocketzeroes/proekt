#include<stdio.h>
#include<stdlib.h>

enum{ MAXN = 250000};
int n;
int nedges[2*MAXN], vis[2*MAXN], evis[2*MAXN];
int vals[2*MAXN];
int iscycle;
int root;
int largest;
int lastid = 0;

struct edge{
    int s ,t ,tid ,nxt;
};
struct edge edges[MAXN*2];

int cmp(const void * a, const void * b){
   return (*(int*)a) - (*(int*)b);
}

int getid(int key){
    int *pwho = (int*)bsearch(&key, vals, lastid, sizeof(int), cmp);
    return ((int)pwho-(int)vals)/sizeof(int); 
}
void dfs(int who, int col){
    if (vis[who] == col){
        iscycle = 1;
        root = who;
    }
    else {
        int nxt = nedges[who];
        if (!iscycle && edges[nxt].s > largest) {
            largest = edges[nxt].s;
            root = who;
        }
        vis[who] = col;
        while (nxt != -1) {
            if (evis[nxt&~1] == -1) {
                evis[nxt&~1] = col;
                dfs(edges[nxt].tid, col);        
            }
            nxt = edges[nxt].nxt;
        }
    }
}
long long mdfs(int who, int col){
    long long ans = 0;
    if (vis[who] == col ) {
        return 0;
    }
    else {
        int nxt = nedges[who];
        vis[who] = col;
        while (nxt != -1) {
            if (evis[nxt&~1] != col) {
                evis[nxt&~1] = col;
                ans += mdfs(edges[nxt].tid, col) + edges[nxt].s;
            }
            nxt = edges[nxt].nxt;
        }
    }
    return ans;
}
int main(){
    int i, s, t, col;
    long long sum = 0;
    scanf("%d",&n);
    for (i = 0; i < 2*n; i++) {
        nedges[i] = -1;
        vis[i] = -1;
        evis[i] = -1;
    }
    for (i = 0; i < n; i++) {
        scanf("%d %d",&s,&t);
        edges[2*i].s = s;
        edges[2*i].t = t;
        vals[2*i] = s;
        edges[2*i+1].s = t;
        edges[2*i+1].t = s;
        vals[2*i+1] = t;            
    }
    qsort(vals, 2*n, sizeof(int), cmp);
    lastid = 1;
    for (i = 1; i < 2*n; i++) {
        if (vals[i] != vals[lastid-1]) {
            vals[lastid++] = vals[i];
        }
    }
    for (i = 0; i < 2*n; i++) {
        if (!((i&1) && edges[i].s == edges[i].t)) {
            edges[i].tid = getid(edges[i].t);        
            edges[i].nxt = nedges[getid(edges[i].s)];
            nedges[getid(edges[i].s)] = i;
        }
    }
    col = 0;
    for (i = 0; i < lastid; i++) {
        if (vis[i] == -1) {
            long long val;
            int nv, ne;
            largest = 0;
            iscycle = 0;            
            dfs(i,col++);
            val = mdfs(root, col++);
            sum += val;
        }
    }
    printf("%lld\n", sum);
    return 0;
}

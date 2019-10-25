#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

typedef long long ll;
enum{ maxn = 100000+10};
ll inf = (ll)1e18;
int n;
int tot;
int father[maxn];

typedef struct{
  ll  first;
  int second;
}pli;
pli newpli(ll a, int b){
    return(pli){a,b};
}

typedef struct{
    int x, y, id;
}pt;
pt Point[maxn<<4];

int cmpPt(const void*pa, const void*pb){
    pt*tva=(pt*)pa;
    pt*res=(pt*)pb;
    if(tva->x == res->x)
        return(tva->y < res->y)?-1:1;
    else
        return(tva->x < res->x)?-1:1;
}

typedef struct{
    int u, v;
    ll  w;
}edge;
edge Edge[maxn<<10];
int cmpE(const void*pa, const void*pb){
    edge*tva=(edge*)pa;
    edge*res=(edge*)pb;
    return(tva->w < res->w)?-1:1;
}

typedef struct{
    int l, r, id;
    ll  Min;
}node;
node Node[maxn<<6];

void add(int u, int v, ll w){
    Edge[++tot].u = u;
    Edge[tot].v   = v;
    Edge[tot].w   = w;
}
void Pushup(int i){
    int lson = i<<1;
    int rson = lson|1;
    if(Node[lson].Min <= Node[rson].Min){
        Node[i].Min = Node[lson].Min;
        Node[i].id  = Node[lson].id;
    }
    else{
        Node[i].Min = Node[rson].Min;
        Node[i].id  = Node[rson].id;
    }
}
void build(int i, int l, int r){
    Node[i].l   = l;
    Node[i].r   = r;
    Node[i].Min = inf;
    Node[i].id  = -1;
    if(l == r)
        return;
    int f = i;
    int mid = (l + r)>>1;
    i <<= 1;
    build(i, l, mid);
    build(i|1, mid + 1, r);
}
void update(int i, int loc, ll value, int id){
    if(Node[i].l == Node[i].r){
        if(value >= Node[i].Min)
            return;
        Node[i].Min = value;
        Node[i].id  = id;
        return;
    }
    int f = i;
    i <<= 1;
    if(loc <= Node[i].r)
        update(i, loc, value, id);
    else
        update(i|1, loc, value, id);
    Pushup(f);
}
pli query(int i, int l, int r){
    if(Node[i].l == l && Node[i].r == r)
        return newpli(Node[i].Min, Node[i].id);
    i <<= 1;
    if(r <= Node[i].r)
        return query(i, l, r);
    else if(l >= Node[i|1].l)
        return query(i|1, l, r);
    else{
        pli pp1 = query(i, l, Node[i].r);
        pli pp2 = query(i|1, Node[i|1].l, r);
        if(pp1.first <= pp2.first)
            return pp1;
        else
            return pp2;
    }
}
void Tran(int type){
    if(type == 1){
        qsort(Point+1, n, sizeof(pt), cmpPt);
        return;
    }
    else if(type == 2 || type == 4){
        for(int i = 1; i <= n; i++){
            swap(Point[i].x, Point[i].y);
        }
        qsort(Point+1, n, sizeof(pt), cmpPt);
        return;
    }
    else if(type == 3){
        for(int i = 1; i <= n; i++){
            Point[i].x = -Point[i].x;
        }
        qsort(Point+1, n, sizeof(pt), cmpPt);
        return;
    }
}
void getGraph(){
    for(int i = 1; i <= 4; i++){
        Tran(i);
        build(1, 0, 4000);
        for(int j = n; j >= 1; j--){
            int loc = Point[j].y - Point[j].x;
            loc += 2000;
            pli pp = query(1, loc, 4000);
            if(pp.first < inf){
                int id = pp.second;
                add(Point[j].id, id, pp.first - (ll)(Point[j].x + Point[j].y));
            }
            update(1, loc, (ll)(Point[j].x + Point[j].y), Point[j].id);
        }
    }
}
void init(){
    tot = 0;
    for(int i = 1; i <= n; i++)
        father[i] = i;
}
int Find(int x){
    if(father[x] == x)
        return x;
    else
        return father[x] = Find(father[x]);
}
ll kruscal(){
    ll ans    = 0;
    int judge = 0;
    qsort(Edge+1, tot, sizeof(edge), cmpE);
    for(int i = 1; i <= tot; i++){
        int u  = Edge[i].v;
        int v  = Edge[i].u;
        ll w   = Edge[i].w;
        int f1 = Find(u);
        int f2 = Find(v);
        if(f1 != f2){
            judge++;
            ans += w;
            father[f1] = f2;
        }
        if(judge == n - 1)
            break;
    }
    return ans;
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d%d", &Point[i].x, &Point[i].y);
        Point[i].id = i;
    }
    init();
    getGraph();
    printf("%lld\n", kruscal());
    return 0;
}

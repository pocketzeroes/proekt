#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
    ll  first;
    int second;
}Pair;
Pair make_pair(ll a, int b){
    Pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

enum{ N = 100005};
#define INF 1000000000000LL
int n,m;
int k;
int fa[N];
int cnt;
ll ans;
int tot,rt;
Pair t[N];



typedef struct{
 int x, l, r, v;
}segment;
segment Segment(int a, int b, int c, int d){
    segment rez;
    rez.x = a;
    rez.l = b;
    rez.r = c;
    rez.v = d;
    return rez;
}

segment s[N*4];
typedef struct{
 int l, r;
 Pair first, second;
 ll ad;
}node;
node tree[N*2];


int get(){
    char ch;
    while(ch=getchar(),(ch<'0'||ch>'9')&&ch!='-');
    if (ch=='-'){
        int s=0;
        while(ch=getchar(),ch>='0'&&ch<='9')
            s=s*10+ch-'0';
        return -s;
    }
    int s=ch-'0';
    while(ch=getchar(),ch>='0'&&ch<='9')
        s=s*10+ch-'0';
    return s;
}


int cmp(const void*pa, const void*pb){
    segment*a=(segment*)pa;
    segment*b=(segment*)pb;
    return (a->x < b->x)?-1:1;
}


bool cmp1(Pair a,Pair b){
    return a.first<b.first;
}
void update(int now){
    int l = tree[now].l, r = tree[now].r;
    if (cmp1(tree[l].first, tree[r].first))
        tree[now].first = tree[l].first;
    else
        tree[now].first = tree[r].first;
    int be = tree[now].first.second;
    tree[now].second = make_pair(INF, 0);
    if (tree[l].first.second  != be && cmp1(tree[l].first , tree[now].second)) tree[now].second = tree[l].first;
    if (tree[l].second.second != be && cmp1(tree[l].second, tree[now].second)) tree[now].second = tree[l].second;
    if (tree[r].first.second  != be && cmp1(tree[r].first , tree[now].second)) tree[now].second = tree[r].first;
    if (tree[r].second.second != be && cmp1(tree[r].second, tree[now].second)) tree[now].second = tree[r].second;
}
void build(int*noow, int l, int r){
    (*noow) = ++tot;
    tree[*noow].l     = tree[*noow].r = tree[*noow].ad = 0;
    tree[*noow].first = tree[*noow].second=make_pair(INF,0);
    if(l==r){
        tree[*noow].first = make_pair(0, fa[l]);
        return;
    }
    int mid = (l+r)/2;
    build(&tree[*noow].l, l  , mid);
    build(&tree[*noow].r, mid+1, r);
    update(*noow);
}
void down(int now){
    if(tree[now].ad){
        ll ad=tree[now].ad;
        int l=tree[now].l,
            r=tree[now].r;
        tree[l].ad+=ad;
        tree[r].ad+=ad;
        if (tree[l].first.second )tree[l].first.first +=ad;
        if (tree[l].second.second)tree[l].second.first+=ad;
        if (tree[r].first.second )tree[r].first.first +=ad;
        if (tree[r].second.second)tree[r].second.first+=ad;
        tree[now].ad=0;
    }
}
void change(int now, int l, int r, int x, int y, int v){
    if (x<=l&&r<=y){
        tree[now].ad=tree[now].ad+v;
        if (tree[now].first.second)
            tree[now].first.first+=v;
        if (tree[now].second.second)
            tree[now].second.first+=v;
        return;
    }
    down(now);
    int mid=(l+r)/2;
    if (x<=mid)
        change(tree[now].l,l,mid,x,y,v);
    if (y>mid)
        change(tree[now].r,mid+1,r,x,y,v);
    update(now);
}
int getfather(int x){
    if(fa[x] == x)
        return x; 
    else{
        fa[x] = getfather(fa[x]);
        return fa[x];
    }
}
void solve(){
    tot=0;
    build(&rt, 1, n);
    int w=1;
    for(int i=1;i<=n;i++)
        t[i] = make_pair(INF,0);
    for(int i=1;i<=n;i++){
        while(w<=k&&s[w].x<=i){
            change(1,1,n,s[w].l,s[w].r,s[w].v);
            w++;
        }
        Pair u;
        if (tree[1].first.second==fa[i])
            u=tree[1].second;
        else 
            u=tree[1].first;
        if (cmp1(u,t[fa[i]]))
            t[fa[i]]=u;
    }
    for(int i=1;i<=n;i++){
        int x = getfather(i);
        int y=getfather(t[x].second);
        if (x!=y){
            cnt--;
            fa[x]=y;
            ans = ans+t[x].first;
        }
    }
    for(int i=1;i<=n;i++)
        getfather(i);
}
int main(){
    n=get();
    m=get();
    for(int i=1;i<=m;i++){
        int lx=get(),
            rx=get(),
            ly=get(),
            ry=get(),
            w =get();
        s[++k] = Segment(lx  , ly, ry,  w);
        s[++k] = Segment(rx+1, ly, ry, -w);
        s[++k] = Segment(ly  , lx, rx,  w);
        s[++k] = Segment(ry+1, lx, rx, -w);
    }
    qsort(s+1, k, sizeof(segment), cmp);
    for(int i=1; i<=n; i++)
        fa[i] = i;
    cnt=n;
    for(;cnt>1;)
        solve();
    printf("%lld\n",ans);
    return 0;
}

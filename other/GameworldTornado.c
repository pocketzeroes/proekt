#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct SegmentTree{
    int li;
    int ri;
    struct SegmentTree*l;
    struct SegmentTree*r;
    ll value;
    ll score;
}SegmentTree;
SegmentTree*newSegmentTree(int l, int r){
    SegmentTree*rv=calloc(1, sizeof(SegmentTree));
    rv->li=l;
    rv->ri=r;
    return rv;
}
void update(SegmentTree*st, int f, int t, ll x){
    if(st->li > t || st->ri < f)
        return;
    if(f <= st->li && t >= st->ri)
        st->value += x;
    else{
        if(!st->l)
            st->l = newSegmentTree(st->li, (st->li + st->ri)/2);
        if(!st->r)
            st->r = newSegmentTree((st->li + st->ri)/2+1, st->ri);
        update(st->l, f, t, x);
        update(st->r, f, t, x);
    }
    if(st->l && st->r)
        st->score = st->l->score + st->r->score;
    else
        st->score = 0;
    if(st->value > 0)
        st->score = st->ri - st->li + 1;
}

typedef struct{
    int x, y1, y2, d;
}event;
int cmpE(const void*pa, const void*pb){
    event*tva = (event*)pa;
    event*oth = (event*)pb;
    return(tva->x < oth->x)?-1:1;
}
enum{ MAXN = 100000    };
enum{ MAXC = 1000000000};
int n;
event E[MAXN*2];

int main(){
    scanf("%d", &n);
    SegmentTree*tree = newSegmentTree(0, MAXC);
    for(int i=0; i<n; i++){
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        y2--;
        E[i*2]   = (event){x1, y1, y2, 1};
        E[i*2+1] = (event){x2, y1, y2, -1};
    }
    qsort(E, n*2, sizeof(event), cmpE);
    ll area = 0;
    int last_x = 0;
    for(int i=0; i<n*2; i++){
        area += tree->score * (E[i].x - last_x);
        update(tree, E[i].y1, E[i].y2, E[i].d);
        last_x = E[i].x;
    }
    printf("%lld\n", area);
    return 0;
}

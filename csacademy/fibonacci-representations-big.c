#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
typedef struct{
  pair first;
  pair second;
}quad;
quad newQuad(pair a, pair b){
  quad rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
quad mkQuad(ll v){
    quad rv;
    rv.first  = newPair(1,(v-1)/2);
    rv.second = newPair(1, v/2 );
    return rv;
}
#define MOD 1000000007LL

typedef struct node{
    ll sz,
       v,
       sum,
       p;
    struct node *l,
                *r;
    quad tr;
}node;
node*newNode(ll v){
    node*rez = malloc(sizeof(node));
    rez->sz  = 1;
    rez->v   = v;
    rez->sum = v;
    rez->l   = NULL;
    rez->r   = NULL;
    rez->p   = rand();
    rez->tr  = mkQuad(v);
    return rez;
}
node*treap = NULL;
void inc(int a);




ll sz(node*t){
    return (t == NULL ? 0 : t->sz);
}
ll sum(node* t){
    return (t == NULL ? 0 : t->sum);
}
quad get_tr(node *t){
    if(t == NULL)
        return newQuad(newPair(1,0),
                       newPair(0,1));
    return t->tr;
}
quad comp(quad a, quad b){
    return newQuad(
        newPair((a.first .first * b.first.first  + a.first .second * b.second.first ) % MOD,
                (a.first .first * b.first.second + a.first .second * b.second.second) % MOD),
        newPair((a.second.first * b.first.first  + a.second.second * b.second.first ) % MOD,
                (a.second.first * b.first.second + a.second.second * b.second.second) % MOD)
    );
}
void upd(node* t){
    if(t == NULL)
        return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    t->sum = t->v + sum(t->l) + sum(t->r);
    t->tr = comp(get_tr(t->l), comp(mkQuad(t->v), get_tr(t->r)));
}
void split(node*t, node**l, node**r, ll k){
    if(t == NULL){
        *l = NULL;
        *r = NULL;
    }
    else if(sz(t->l) < k){
        split(t->r, &t->r, r, k-sz(t->l)-1);
        *l = t;
    }
    else{
        split(t->l, l, &t->l, k);
        *r=t;
    }
    upd(t);
}
void splitsum(node *t, node**l, node**r, ll x){
    if(t == NULL){
        *l = NULL;
        *r = NULL;
    }
    else if(sum(t->l) + t->v <= x){
        splitsum(t->r, &t->r, r, x-sum(t->l)-t->v);
        *l = t;
    }
    else{
        splitsum(t->l, l, &t->l, x);
        *r = t;
    }
    upd(t);
}
void merge(node**t, node *l, node *r){
    if(l == NULL)
        *t = r;
    else if(r == NULL)
        *t = l;
    else if(l->p < r->p){
        merge(&l->r, l->r,r);
        *t = l;
    }
    else {
        merge(&r->l,l,r->l);
        *t=r;
    }
    upd(*t);
}
int has(int x){
    if(x <= 0)
        return 0;
    node *b, *c;
    splitsum(treap, &b, &c, x);
    int ans = (sum(b) == x);
    merge(&treap, b, c);
    return ans;
}
void ins(int x){
    node *b, *c;
    splitsum(treap, &b, &c, x-1);
    if(sz(c) == 0){
        ll diff = x - sum(b);
        node*cc = newNode(diff);
        merge(&treap, b, cc);
    }
    else {
        node *c1;
        split(c, &c1, &c, 1);
        ll diff1 = x - sum(b);
        ll diff2 = c1->v - diff1;
        free( c1);
        node *cc1 = newNode(diff1);
        node *cc2 = newNode(diff2);
        merge(&cc1, cc1, cc2);
        merge(&c, cc1, c);
        merge(&treap, b, c);
    }
}
void del(int x){
    node *b, *c;
    splitsum(treap, &b, &c, x-1);
    if(sz(c) == 1)
        treap = b;
    else {
        node *c1, *c2;
        split(c, &c1, &c, 1);
        split(c, &c2, &c, 1);
        ll diff = c1->v + c2->v;
        free(c1);
        free(c2);
        node *cc = newNode(diff);
        merge(&c, cc, c);
        merge(&treap, b, c);
    }
}
void weird_ins(int a){
    node *b, *c;
    splitsum(treap, &b, &c, a);
    assert(sum(b) == a);
    if(sz(c) > 0){
        node *c1;
        split(c, &c1, &c, 1);
        ll diff = c1->v + 1;
        free( c1);
        node *cc1 = newNode(diff);
        merge(&c, cc1, c);
    }
    node *s = NULL;
    node *e = NULL;
    node *cur = b;
    while(sz(cur) > 1){
        node *curl, *curr;
        split(cur, &curl, &curr, sz(cur)/2);
        if(sum(curr) == 2 * sz(curr)){
            merge(&e, curr, e);
            cur = curl;
        }
        else {
            merge(&s, s, curl);
            cur = curr;
        }
    }
    if(sz(cur) == 1){
        if(sum(cur) == 2)
            merge(&e, cur, e);
        else
            merge(&s, s, cur);
        cur = NULL;
    }
    int newupd = a - 2 * (sz(e) + 1);
    if(sz(e) > 0){
        node *trash;
        split(e, &trash, &e, 1);
        free( trash);
    }
    if(sz(s) == 0)
        s = newNode(1);
    else{
        node*sr;
        split(s, &s, &sr, sz(s) - 1);
        ll diff = sr->v + 1;
        free( sr);
        node*ss1 = newNode(diff);
        merge(&s, s, ss1);
    }
    merge(&s, s, e);
    merge(&treap, s, c);
    inc(a+1);
    inc(newupd);
}
void inc(int a){
    if(a < 0)
        return;
    if(a == 0)
        a = 1;
    if(has(a+1)){
        del(a+1);
        inc(a+2);
    }
    else if(has(a-1)){
        del(a-1);
        inc(a+1);
    }
    else if(has(a)){
        if(has(a-2))
            weird_ins(a);
        else {
            del(a);
            inc(a-2);
            inc(a+1);
        }
    }
    else
        ins(a);
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        inc(a);
        quad x = get_tr(treap);
        ll ans = (x.first.first + x.first.second) % MOD;
        printf("%lld\n", ans);
    }
}



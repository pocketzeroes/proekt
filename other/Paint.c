#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
ll in_nextLong(){
  ll x;
  scanf("%lld", &x);
  return x;
}


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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

typedef struct Node{
    ll lo, hi;
    ll min;
    struct Node*left;
    struct Node*right;
}Node;
Node*newNode(ll lo, ll hi){
    Node*rez = calloc(1, sizeof(Node));
    rez->lo = lo;
    rez->hi = hi;
    return rez;
}
void add(Node*n, ll x, ll value){
    ll mid =(n->lo + n->hi)/2LL;
    if(n->lo == n->hi){
        if(value < n->min)
            n->min = value;
    }
    else if(x<=mid){
        if(n->left==NULL)
           n->left = newNode(n->lo, mid);
        add(n->left, x, value);
        if(n->left->min < n->min)
           n->min = n->left->min;
    }
    else{
        if(n->right==NULL)
           n->right = newNode(mid+1, n->hi);
        add(n->right, x, value);
        if(n->right->min < n->min)
            n->min = n->right->min;
    }
}
ll find(Node*n, ll x){
    ll small = n->min;
    if(x < n->hi){
        ll mid = (n->lo + n->hi)/2LL;
        small=0;
        if(n->left!=NULL)
            small = find(n->left, x);
        if(x >= mid+1 && n->right!=NULL)
            small = min(small, find(n->right, x));
    }
    return small;
}
int main(){
    ll  n = in_nextLong();
    int k = in_nextInt();
    pair painters[k];
    for(int i=0; i<k; i++){
        ll a = in_nextLong();
        ll b = in_nextLong();
        painters[i] = newPair(a, b);
    }
    qsort(painters, k, sizeof(pair), cmpP);
    Node*root = newNode(1,n);
    ll best = LLONG_MAX;
    for(int z=0;z<k;z++){pair p = painters[z];
        ll min = find(root, p.first-1);
        ll cost = p.first + min-1-p.second;
        add(root, p.second, cost);
        cost += n;
        if(cost<best)
           best=cost;
    }
    printf("%lld\n", best);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define INF 1000000000000000000LL
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

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
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair *pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


#define MAXN 200010

typedef struct{
    ll minVal;
    ll sumVal;
    ll updateVal;
}SegmentNode;
SegmentNode st[MAXN*4];
ll width[MAXN];
ll gap  [MAXN];

void updateChildren(size_t cur, size_t L, size_t R);

size_t left (size_t cur){
    return  cur << 1;
}
size_t right(size_t cur){
    return (cur << 1) + 1;
}
void merge(SegmentNode*left, SegmentNode*right, SegmentNode*result){
    result->minVal = min(left->minVal, right->minVal);
    result->sumVal = left->sumVal + right->sumVal;
}
SegmentNode query(size_t cur, size_t L, size_t R, size_t LQ, size_t RQ){
    if (L >= LQ && R <= RQ)
        return st[cur];
    updateChildren(cur, L, R);
    size_t M = (L+R)/2;
    if (M < LQ)
        return query(right(cur), M+1, R, LQ, RQ);
    if (M+1 > RQ)
        return query(left(cur), L, M, LQ, RQ);
    SegmentNode leftResult = query(left(cur), L, M, LQ, RQ);
    SegmentNode rightResult = query(right(cur), M+1, R, LQ, RQ);
    SegmentNode result;
    merge(&leftResult, &rightResult, &result);
    return result;
}
void update(size_t cur, size_t L, size_t R, size_t idx, ll curGap, ll curWidth){
    if (L == idx && R == idx) {
        st[cur].minVal = curGap;
        st[cur].sumVal = curWidth;
    }
    else if (L <= idx && R >= idx) {
        size_t M = (L+R)/2;
        update(left(cur), L, M, idx, curGap, curWidth);
        update(right(cur), M+1, R, idx, curGap, curWidth);
        merge(&st[left(cur)], &st[right(cur)], &st[cur]);
    }
}
void rangeUpdate(size_t cur, size_t L, size_t R, size_t Lbound, size_t Rbound, ll val){
    if (L >= Lbound && R <= Rbound) {
        st[cur].minVal += val;
        st[cur].updateVal += val;
    }
    else if (L <= Rbound && R >= Lbound) {
        updateChildren(cur, L, R);
        size_t M = (L+R)/2;
        rangeUpdate(left(cur), L, M, Lbound, Rbound, val);
        rangeUpdate(right(cur), M+1, R, Lbound, Rbound, val);
        merge(&st[left(cur)], &st[right(cur)], &st[cur]);
    }
}
void updateChildren(size_t cur, size_t L, size_t R){
    rangeUpdate(left(cur), L, R, L, R, st[cur].updateVal);
    rangeUpdate(right(cur), L, R, L, R, st[cur].updateVal);
    st[cur].updateVal = 0;
}
void build(size_t cur, size_t L, size_t R){
    st[cur].updateVal = 0;
    if (L == R) {
        st[cur].minVal = gap[L];
        st[cur].sumVal = width[L];
    }
    else {
        size_t M = (L+R)/2;
        build(left(cur), L, M);
        build(right(cur), M+1, R);
        merge(&st[left(cur)], &st[right(cur)], &st[cur]);
    }
}
int main(){
    ll n;
    scanf("%lld", &n);
    ll t[n];
    ll h[n];
    pair t_sorted[n];
    pair h_sorted[n];
    for (ll i = 0; i < n; ++i){
        scanf("%lld %lld", &t[i], &h[i]);
        t_sorted[i] = newPair(t[i], i);
        h_sorted[i] = newPair(h[i], i);
    }
    qsort(t_sorted, n, sizeof(pair), cmpP);
    qsort(h_sorted, n, sizeof(pair), cmpP);
    ll i_to_h_idx[n];
    for (ll i = 0; i < n; ++i) {
        i_to_h_idx[h_sorted[i].second] = i;
    }
    for (ll i = 0; i < MAXN; ++i) {
        width[i] = 0;
        gap[i] = INF;
    }
    build(1, 0, n-1);
    vecp taken = newVecP();
    for (ll i = 0; i < n; ++i){
        ll cur_t      = t_sorted[i].first;
        ll cur_h      = h[t_sorted[i].second];
        ll place      = i_to_h_idx[t_sorted[i].second];
        ll sum_before = query(1, 0, n-1, 0, place).sumVal + cur_t;
        ll cur_gap    = cur_h - sum_before;
        if (cur_gap >= 0){
            if (query(1, 0, n-1, place, n-1).minVal >= cur_t) {
                taken.ptr = pushbackP(taken.ptr, &taken.sz, newPair(cur_h, cur_t));
                update(1, 0, n-1, place, cur_gap, cur_t);
                rangeUpdate(1, 0, n-1, place+1, n-1, -cur_t);
            }
        }
    }
    qsort(taken.ptr, taken.sz, sizeof(pair), cmpP);
    ll sumbefore = 0;
    for (ll i = 0; i < taken.sz; ++i){
        sumbefore += taken.ptr[i].second;
        if (sumbefore > taken.ptr[i].first){
            fprintf(stderr, "ERROR in AC solution at index %d\n", i);
        }
    }
    printf("%d\n", taken.sz);
}

#pragma GCC optimize "-O3"//https://open.kattis.com/problems/traintickets
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
enum{ inf = 1000000000};

typedef struct{
    int a[12];
}arr;
arr*costs;

typedef struct Node{
    struct Node*L,*R;
    int lo, hi;
    int res[12][12];
}Node;
void combine(int A[12][12], int B[12][12], int C[12][12]);

Node*newNode(int lo, int hi){
    Node*rv = calloc(1, sizeof(Node));
    rv->lo=lo;
    rv->hi=hi;
    if (lo + 1 == hi){
        rv->L = rv->R = NULL;
        arr co = costs[lo];
        rep(i,0,12){
            int dp[24];
            rep(j,0,24)
              dp[j] = inf;
            dp[i] = 0;
            rep(j,i,12)
              rep(k,0,12){
                dp[j+k+1] = fmin(dp[j+k+1], dp[j] + co.a[k]);
              }
            rep(j,0,12)
              rv->res[i][j] = dp[12+j];
        }
    }
    else{
        int mid = (lo + hi) / 2;
        rv->L = newNode(lo, mid);
        rv->R = newNode(mid, hi);
        combine(rv->L->res, rv->R->res, rv->res);
    }
    return rv;
}
void combine(int A[12][12], int B[12][12], int C[12][12]){
    rep(i,0,12)
      rep(j,0,12){
        int c = inf;
        rep(k,0,12)
          c = fmin(c, A[i][k] + B[k][j]);
        C[i][j] = c;
      }
}
bool contains(Node*n, int from, int to){
    if(from >= n->hi || to <= n->lo)
        return false;
    return true;
}
void query(Node*n, int from, int to, int out[12][12]){
//  assert(contains(from, to));
    if(from <= n->lo && n->hi <= to)
        memcpy(out, n->res, sizeof(n->res));
    else{
//      assert(L);
        if(contains(n->L, from, to) && contains(n->R, from, to)){
            int tempa[12][12], tempb[12][12];
            query(n->L, from, to, tempa);
            query(n->R, from, to, tempb);
            combine(tempa, tempb, out);
        }
        else if(contains(n->L, from, to))
            query(n->L, from, to, out);
        else
            query(n->R, from, to, out);
    }
}

int main(){
    int N;
    scanf("%d", &N);
    costs = calloc(N, sizeof(arr));
    rep(i,0,N){
        rep(j,0,12)
          scanf("%d", &costs[i].a[j]);
    }
    Node*tr = newNode(0, N);
    int Q;
    scanf("%d", &Q);
    rep(i,0,Q){
        int a, b;
        scanf("%d %d", &a, &b);
        --a;
        int mat[12][12];
        query(tr, a, b, mat);
        printf("%d\n", mat[0][0]);
    }
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
#define INF 2000000001
#define MAXN 101
#define MAXM 41
#define MAXK MAXM
#define MAX_NODE MAXM
#define MAX_ITEMS MAXN

typedef unsigned long long BITMASK;
#define has_bit(bit_mask, x) ((bit_mask) & (1ULL << (x)))
#define turn_on_bit(bit_mask, x) (bit_mask |= (1ULL << (x)))
#define turn_off_bit(bit_mask, x) (bit_mask &= (~(1ULL << (x))))
#define smallest_on_bit(bit_mask) (__builtin_ctzll((bit_mask) & (-(bit_mask))))

BITMASK neighbors[MAX_NODE];
bool must[MAX_NODE];
inline void add_edge(int a, int b) {
    neighbors[a] |= (1ULL << b);
    neighbors[b] |= (1ULL << a);
}

int A[MAX_ITEMS];
int P[MAX_ITEMS];
int B[MAX_ITEMS];
int Q[MAX_ITEMS];
int N,M,K;

int backtrack(BITMASK alive_stores, BITMASK chosen_stores) {
    int sz = __builtin_popcountll(chosen_stores);
    if (sz > K) return INF; 
    assert((chosen_stores & alive_stores) == 0);   
    if (sz == K || alive_stores == 0) {
        int total_cost = 0;
        int a_cost, b_cost, i_cost;
        for(int i=0; i<N; ++i) {
            a_cost = has_bit(chosen_stores, A[i]) ? P[i] : INF;
            b_cost = has_bit(chosen_stores, B[i]) ? Q[i] : INF;
            i_cost = min(a_cost, b_cost);
            if (i_cost == INF) return INF;
            total_cost += i_cost;
        }
        return total_cost;
    }
    int j = smallest_on_bit(alive_stores);
    assert(j >= 0);
    assert(has_bit(alive_stores, j));
    assert(((alive_stores >> j) << j) == alive_stores);
    int ans = INF;
    {
        BITMASK new_alive_stores = alive_stores;
        BITMASK new_chosen_stores = chosen_stores;
        turn_on_bit(new_chosen_stores, j);    
        turn_off_bit(new_alive_stores, j);    
        ans = min(ans, backtrack(new_alive_stores, new_chosen_stores));
    }
    {
        BITMASK new_alive_stores = alive_stores;
        BITMASK new_chosen_stores = chosen_stores;
        turn_off_bit(new_alive_stores, j);
        int k;
        for(BITMASK alive_neighbors = (neighbors[j] & alive_stores);  alive_neighbors;  alive_neighbors = alive_neighbors&(alive_neighbors - 1)){
            k = smallest_on_bit(alive_neighbors);
            turn_on_bit(new_chosen_stores, k);
            turn_off_bit(new_alive_stores, k);
        }
        assert((new_chosen_stores & new_alive_stores) == 0);  
        ans = min(ans, backtrack(new_alive_stores, new_chosen_stores));
    }
    return ans;
}
int main(){
    scanf("%d%d%d",&N,&M,&K);
    assert(1<=N&&N<=100);
    assert(1<=M&&M<=40);
    assert(1<=K&&K<=M);
    for(int i=0; i<N; ++i) {
        scanf("%d%d%d%d",&A[i],&P[i],&B[i],&Q[i]);
        assert(1<=A[i]&&A[i]<=M);
        assert(1<=B[i]&&B[i]<=M);
        assert(1<=P[i]&&P[i]<=10000000);
        assert(1<=Q[i]&&Q[i]<=10000000);
        A[i]--; B[i]--; 
        add_edge(A[i],B[i]);
        if (A[i] == B[i]) must[A[i]] = true;  
    }
    BITMASK alive_stores = (1ULL << M) - 1; 
    BITMASK chosen_stores = 0;              
    for(int j=0; j<M; ++j) {
        if (!neighbors[j]) turn_off_bit(alive_stores, j);
        if (must[j]) turn_on_bit(chosen_stores, j), turn_off_bit(alive_stores, j);
    }
    int ans = backtrack(alive_stores, chosen_stores);
    if (ans >= INF) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}

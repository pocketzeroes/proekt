#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define bit_set(a,b) ((a) |= (1ULL<<(b)))
#define bit_clr(a,b) ((a) &= ~(1ULL<<(b)))

typedef long long ll;
typedef ll bitset20;
enum{ max_n = 20};

int main(){
    int tn;
    for(scanf("%d", &tn); tn--;){
        int n;
        scanf("%d", &n);
        bitset20 adj[n]; memset(adj, 0, sizeof(adj));
        for (int i = 0; i < n; i++){
            int d;
            for(scanf("%d", &d); d--;){
                int v;
                scanf("%d", &v);
                bit_set(adj[i], v-1);
            }
            bit_set(adj[i], i);
        }
        int best = n;
        for(int i = 0; i < (1 << n); i++){
            int nb = 0;
            bitset20 covered=0;
            for(int j = 0; j < n; j++){
                if(i & (1 << j)){
                    covered |= adj[j];
                    nb++;
                }
            }
            if(__builtin_popcountll(covered) == n && best > nb)
                best = nb;
        }
        printf("%d\n", best);
    }
    return 0;
}

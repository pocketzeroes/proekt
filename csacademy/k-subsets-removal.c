#include <assert.h>
#include <stdio.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ MAX_N   = 1000};
enum{ MAX_VAL = 1000};
int n, k;
int v[MAX_N];
int freq[MAX_VAL + 1];

void read(){
    scanf("%d %d", &n, &k);
    assert(1 <= k && k <= n && n <= MAX_N);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
        assert(1 <= v[i] && v[i] <= MAX_VAL);
    }
}
int main(){
    read();
    for (int i = 0; i < n; ++i){
        ++freq[v[i]];
    }
    int best = 0;
    for (int i = 1; i <= MAX_VAL; ++i){
        best = max(best, freq[i] % k);
    }
    printf("%d", best);
}

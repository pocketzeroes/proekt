#include<stdio.h>
#include<assert.h>

typedef long long ll;
ll solve(int N, int L[]){
    int i, j, k, elem;
    ll memo[50], res = 0;
    for (i = 1; i < N; ++i){
        if (L[i] >= L[i - 1])
            continue;
        for (j = 0; j <= i; ++j){
            memo[j] = 0;
            for (k = 0; L[k] < L[j]; ++k)
                memo[j] += 1 + memo[k];
        }
        res += 1 + memo[i];
        elem = L[i];
        for(j = i; j > 0 && L[j - 1] > elem; --j)
            L[j] = L[j - 1];
        L[j] = elem;
    }
    return res;
}
int main(){
    int cases = 0, res = scanf("%d", &cases);
    assert(res == 1);
    assert(0 < cases && cases <= 100);
    while (cases-- > 0){
        int N = 0, L[50] = { 0 }, n;
        ll answer;
        res = scanf("%d", &N);
        assert(res == 1);
        assert(1 <= N && N <= 50);
        for (n = 0; n < N; ++n){
            res = scanf("%d", &L[n]);
            assert(res == 1);
            assert(1 <= L[n] && L[n] <= 1000);
        }
        answer = solve(N, L);
        assert(answer >= 0);
        printf("%lld\n", answer);
    }
    return 0;
}

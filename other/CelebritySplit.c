#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}


int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
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
int N;
ll*A;
ll*suf;
ll ans;

void solve(int i, ll a, ll b, ll c){
    if (c >= ans || abs(a - b) > suf[i])
        return;
    if (a == b)
        ans = min(ans, c + suf[i]);
    if (i == N)
        return;
    if (a != b && a > 0)
        solve(i + 1, a, b + A[i], c);
    solve(i + 1, a + A[i], b, c);
    solve(i + 1, a, b, c + A[i]);
}
int main(){
    while(true){
        N = in_nextInt();
        if(N == 0)
            return 0;
        A   = calloc(N,   sizeof(ll));
        suf = calloc(N+1, sizeof(ll));
        ans = LLONG_MAX;
        for(int i = 0; i < N; i++)
            A[i] = in_nextLong();
        qsort(A, N, sizeof(ll), cmpLL);
        for(int i = 0; i <= N / 2; i++){
            ll temp = A[i];
            A[i] = A[N - i - 1];
            A[N - i - 1] = temp;
        }
        suf[N] = 0;
        for(int i = N - 1; i >= 0; i--)
            suf[i] = suf[i + 1] + A[i];
        solve(0, 0, 0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}



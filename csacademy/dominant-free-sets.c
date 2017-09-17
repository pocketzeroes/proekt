#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
///////////////
enum{ N   = 100000      };
enum{ MOD = (int)1e9 + 7};
int F[N];

void add(int x, int v){
    for (; x < N; x = (x | (x + 1)))
        F[x] = (F[x] + v) % MOD;
}
int get(int x){
    int res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        res = (res + F[x]) % MOD;
    return res;
}
int main(){
    int n;
    scanf("%d", &n);
    pair a[n];
    for (int i = 0; i < n; i++){
        scanf("%d %d", &a[i].first, &a[i].second);
        a[i].first--; a[i].second--;
    }
    qsort(a, n, sizeof(pair), cmpP);
    int ans = 0;
    for (int i = 0; i < n; i++){
        int cnt = (1 + (get(N - 1) - get(a[i].second) + MOD) % MOD) % MOD;
        add(a[i].second, cnt);
        ans = (ans + cnt) % MOD;
    }
    printf("%d\n", ans);
    return 0;
}











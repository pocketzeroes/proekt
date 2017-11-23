#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

typedef struct{
  ll first;
  ll second;
}pair;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

int main() {
    int n;
    scanf("%d", &n);
    pair v[n];
    for (int i = 0; i < n; i++) 
        scanf("%lld %lld", &v[i].first, &v[i].second);
    qsort(v, n, sizeof(pair), cmpP);
    ll left [n]; memset(left , 0, sizeof(left ));
    ll right[n]; memset(right, 0, sizeof(right));
    for(int i = 1, j = n - 2; i < n; i++, j--){
        ll d1 = v[i].first - v[i - 1].second; left [i] = i * d1 + left [i - 1];
        ll d2 = v[j + 1].first - v[j].second; right[j] = i * d2 + right[j + 1];
    }
    ll ans = LLONG_MAX;
    for (int i = 0; i < n; i++)
        ans = min(ans, left[i] + right[i]);
    printf("%lld\n", ans);
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  ll  first;
  int second;
}pair;

int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

enum{ MAXN = 100000};
enum{ MAXM = 100000};
int n, m;
ll w[MAXN];
pair mongers[MAXM];

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        scanf("%lld", &w[i]);
        w[i] *= -1;
    }
    for(int i=0; i<m; i++){
        scanf("%d %lld", &mongers[i].second, &mongers[i].first);
        mongers[i].first *= -1;
    }
    qsort(w, n, sizeof(ll), cmpLL);
    qsort(mongers, m, sizeof(pair), cmpP);
    ll res = 0ll;
    for(int i = 0, j = 0; i < n && j < m;){
        if(mongers[j].second == 0){
            j++;
            continue;
        }
        res += mongers[j].first * w[i];
        mongers[j].second--;
        i++;
    }
    printf("%lld\n", res);
    return 0;
}

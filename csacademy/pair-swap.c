#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int cmp(const void*pa, const void*pb){
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? -1:1;
}

enum{ MAX = 100009};
enum{ MOD =(int) 1e9+7 };
int main(){
    ll n, d; 
    scanf("%lld %lld", &n, &d);
    ll a[MAX] ={0}, ca[MAX] ={0};
    for(ll i = 0; i < (n); ++i){
      scanf("%lld", &a[i]);
      ca[i] = a[i];
    }
    qsort(ca, n, sizeof(ll), cmp);
    ll j;
    for (j = 0; j < n; j++){
        if(a[j] != ca[j]) 
            break;
    }
    if(j+d < n)
        ;
    else
      d = n-1-j;
    for(; j+d < n; j++){
      ll min = 10000000, ind = -1;
      for(ll k = j; k <= (j+d); ++k){
        if(a[k] <= min){
          min = a[k]; ind = k;
        }
      }
      if(ind != j){
        ll tmp = a[ind];
        a[ind] = a[j];
        a[j] = tmp;
        for(ll i = 0; i < (n); ++i){
          printf("%lld ", a[i]);
        }
        puts("");
        return 0;
      }
    }
    return 0;
}




















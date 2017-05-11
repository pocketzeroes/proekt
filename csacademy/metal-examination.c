#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll _gcd(ll u, ll v ){
  return v != 0?_gcd(v, u%v):u;
}

typedef struct MetalS{
    int price, quantity;
}Metal;
int cmpM(const void*pb,const void*pa){
    Metal*rhs=(Metal*)pa;
    Metal*lhs=(Metal*)pb;
    return(1LL*lhs->quantity*rhs->price < 1LL*rhs->quantity*lhs->price)?-1:1;
}
int main(){
    int n, g; 
    scanf("%d %d", &n, &g);
    Metal metal[n];
    for(int i=0;i<n;i++){
        scanf("%d %d", &metal[i].price, &metal[i].quantity);
    }
    qsort(metal,n,sizeof(Metal),cmpM);
    ll suffix_cost[n];
    memset(suffix_cost,0,sizeof(suffix_cost));
    for(int i = n - 2; i >= 0; i -= 1){
        suffix_cost[i] = suffix_cost[i + 1] + metal[i + 1].price;
    }
    ll total_weight = 0;
    for(int i=0;i<n;i++){Metal itr = metal[i];
        total_weight += itr.quantity;
    }
    ll best_ans  = 0;
    ll total_ans = 0;
    for (int i = 0, G = g; i < n; i += 1){
        G -= metal[i].quantity;
        total_ans += 1LL * G * metal[i].price;
    }
    for (int i = 0, G = g; i < n; i += 1){
        G -= metal[i].quantity;
        ll current_ans = total_ans;
        current_ans -= 1LL * G * metal[i].price;
        current_ans += 1LL * suffix_cost[i] * metal[i].quantity;
        current_ans += 1LL * metal[i].price * (g - total_weight + metal[i].quantity);
        if (best_ans < current_ans) {
            best_ans = current_ans;
        }
    }
    ll gcd = _gcd(best_ans, 1LL * n);
    printf("%lld %lld\n", best_ans/gcd, n/gcd);
}



























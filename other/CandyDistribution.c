#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
typedef struct{
  ll   first;
  pair second;
}trip;
trip newTrip(ll a, pair b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

trip eea(ll a, ll b){
    if(b == 0)
        return newTrip(a, newPair(1, 0));
    trip p = eea(b, a % b);
    ll s = p.second.first, 
       t = p.second.second;
    return newTrip(p.first, newPair(t, s - t * (a / b)));
}
int main(){
    int numCases;
    scanf("%d", &numCases);
    while (numCases-- > 0){
        ll K, C;
        scanf("%lld %lld", &K, &C);
        if (C == 1){
            printf("%lld\n", K + 1);
            continue;
        }
        else if (K == 1){
            puts("1");
            continue;
        }
        trip extEuclid = eea(C, K);
        if (extEuclid.first != 1)
            puts("IMPOSSIBLE");
        else
            printf("%lld\n", (extEuclid.second.first + K) % K);
    }
    return 0;
}

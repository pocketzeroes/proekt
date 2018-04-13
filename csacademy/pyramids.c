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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

enum{ N = (int) (1e5 + 5)};
ll n, r, c;
ll result;
pair pyr[N];

inline ll area(pair*p){
    ll s = (-p->second - p->first) >> 1;
    return s * s;
}
int main(){
    scanf("%lld", &n);
    for (int i=0; i<n; i++){
        scanf("%lld %lld", &r, &c);
        pyr[i] = newPair(c-r, -c-r);
    }
    qsort(pyr, n, sizeof(pair), cmpP);
    ll y;
    int j = 0;
    for(int i=0; i<n; i++){
        if (i == 0 || pyr[i].second < pyr[j].second){
            result += area(&pyr[i]);
            if (i > 0){
                if ((y = -pyr[j].second - pyr[i].first) > 1) {
                    if (y & 1) {
                        y = (y + 1) / 2;
                        result -= y * (y - 1);
                    }
                    else {
                        y /= 2;
                        result -= y * y;
                    }
                }
            }
            j = i;
        }
    }
    printf("%lld\n", result);
    return 0;
}

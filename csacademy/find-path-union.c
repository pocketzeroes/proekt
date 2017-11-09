#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct pair{
    ll  first;
    int second;
}pair;
pair newPair(ll a, int b){
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

int main(){
    int n;
    scanf("%d", &n);
    pair s[n];
    for(int i = 0; i < n; i++){
        ll x;
        scanf("%lld", &x);
        ll  t   = 0;
        int len = 0;
        ll  q   = 1;
        while(x > 1){
            if(x % 2)
                t += q;
            q *= 2;
            len++;
            x /= 2;
        }
        t <<= (63 - len);
        s[i] = newPair(t, len);
    }
    qsort(s, n, sizeof(pair), cmpP);
    int res = 0;
    pair last = newPair(0LL, 0);
    for(int i=0; i<n; i++){pair ss = s[i];
        int j = 0;
        while(j < ss.second && j < last.second && (last.first & (1l << (62 - j))) == (ss.first & (1l << (62 - j))))
            j++;
        res += ss.second - j;
        last = ss;
    }
    printf("%d", res);
    return 0;
}




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
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
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

enum{ MOD = 10007};
int itable[MOD];
int ftable[MOD];

ll mod(ll a, ll m){
    a %= m;
    if (a < 0)
        a += m;
    return a;
}
ll inverse(ll a, ll m){
    a = mod(a, m);
    if (a == 1)
        return 1;
    return mod((1 - m * inverse(m % a, a)) / a, m);
}
void setup(){
    itable[0] = 0;
    ftable[0] = 1;
    for (int i = 1; i < MOD; i++){
        itable[i] = inverse(i, MOD);
        ftable[i] = (ftable[i - 1] * i) % MOD;
    }
}
void factorial(int n, int*p, int*m){
    if(n < MOD){
       *p = 0;
       *m = ftable[n];
    }
    else{
        int s = n / MOD;
        factorial(s, p, m);
        (*p) += s;
        (*m) = (*m * ftable[n % MOD]) % MOD;
        if (s & 1)
           *m = mod(- *m, MOD);
    }
}
int choose(int n, int r){
    int pa, pb, pc;
    int ma, mb, mc;
    if (r < 0 || r > n)
        return 0;
    factorial(n,     &pa, &ma);
    factorial(r,     &pb, &mb);
    factorial(n - r, &pc, &mc);
    if (pa > pb + pc)
        return 0;
    mb = (mb * mc) % MOD;
    return (ma * itable[mb]) % MOD;
}
ll countit(ll x, ll y){
    if (x < 0 || y < 0)
        return 0;
    int man = x + y;
    if (man % 3)
        return 0;
    x -= man / 3;
    y -= man / 3;
    return choose(x + y, x);
}
int main(){
    int cases;
    scanf("%d", &cases);
    setup();
    for (int cas = 0; cas < cases; cas++){
        int H, W, R;
        scanf("%d %d %d", &H, &W, &R);
        pair rocks[R+1];
        pair end   = newPair(H, W);
        pair start = newPair(1, 1);
        for(int i = 0; i < R; i++)
            scanf("%d %d", &rocks[i].first, &rocks[i].second);
        qsort(rocks, R, sizeof(pair), cmpP);
        rocks[R] = end;
        ll ans = 0;
        for(int i = (1 << R); i < (2 << R); i++){
            ll cur = 1;
            pair pos = start;
            for(int j = 0; j <= R; j++){
                if(i & (1 << j)){
                    int dr = rocks[j].first  - pos.first;
                    int dc = rocks[j].second - pos.second;
                    cur = (cur * countit(dr, dc)) % MOD;
                    pos = rocks[j];
                }
            }
            if(__builtin_parity(i))
                ans += cur;
            else
                ans -= cur;
        }
        printf("Case #%d: ", cas + 1);
        printf("%lld\n", mod(ans, MOD));
    }
    return 0;
}

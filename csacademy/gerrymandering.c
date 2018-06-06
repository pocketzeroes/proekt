#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;
enum{ N = 1000*1000 + 7};
ll test;
ll n;
ll t[N],T[N];
ll res;

int main(){
    scanf("%lld", &n);
    for(ll i = 1; i <= (n); ++i){
        char c, C;
        getchar();
        scanf("%c %c", &c, &C);
        if (c == 'A')
            t[i] = 1;
        else
            t[i] = -1;
        T[i] = (C == 'L');
    }
    ll last = 1;
    for(ll i = 1; i <= (n); ++i){
        if (T[i] == 0)
            continue;
        ll akt = 0;
        for(ll j = last; j <= (i); ++j)
            akt += t[j];
        ll best = akt;
        ll akt1 = akt;
        bool czyost = 1;
        for(ll j = i+1; j <= (n); ++j){
            if (T[j]){
                czyost = 0;
                break;
            }
            akt1 += t[j];
            best = max(best,akt1);
        }
        if (czyost){
            for(ll j = i+1; j <= (n); ++j)
                akt += t[j];
            res += (akt >= 0);
            break;
        }
        ll gdzie;
        if (best >= 0){
            res++;
            akt1 = akt, best = (akt >= 0 ? akt : 1000000007), gdzie = i;
            for(ll j = i+1; j <= (n); ++j){
                if (T[j])
                    break;
                akt1 += t[j];
                if (akt1 >= 0){
                    if (akt1 < best){
                        best = akt1;
                        gdzie = j;
                    }
                }
            }
            last = gdzie+1;
        }
        else{
            akt1 = akt, best = akt, gdzie = i;
            for(ll j = i+1; j <= (n); ++j){
                if (T[j])
                    break;
                akt1 += t[j];
                if (akt1 < best){
                    best = akt1;
                    gdzie = j;
                }
            }
            last = gdzie+1;
        }
    }
    printf("%lld\n", res);
    return 0;
}


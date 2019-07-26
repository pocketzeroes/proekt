#include<stdio.h> //"shares" swerc 2012
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


ll calculate_gcd(ll a, ll b){
    if (b == 0)
        return a;
    return calculate_gcd (b, a % b);
}
ll*shares_dyn_act,
  *shares_dyn_prev,
  *shares_dyn_aux;

int main(){
    ll capital;
    scanf("%lld", &capital);
    int actions;
    scanf("%d", &actions);
    int packs;
    scanf("%d", &packs);
    vecp shares = newVecP();
    for(int i=0; i<actions; ++i){
        pair a = newPair(0,0);
        scanf("%lld %lld", &a.first, &a.second);
        shares.ptr = pushbackP(shares.ptr, &shares.sz, a);
    }
    vecp packets = newVecP();
    ll gcd = -1;
    for(int i=0; i<packs; ++i){
        int sec;
        scanf("%d", &sec);
        pair p=newPair(0,0);
        for(int j=0; j<sec; ++j){
            pair a=newPair(0,0);
            int aux;
            scanf("%d %lld", &aux, &a.second);
            a.first = aux-1;
            p.first  += (ll) a.second *(shares.ptr[a.first].second - shares.ptr[a.first].first);
            p.second += (ll) a.second * shares.ptr[a.first].first;
        }
        if(p.first <= 0)
            continue;
        if(p.second > capital)
            continue;
        if(p.second < 0)
            puts("Problem!!!");
        packets.ptr = pushbackP(packets.ptr, &packets.sz, p);
        if(gcd == -1)
            gcd = p.second;
        else if(p.second >= 0)
            gcd = calculate_gcd(gcd, p.second);
    }
    if(packets.sz == 0){
        printf("0\n");
        return 0;
    }
    ll newCapital = capital/gcd;
    shares_dyn_prev = (ll *) calloc (newCapital + 1, sizeof(ll));
    if(shares_dyn_prev == NULL ){
        puts("Problema 3");
        return EXIT_FAILURE;
    }
    shares_dyn_act = (ll *) calloc (newCapital + 1, sizeof(ll));
    if (shares_dyn_act == NULL ){
        puts("Problema 4");
        return EXIT_FAILURE;
    }
    ll second, newcost, costeAnt;
    for(int i = 1; i <= packets.sz; ++i){
        second = gcd;
        newcost = packets.ptr[i-1].second/gcd;
        for (ll j = 1; second <= capital && j <= newCapital; ++j) {
            costeAnt = j - newcost;
            if(second < packets.ptr[i-1].second)
                shares_dyn_act[j] = shares_dyn_prev[j];
            else {
                if (shares_dyn_prev[j] < shares_dyn_prev[costeAnt] + packets.ptr[i-1].first){
                    shares_dyn_act [j] = shares_dyn_prev[costeAnt] + packets.ptr[i-1].first;
                    if (shares_dyn_act[j] < 0)
                        puts(" Problema ERR");
                }
                else
                    shares_dyn_act[j] = shares_dyn_prev[j];
            }
            second += gcd;
            if (shares_dyn_act[j-1]>shares_dyn_act[j])
                shares_dyn_act[j] = shares_dyn_act[j-1];
        }
        shares_dyn_aux  = shares_dyn_act;
        shares_dyn_act  = shares_dyn_prev;
        shares_dyn_prev = shares_dyn_aux;
    }
    printf("%lld\n", shares_dyn_prev[newCapital]);
    return 0;
}

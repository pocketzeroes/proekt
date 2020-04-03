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
  ll first, second, third;
}trip;
trip newtrip(ll a, ll b, ll c){
  return(trip){a,b,c};
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
ll fib[88] ={
 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352ll,
 24157817ll, 39088169ll, 63245986ll, 102334155ll, 165580141ll, 267914296ll, 433494437ll, 701408733ll, 1134903170ll, 1836311903ll, 2971215073ll, 4807526976ll, 7778742049ll, 12586269025ll, 20365011074ll, 32951280099ll,
 53316291173ll, 86267571272ll, 139583862445ll, 225851433717ll, 365435296162ll, 591286729879ll, 956722026041ll, 1548008755920ll, 2504730781961ll, 4052739537881ll, 6557470319842ll, 10610209857723ll, 17167680177565ll,
 27777890035288ll, 44945570212853ll, 72723460248141ll, 117669030460994ll, 190392490709135ll, 308061521170129ll, 498454011879264ll, 806515533049393ll, 1304969544928657ll, 2111485077978050ll, 3416454622906707ll,
 5527939700884757ll, 8944394323791464ll, 14472334024676221ll, 23416728348467685ll, 37889062373143906ll, 61305790721611591ll, 99194853094755497ll, 160500643816367088ll, 259695496911122585ll, 420196140727489673ll,
 679891637638612258ll
};

void solve1(ll n){
    puts("YES");
    vect ans = newVecT();//of trip ll
    for(ll i=1; i<=62; i++)
        for(ll j=i+1; j<=62; j++)
           pbt(ans, newtrip(i, j, j-i));
    for(ll i=0; i<=60; i++){
        if(n&(1LL<<i)){
            ll w = 63 - (i+2);
            ll e = i+2;
            pbt(ans, newtrip(63, e, w));
        }
    }
    printf("63 %d\n", ans.sz);
    for(int z=0; z<ans.sz; z++){trip xyz=ans.ptr[z];
        ll x = xyz.first;
        ll y = xyz.second;
        ll z = xyz.third;
        if     (x == 63) x =  2;
        else if(x ==  2) x = 63;
        if     (y == 63) y =  2;
        else if(y ==  2) y = 63;
        printf("%lld %lld %lld\n", x, y, z);
    }
}
void solve2(ll n){
    puts("YES");
    vect ans=newVecT();//of trip ll
    for(ll i=2; i<=87; i++){
        pbt(ans, newtrip(i-1, i, 1));
        if(i == 2)
            continue;
        pbt(ans, newtrip(i-2, i, 2));
    }
    for(ll i=87; i>0; i--){
        if(n >= fib[i]){
           n -= fib[i];
           pbt(ans, newtrip(88, i, 88 - i));
        }
    }
    printf("88 %d\n", ans.sz);
    for(int z=0; z<ans.sz; z++){trip xyz=ans.ptr[z];
        ll x = xyz.first;
        ll y = xyz.second;
        ll z = xyz.third;
        if     (x == 88) x =  2;
        else if(x ==  2) x = 88;
        if     (y == 88) y =  2;
        else if(y ==  2) y = 88;
        printf("%lld %lld %lld\n", x, y, z);
    }
}
int main(){
    ll n;
    while(1){
        scanf("%lld", &n);
        if(n == -1)
            return 0;
        solve1(n);
        solve2(n);
    }
    return 0;
}

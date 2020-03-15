#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned short uss;
typedef unsigned int ui;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

char buff[2000001];
char*getstr(){
  scanf("%s", buff);
  return strdup(buff);
}
#define x first
#define y second
typedef struct{
  ull first, second;
}pair;
pair newpair(ull a, ull b){
  return(pair){a,b};
}
////////////////////

enum{ M =(int)1e9+7  };
enum{ N =(int)2e6+228};
enum{ P = 29         };
pair ps[N];
pair hs[N], hs_back[N];
ll n;

bool check(ll pos, ll len){
    pair h1 = {hs[pos+len].x-hs[pos].x, (M+hs[pos+len].y-hs[pos].y)%M};
    pair h2 = {hs_back[pos-len+1].x-hs_back[pos+1].x, (M+hs_back[pos-len+1].y-hs_back[pos+1].y)%M};
    h1.x *= ps[n-pos-1].x;
    h1.y = (h1.y*ps[n-pos-1].y)%M;
    h2.x *= ps[pos+1].x;
    h2.y = (h2.y*ps[pos+1].y)%M;
    return h1.x == h2.x&&
           h1.y == h2.y;
}
ui dp[N];
ll fwt[N];
void fwinc(ll p, ll d){
    ++p;
    for(;p<N;p+=p&-p) fwt[p]+=d;
}
ll fwget(ll r, ll s){
    ++r;
    for(;r>0;r-=r&-r) 
        s+=fwt[r];
    return s;
}
vecl lastblock[N];

int main(){
    char*s=getstr();
    n = strlen(s);
    ps[0] = (pair){1, 1};
    for(ui i = 1;i<=n+2;i++){
        ps[i].x = ps[i-1].x*P;
        ps[i].y =(ps[i-1].y*P)%M;
    }
    hs[0] =(pair) {s[0]-'a'+1, s[0]-'a'+1};
    for(ui i =1;i<n;i++){
        hs[i].x = hs[i-1].x + ps[i].x*(s[i]-'a'+1);
        hs[i].y =(hs[i-1].y +(ps[i].y*(s[i]-'a'+1))%M)%M;
    }
    hs_back[n-1] =(pair) {s[n-1]-'a'+1, s[n-1]-'a'+1};
    for(ll i =n-2;i>=0;i--){
        hs_back[i].x = hs_back[i+1].x + ps[n-i-1].x*(s[i]-'a'+1);
        hs_back[i].y =(hs_back[i+1].y +(ps[n-i-1].y*(s[i]-'a'+1))%M)%M;
    }
    for(ui i = 0;i<n;i++){
        ui k = fmin(i+1, n-i-1);
        ui l = 0, r = k;
        while(r-l>1){
            ui m = (l+r)>>1;
            if(check(i, m)) l = m;
            else r = m;
        }
        ui ans = 0;
        for(ui m = l;m<=r;m++) if(check(i, m)) ans = m;
        dp[i+1] = ans;
    }
    ll res = 0;
    for(ll i = n;i>0;i--){
        res += fwget(dp[i]+i,0);
        if(dp[i]){
            fwinc(i, 1);
            pbl(lastblock[i-dp[i]], i);
        }
        for(int z=0;z<lastblock[i].sz;z++){ll j = lastblock[i].ptr[z];
            fwinc(j, -1);
        }
    }
    printf("%lld\n", res);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<assert.h>
#include<limits.h>

typedef long long ll;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ mxfc = 20010};
const ll mdl=1000000007LL;
ll fc   [mxfc];
ll invfc[mxfc];
int*pp=NULL;  int ppSz   =0;

ll ncr(ll a, ll b){
  ll rv;
  if(b==0 || b==a){rv=1;goto end;}
  if(b< 0 || b >a){rv=0;goto end;}
  rv = fc[a]*invfc[b]%mdl*invfc[a-b]%mdl;
end:
  return rv;
}
void inifc(){
  fc[0] = fc[1] = invfc[0] = invfc[1] = 1;
  for(ll i=2; i<mxfc; ++i){
    fc   [i] = fc[i-1]*i%mdl;
    invfc[i] = invfc[mdl%i]*(mdl-mdl/i)%mdl;
  }
  for(ll i=2; i<mxfc; ++i){
    invfc[i] *= invfc[i-1];
    invfc[i] %= mdl;
  }
}
int main(){
  inifc();
  ll n,k;
  scanf("%lld %lld",&n,&k);
  pp=pushback(pp, &ppSz, 1);
  for(ll i=1; i<=n*n/2+9; ++i){
    pp=pushback(pp, &ppSz, pp[ppSz-1] * 2 % mdl);
  }
  ll wfc[k+1]; memset(wfc, 0, sizeof(wfc));
  wfc[1]=1;
  for(ll i=2;i<k;++i){
    wfc[i] = pp[i*(i-1)/2];
    for(ll j=1; j<=i-1; ++j){
      wfc[i] -= wfc[j]*pp[(i-j)*(i-j-1)/2]%mdl*ncr(i,j)%mdl;
    }
    wfc[i] %= mdl;
    wfc[i] += mdl;
    wfc[i] %= mdl;
  }
  ll ccomp[n+1];memset(ccomp, 0, sizeof(ccomp));
  ccomp[0]=1;
  for(ll i=0;i<(n+1);++i){
    ccomp[i] %= mdl;
    ccomp[i] += mdl;
    ccomp[i] %= mdl;
    for(ll nua=1; nua<k && nua+i<=n; ++nua){
      ll var = ccomp[i] * wfc[nua] % mdl * ncr(n-i,nua) % mdl;
      ccomp[nua+i] += var;
    }
  }
  ll ans=pp[n*(n-1)/2]-ccomp[n];
  ans%=mdl;
  ans+=mdl;
  ans%=mdl;
  printf("%lld\n", ans);
  return 0;
}






























































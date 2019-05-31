#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
void swap(ll*nums, int i, int j) {
   ll t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


enum{ mod      = 5 * (1 << 25) + 1};
enum{ root     = 243              };
enum{ root_1   = 114609789        };
enum{ root_pw  = 1<<25            };
enum{ MAX_LEN  = 1000000          };
int asz;

ll gcd(ll a, ll b, ll*s, ll*t){
  if(b==0){
    t = 0;
   *s = (a < 0) ? -1 : 1;
    return(a < 0) ? -a : a;
  }
  else{
    ll g = gcd(b, a%b, t, s);
    (*t) -= a/b * (*s);
    return g;
  }
}
ll inverse(ll n, ll mod){
  ll s, t;
  gcd(n, mod, &s, &t);
  return (s > 0) ? s : s + mod;
}
void fft(ll*a, bool invert){
  int n = asz;
  for (int i=1, j=0; i<n; ++i){
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      swap(a, i, j);
  }
  for (int len=2; len<=n; len<<=1){
    ll wlen = invert ? root_1 : root;
    for (ll i=len; i<root_pw; i<<=1)
      wlen = (ll)(wlen * 1ll * wlen % mod);
    for (int i=0; i<n; i+=len){
      ll w = 1;
      for (int j=0; j<len/2; ++j){
        ll u = a[i+j],  
           v = (ll)(a[i+j+len/2] * 1ll * w % mod);
        a[i+j] = u+v < mod ? u+v : u+v-mod;
        a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
        w = (ll)(w * 1ll * wlen % mod);
      }
    }
  }
  if (invert) {
    ll nrev = inverse(n, mod);
    for (int i=0; i<n; ++i)
      a[i] = (ll)(a[i] * 1ll * nrev % mod);
  }
}
int main(){
  char*s;
  s = getstr();
  int n = strlen(s);
  int fft_len = 1;
  while (fft_len < 2*MAX_LEN)
    fft_len *= 2;
  ll A[fft_len]; memset(A, 0, sizeof(A));
  ll B[fft_len]; memset(B, 0, sizeof(B));
  ll C[fft_len]; memset(C, 0, sizeof(C));
  asz=fft_len;
  for (int i = 0; i < n; i++){
    if (s[i] == 'A')
      A[i] = 1;
    else
      B[n-i] = 1;
  }
  fft(A, false);
  fft(B, false);
  for (int i = 0; i < fft_len; i++)
    C[i] = A[i] * B[i] % mod;
  fft(C, true);
  for (int i = n+1; i < 2*n; i++)
    printf("%lld\n", C[i]);
  puts("");
  return 0;
}

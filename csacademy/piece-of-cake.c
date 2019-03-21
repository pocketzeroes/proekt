#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll gcd(ll u, ll v){
  return v != 0?gcd(v, u%v):u;
}

int cmpL(const void*pb, const void*pa){//rev
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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

int main(){
  int n;
  scanf("%d", &n);
  ll dw = (1 << 24)*3;
  vecl nums[21]; memset(nums,0,sizeof(nums));
  for(int i = 0; i < n; ++i){
    int x;
    scanf("%d", &x);
    int msb = 0;
    while((1 << msb) <= x)
      ++msb;
    nums[msb].ptr = pushbackL(nums[msb].ptr, &nums[msb].sz, x*dw);
  }
  int at = 0;
  ll ans[2]={0};
  for(int i = 20; i > 0; --i){
    qsort(nums[i].ptr, nums[i].sz, sizeof(ll), cmpL);//rev
    for(int q=0;q<nums[i].sz;q++){ll x = nums[i].ptr[q];
      ans[at] += x / 2;
      nums[i-1].ptr = pushbackL(nums[i-1].ptr, &nums[i-1].sz, x/2);
      at = !at;
    }
  }
  if(n%2==0){
    for(int q=0;q<nums[0].sz;q++){ll x = nums[0].ptr[q];
      ans[at] += x;
      at = !at;
    }
  }
  else{
    for(int q=0;q<nums[0].sz;q++){ll x = nums[0].ptr[q];
      ans[at] += 2 * x / 3;
      ans[!at] += x / 3;
      at = !at;
    }
  }
  void output(ll up, ll dw){
    ll g_cd = gcd(up, dw);
    up /= g_cd;
    dw /= g_cd;
    printf("%lld/%lld\n", up, dw);
  }
  output(ans[0], dw);
  output(ans[1], dw);
  return 0;
}


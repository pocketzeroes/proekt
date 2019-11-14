#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void reverse(char * str){
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pair;
pair newpair(ll a, ll b){
  return(pair){a,b};
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int upper_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])>=0)
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}
int lower_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

const ll INF = 1e15;
vecp tmp, nums;// of pll
ll  P[15];
int comb1[2][20];
int comb2[2][20];


ll f(ll x){
  static char tmp[20];
  sprintf(tmp, "%lld", x);
  reverse(tmp);
  ll y;
  sscanf(tmp, "%lld", &y);
  return x+y;
}
void init(){
  P[0] = 1;
  for(int i=1; i<15; ++i)
    P[i] = P[i-1] * 10;
  for(int a=0; a<=9; ++a){
    ++comb1[0][a+a];
    if(a)
      ++comb1[1][a+a];
    for(int b = 0; b <= 9; ++b){
      ++comb2[0][a+b];
      if(a)
        ++comb2[1][a+b];
    }
  }
}
void gen(int len, int pos, int c1, int c2, ll num, int w){
  if(pos == len/2){
    if(len % 2 == 0){
      if(c1 == c2)
        pb(tmp, newpair(num, w));
      return;
    }
    for(int d = 0; d <= 18; d += 2){
      int nw = w * comb1[!pos][d];
      if (nw == 0)
        continue;
      ll nnum = num + P[pos] * ((d+c2) % 10);
      if (c1){
        if (d+c2 <= 9)
          continue;
        pb(tmp, newpair(nnum, nw));
      }
      else{
        if(d+c2 >= 10)
          continue;
        pb(tmp, newpair(nnum, nw));
      }
    }
    return;
  }
  for(int d = 0; d <= 18; ++d){
    int nw = w * comb2[!pos][d];
    if(nw == 0)
      continue;
    int nc2 = d+c2 >= 10;
    ll nnum = num + P[pos] * ((d+c2)%10) + P[len-pos-1] * (d%10), nnum_c = num + P[pos] * ((d+c2)%10) + P[len-pos-1] * ((d+1)%10);
    if(c1){
      if(d < 9)
        continue;
      gen(len, pos+1, 1, nc2, nnum_c, nw);
      if(d >= 10)
        gen(len, pos+1, 0, nc2, nnum, nw);
    }
    else{
      if(d >= 10)
        continue;
      gen(len, pos+1, 0, nc2, nnum, nw);
      if(d < 9)
        gen(len, pos+1, 1, nc2, nnum_c, nw);
    }
  }
}
int main(){
  init();
//  tmp .reserve(4e6);
//  nums.reserve(4e6);
  for(int len = 1; len <= 10; ++len){
    gen(len, 0, 0, 0, 0, 1);
    gen(len, 0, 1, 0, P[len], 1);
  }
  qsort(tmp.ptr, tmp.sz, sizeof(pair), cmpP);
  for(int z=0;z<tmp.sz;z++){pair p = tmp.ptr[z];
    if(nums.sz==0 || p.first != nums.ptr[nums.sz-1].first)
      pb(nums, p);
    else
      nums.ptr[nums.sz-1].second += p.second;
  }
  for(int i=0; i<nums.sz; ++i){
    pair p = nums.ptr[i];
    ll t = f(p.first);
    int it = lower_bound(nums.ptr, nums.sz, newpair(t, -1ll));
    nums.ptr[it].second += p.second;
    if(i > 0)
      nums.ptr[i].second += nums.ptr[i-1].second;
  }
  int q;
  scanf("%d", &q);
  for (int i = (0); i < ((q)); ++i){
    ll l, r;
    scanf("%lld%lld", &l, &r);
    int lo = lower_bound(nums.ptr, nums.sz, newpair(l, -1ll));
    int hi = upper_bound(nums.ptr, nums.sz, newpair(r, INF));
    ll ans = 0;
    if(hi != 0)
      ans += nums.ptr[hi-1].second;
    if(lo != 0)
      ans -= nums.ptr[lo-1].second;
    printf("%lld\n", ans + (r-l+1));
  }
  return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN = 1010};
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

ll seed = 31;
ll Pow[MAXN];
ll lis[MAXN], hash[MAXN];
char line[12345];
int n, l;

int moo(int l){
  ll h = 0;
  int t = 0;
  for(int i = 0; i < l; ++i)
    h = h * seed + lis[i];
  for(int i = l; i < n; ++i) {
    h = h * seed + lis[i];
    hash[t++] = h;
    h = h - lis[i - l] * Pow[l];
  }
  qsort(hash, t, sizeof(ll), cmpLL);
  int ma = 0;
  for(int i = 0; i < t;){
    int i1;
    for(i1 = i + 1; i1 < t && hash[i1] == hash[i]; ++i1);
    ma = fmax(ma, i1 - i);
    i = i1;
  }
  if(ma == 1)
    return 0;
  printf("%d\n", ma);
  return 1;
}
int main(){
  Pow[0] = 1;
  for(int i = 1; i < MAXN; ++i)
    Pow[i] = Pow[i - 1] * seed;
  gets(line);
  while((l = strlen(line)) > 0){
    n = 0;
    for(int i = 0; i < l; ++i)
      if(line[i] >= 'A' && line[i] <= 'Z')
        lis[n++] = line[i] - 'A';
      else
        ;
    for(int i = 0; i < n; ++i)
      if(!moo(i))
        break;
    puts("");
    gets(line);
  }
  return 0;
}

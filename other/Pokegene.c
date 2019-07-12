#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
typedef struct{
  char*s;
  int  i;
}State;
State newState(char*s, int i){
  State rez;
  rez.s = s;
  rez.i = i;
  return rez;
}
int cmpSt(const void*pa, const void*pb){
  State*a=(State*)pa;
  State*b=(State*)pb;
  return strcmp(a->s, b->s);
}

int*mapping;
State*l;
ll**hash;
enum{ HASH = 3137     };
enum{ MOD = 1000000007};

int match(int lhs, int rhs){
  int lowLen = 0;
  int highLen = min(strlen(l[lhs].s), strlen(l[rhs].s));
  while(lowLen != highLen){
    int mid = (lowLen+highLen+1)/2;
    if(hash[lhs][mid] == hash[rhs][mid])
      lowLen = mid;
    else
      highLen = mid-1;
  }
  return lowLen;
}
ll solve(){
  int n = in_nextInt();
  int k = in_nextInt();
  int have[n];
  for(int i = 0; i < n; i++)
    have[i] = mapping[in_nextInt()-1];
  qsort(have, n, sizeof(int), cmp);
  ll ret = 0;
  for(int i = 0; i + k <= n; i++) {
    int lhs = have[i];
    int rhs = have[i+k-1];
    int matchLen = match(lhs, rhs);
    int border = 0;
    if(i > 0)
      border = max(border, match(have[i-1], have[i]));
    if(i + k < n)
      border = max(border, match(have[i+k-1], have[i+k]));
    ret += max(0, matchLen - border);
  }
  return ret;
}
int main(){
  int n   = in_nextInt();
  int qq  = in_nextInt();
  mapping = calloc(n, sizeof(int));
  l       = calloc(n, sizeof(State));
  for(int i=0; i<n; i++)
    l[i] = newState(getstr(), i);
  qsort(l, n, sizeof(State), cmpSt);
  hash = calloc(n, sizeof(ll*));
  for(int i=0; i<n; i++){
    hash[i] = calloc(strlen(l[i].s)+1, sizeof(ll));
    for(int a=0; a < strlen(l[i].s); a++){
      hash[i][a+1] = hash[i][a] * HASH + l[i].s[a];
      hash[i][a+1] %= MOD;
    }
  }
  for(int i=0; i<n; i++)
    mapping[l[i].i] = i;
  while(qq-- > 0)
    printf("%lld\n", solve());
  return 0;
}

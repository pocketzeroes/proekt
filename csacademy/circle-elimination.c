#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
typedef struct pair{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  if(a->first != b->first)return (a->first < b->first)?-1:1;
  return (a->second < b->second)?-1:1;
}

enum{ N =(int) 1e5+7};
pair a[N];


int main(void) {
  int n,in;
  scanf("%d", &n);
  for(int i = (0); i < (n); ++i){
    scanf("%d", &in);
    a[i] = newPair(in, i);
  }
  qsort(a, n,sizeof(pair),cmpP);
  ll cnt = 0, last = a[0].second;
  for(int k = (1); k < (n); ++k) {
    pair myp = a[k];
    cnt += min(abs(myp.second-last),n-abs(last-myp.second));
    last = myp.second;
  }
  printf("%lld\n", cnt);
  return 0;
}


































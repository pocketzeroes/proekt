#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
enum{ MAX = 100001};
int n;
pair a[MAX];

int main() {
  scanf("%d%*d", &n);
  for( int i = 0; i < n; ++i ) 
    scanf("%d%d", &a[i].first, &a[i].second);
  qsort(a, n, sizeof(pair), cmpP);
  a[n] = newPair(0, 0);
  long long ret = 0;
  for( int i = 1; i <= n; ++i ) 
    if( a[i-1].second > a[i].second ) 
      ret += a[i-1].second - a[i].second;
  printf("%lld\n", ret);
  return 0;
}

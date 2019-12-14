#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
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

enum{MAX  = 300000};
enum{ITER = 100   };

int myrand(){
  int a = rand()%5000;
  int b = rand()%5000;
  return a*5000+b;
}

int n, Q, C;
int  a[MAX];
pair b[MAX];

int main(){
  scanf("%d %d", &n, &C);
  for(int i=0; i<n; ++i)
    scanf("%d", &a[i]);
  for(int i=0; i<n; ++i)
    b[i] = newpair(a[i], i);
  qsort(b, n, sizeof(pair), cmpP);
  scanf("%d", &Q);
  for(int qq=0; qq<Q; ++qq){
    int lo, hi;
    scanf("%d %d", &lo, &hi);
    --lo, --hi;
    int m = hi-lo+1;
    int iter, x, cnt;
    for(iter=0; iter<ITER; ++iter){
      x = a[lo+myrand()%m];
      cnt = upper_bound(b, n, newpair(x, hi))-
            lower_bound(b, n, newpair(x, lo));
      if(cnt*2 > m)
        break;
    }
    if(iter == ITER)
      puts("no");
    else
      printf("yes %d\n", x);
  }
  return 0;
}

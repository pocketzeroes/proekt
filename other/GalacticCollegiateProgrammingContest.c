#pragma GCC optimize "-O3"
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

/////////////////////////////
enum{ maxn =(int)1e5+100};
int n, m, a[maxn], b[maxn], x[maxn], y[maxn], cnt;
pair p [maxn*3];
int bit[maxn*3];

inline int lowbit(int x){
    return x&(-x);
}
int sum(int k){
    return k<=0 ? 0 : bit[k] + sum(k-lowbit(k));
}
void add(int i, int x){
    for( ; i<=cnt; i+=lowbit(i))
        bit[i] += x;
}
int main(){
    scanf("%d%d", &n, &m);
    p[cnt++] = newpair(0, 0);
    for(int i=0; i<m; ++i){
        scanf("%d%d", a+i, b+i);
        x[a[i]]--;
        y[a[i]]+=b[i];
        p[cnt++] = newpair(x[a[i]], y[a[i]]);
    }
    qsort(p, cnt, sizeof(pair), cmpP);
    int v = lower_bound(p, cnt, newpair(0, 0)) + 1;
    add(v, n);
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    for(int i=0; i<m; ++i){
        v = lower_bound(p, cnt, newpair(x[a[i]], y[a[i]])) + 1;
        add(v, -1);
        x[a[i]]--;
        y[a[i]]+=b[i];
        v = lower_bound(p, cnt, newpair(x[a[i]], y[a[i]])) + 1;
        add(v, 1);
        v = lower_bound(p, cnt, newpair(x[1], y[1])) + 1;
        printf("%d\n", sum(v-1)+1);
    }
    return 0;
}

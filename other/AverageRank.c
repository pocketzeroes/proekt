#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long   ll;
typedef long double ld;

typedef struct{
  ll c, m;
}lin;
ll eval(lin l, ll t){
  return l.c+t*l.m;
}
lin*fun;

int main(){
  int n, d;
  scanf("%d %d", &n, &d);
  int pts  [n]; clr(pts);
  ll  total[n]; clr(total);
  fun = calloc(d+1, sizeof(lin));
  for(int t=0; t<d; t++){
    int k;
    scanf("%d", &k);
    int q[k]; clr(q);
    for(int i=0;i<k;i++){
      scanf("%d", &q[i]); --q[i];
    }
    for(int i=0;i<k;i++){int x = q[i];
      total[x] += eval(fun[pts[x]], t);
    }
    for(int i=0;i<k;i++){int x = q[i];
      fun[pts[x]  ].c-=t;
      fun[pts[x]++].m++;
    }
    for(int i=0;i<k;i++){int x = q[i];
      total[x] -= eval(fun[pts[x]], t);
    }
  }
  for(int x=0; x<n; x++){
    total[x] += eval(fun[pts[x]], d);
  }
  for(int i=0; i<n; i++){
    ld avg = 1+total[i]/(ld)d;
    printf("%.9Lf\n", avg);
  }
  return 0;
}

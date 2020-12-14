#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
typedef struct{
    int first, second, third, fourth;
}quad;
int cmpQr(const void*pb, const void*pa){//rev
  quad*a = (quad*)pa;
  quad*b = (quad*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third )return(a->third  < b->third )?-1:1;
  if(a->fourth != b->fourth)return(a->fourth < b->fourth)?-1:1;
  return 0;
}

int maxHeight(int**cuboids, int cSz, int*cuboids0sz){
    quad v[6*cSz];
    int vsz=0;
    for(int i=0; i<cSz; i++){
        int*x = cuboids[i];
        v[vsz++] = (quad){x[0], x[1], x[2], i};
        v[vsz++] = (quad){x[0], x[2], x[1], i};
        v[vsz++] = (quad){x[1], x[0], x[2], i};
        v[vsz++] = (quad){x[1], x[2], x[0], i};
        v[vsz++] = (quad){x[2], x[0], x[1], i};
        v[vsz++] = (quad){x[2], x[1], x[0], i};
    }
    int n = vsz;
    int dp[n]; clr(dp);
    qsort(v, vsz, sizeof(quad), cmpQr);//rev
    for(int i=0; i<n; i++){
        dp[i] = v[i].third;
        for(int j=0; j<i; j++)
            if(v[j].first >= v[i].first && v[j].second >= v[i].second && v[j].third >= v[i].third && v[j].fourth != v[i].fourth)
                dp[i] = fmax(dp[i], dp[j] + v[i].third);
    }
    return max_element(dp, n);
}

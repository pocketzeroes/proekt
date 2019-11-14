#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX  = 1000000};
enum{ MAXN =  100000};
typedef struct{
   int lo, hi;
}interval;
int n;
interval*intervals;
int how[MAXN];
int dp [MAXN];

int cmpI(const void*pa, const void*pb){
   interval*A=(interval*)pa;
   interval*B=(interval*)pb;
   if(A->lo != B->lo)
      return(A->lo > B->lo)?-1:1;
   if(A->hi != B->hi)
      return(A->hi < B->hi)?-1:1;
   return 0;
}

int a[MAX+1];

void fenwick(){
   memset(a, -1, sizeof a);
}
int query(int X){
   int ret=-1;
   for(int x=X; x>0; x-=x&-x)
      if(a[x]!=-1 && (ret==-1 || dp[a[x]]>dp[ret]))
         ret = a[x];
   return ret;
}
void update(int X, int i){
   for(int x=X; x<=MAX; x+=x&-x)
      if(a[x] == -1 || dp[i] > dp[a[x]])
         a[x] = i;
}

int main(){
   fenwick();
   scanf("%d", &n);
   intervals = calloc(n, sizeof(interval));
   for(int i=0; i<n; ++i){
      interval I;
      scanf("%d %d", &I.lo, &I.hi);
      intervals[i] = I;
   }
   qsort(intervals, n, sizeof(interval), cmpI);
   int ret=0;
   for(int i=0; i<n; ++i){
      dp [i] = 1;
      how[i] =-1;
      int x = query(intervals[i].hi);
      if(x != -1){
         dp [i] = dp[x] + 1;
         how[i] = x;
      }
      update(intervals[i].hi, i);
      if(dp[i] > dp[ret])
         ret = i;
   }
   printf("%d\n", dp[ret]);
   while(ret != -1){
      printf("%d %d\n", intervals[ret].lo, intervals[ret].hi);
      ret = how[ret];
   }
   return 0;
}

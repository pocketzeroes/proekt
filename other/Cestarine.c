#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}
enum{ MAX = 100000};

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

const ll inf = 1000000000000000LL;

int n;
int a[MAX], b[MAX];
int perm[3];
ll dp[MAX+1];

ll calc( int a, int b ) {
   if( a > b ) return a - b;
   if( b > a ) return b - a;
   return inf;
}
int main(){
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i )
      scanf( "%d%d", &a[i], &b[i] );
   qsort(a, n, sizeof(int), cmp);
   qsort(b, n, sizeof(int), cmp);
   dp[n] = 0;
   for( int i = n-1; i >= 0; --i ){
      dp[i] = inf;
      for( int k = 1; k <= 3 && i+k <= n; ++k ){
         for( int j = 0; j < k; ++j )
            perm[j] = j;
         do{
            ll cost = 0;
            for( int j = 0; j < k; ++j )
               cost += calc( a[i+j], b[i+perm[j]] );
            dp[i] = min( dp[i], cost + dp[i+k] );
         }
         while( next_permutation( perm, k));
      }
   }
   printf( "%lld\n", dp[0] );
   return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll A, B;
ll pow_10[16];
ll memo[16][136];
ll min_solution = -1;

ll rec( ll prefix, int digits, int sum ){
   if( sum < 0 )
      return 0;
   ll mini = prefix;
   ll maxi = prefix + pow_10[digits]-1;
   if( mini > B || maxi < A )
      return 0;
   if( digits == 0 ){
      if( sum > 0 )
         return 0;      
      if( min_solution == -1 )
         min_solution = prefix;
      return 1;
   }
   bool memoize = (mini >= A && maxi <= B);
   if( memoize && memo[digits][sum] != -1 )
      return memo[digits][sum];
   ll ret = 0;
   for( int dig = 0; dig < 10; ++dig ) 
      ret += rec( prefix + dig*pow_10[digits-1], digits-1, sum-dig );   
   if( memoize )
      memo[digits][sum] = ret;
   return ret;
}
int main(){
   pow_10[0] = 1;
   for( int i = 1; i <= 15; ++i )
      pow_10[i] = pow_10[i-1] * 10;
   int S;
   scanf( "%lld%lld%d", &A, &B, &S );
   memset( memo, -1, sizeof memo );
   printf( "%lld\n", rec( 0, 15, S ) );
   printf( "%lld\n", min_solution );
   return 0;
}

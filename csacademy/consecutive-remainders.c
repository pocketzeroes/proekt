#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
  ll n, x, y, q;
  scanf("%lld %lld %lld", &n, &x, &y);
  q = n-1;
  if( y >= x * ( x - 1 ))
    return printf("%lld\n", x-1)*0;
  if(n != x && ( 2 * y - n * n + n ) % ( 2 * x - 2 * n ) == 0 && ( 2 * y - n * n + n ) / ( 2 * x - 2 * n ) != 0)
    return printf("%lld\n", x-1)*0;
  if(q && ( 2 * y - q * q + q ) % ( 2 * q ) == 0 && ( 2 * y - q * q + q ) / ( 2 * q ) + q - 1 == x - 1)
    return printf("%lld\n", x-1)*0;
  if(( 2 * y - n * n + n ) % ( 2 * n ) == 0)
    return printf("%lld\n", ( 2 * y - n * n + n ) / ( 2 * n ) + n - 1)*0;
  return 0;
}

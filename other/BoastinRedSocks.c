#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int main(){
	unsigned long long i, j, k, x, y, z, n;
	unsigned long long p, q;
	unsigned int pi, qi;
	for(;;) {
		scanf( " %u %u", &pi, &qi );
		p = pi; 
    q = qi;
		if( pi+qi == 0 ) 
      break;
		x = 0;
		for( i = 2; i <= 50000; i++ ){
			n = i*(i-1)*p;
			while( x*(x-1)*q < n ) 
        x++;
			if( x*(x-1)*q == n ) 
        break;
		}
		if( i > 50000 )
			printf( "impossible\n" );
		else
			printf( "%d %d\n", (int)x, (int)(i-x) );
	}
  return 0;
}

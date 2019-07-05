#include<stdio.h>
#include<string.h>

char a[2000], b[2000];
int al, bl;

int Works( char *s, int sl, int n ) {
	int i;
	for( i = n; i < sl; i++ )
		if( s[i] != s[sl+n-i-1])
      return 0;
	return 1;
}
int main(){
	int i, j, k, x, y, z, n;
	char *s;
	int sl;
	for(;;){
		if( !gets(a) || !gets(b) ) 
      break;
		if( !strcmp( a, b ) ) {
			printf( "No Solution.\n" );
			continue;
		}
		al = strlen( a ); 
    bl = strlen( b );
		for( x = 0; a[x] == b[x]; x++ );
      for( i = 0; i <= al && i <= bl; i++ ) {
        z = Works( a, al, i ) + 2*Works( b, bl, i );
        if( z == 1 || z == 2 || (z == 3 && i > x) ) {
          switch(z) {
            case 1: s = a; break;
            case 2: s = b; break;
            case 3:
              for( j = i-1; j >= 0; j-- ) 
                if( a[j] != b[j] ) 
                  break;
              s = (a[j]<b[j])?a:b;
              break;
          }
          for( j = i-1; j >= 0; j-- ) 
            putchar( s[j] );
          putchar( '\n' );
          break;
        }
      }
		if( i > al || i > bl ){
			s = (i > al) ? b : a; sl = (i > al) ? bl : al;
			if( s[i-1] == 'a' && Works( s, sl, i ) )
				putchar( 'b' );
			else
				putchar( 'a' );
			s = (i > al) ? a : b; sl = (i > al) ? al : bl;
			for( j = sl-1; j >= 0; j-- ) 
        putchar( s[j] );
			putchar( '\n' );
		}
	}
  return 0;
}

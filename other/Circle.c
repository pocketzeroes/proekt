#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n, k;
int m;
int  sorted   [100];
char kandidati[1024][200];
char razina   [11][200];
char*ga;


int cmpa(const void*pa, const void*pb){
   int*a=(int*)pa;
   int*b=(int*)pb;
   int x=*a;
   int y=*b;
   return(strncmp(ga+x, ga+y, n)<0)?-1:1;
}
void kanoniziraj(char*a){
   for( int i = 0; i < n; ++i )
      a[n+i] = a[i];
   ga = a;
   qsort(sorted, n, sizeof(int), cmpa);
   for( int i = 0; i < n; ++i )
      a[i] = a[sorted[0]+i];
   a[n] = 0;
}
char stavi( char x, char y){
   return x == y ? 'B' : 'W';
}
void transformacija(char*a, char*b){
   a[n] = a[0];
   for( int i = 0; i < n; ++i )
      b[i] = stavi( a[i], a[i+1] );
}
int inverzna(char*a, char*b, char prvi){
   b[0] = prvi;
   for( int i = 1; i <= n; ++i )
      b[i] = stavi( a[i-1], b[i-1] );
   return b[0] == b[n];
}
void rec(int d){
   if( d == 0){
      kanoniziraj( razina[0] );
      strncpy( kandidati[m++], razina[0], n );
      return;
   }
   if( inverzna( razina[d], razina[d-1], 'B' ) )
      rec( d-1 );
   if( inverzna( razina[d], razina[d-1], 'W' ) )
      rec( d-1 );
}
int main(){
   scanf( "%d%d", &n, &k );
   scanf( "%s", razina );
   for( int i = 0; i < n; ++i )
      sorted[i] = i;
   for( int i = 0; i < k; ++i )
      transformacija( razina[i], razina[i+1] );
   rec( k );
   qsort( kandidati, m, sizeof kandidati[0], (int (*)(const void *, const void *))strcmp );
   int ret = 0;
   for( int i = 0; i < m; ++i )
      if( i == 0 || strcmp( kandidati[i], kandidati[i-1] ) )
         ++ret;
   printf( "%d\n", ret );
   return 0;
}

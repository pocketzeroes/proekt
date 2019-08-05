#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


enum{ MAXLOPOC = 100000};
enum{ MAXSKOK  = 100000};
int n, k;

typedef struct{
   int x,  y;
   int d1, d2;
   int skok[4];
}pt;
pt lopoci[MAXLOPOC];
char niz[MAXSKOK+1];
int sorted[MAXLOPOC];

int cmp_d1(const void*pa, const void*pb){
   int*ii=(int*)pa;
   int*jj=(int*)pb;
   int i = *ii;
   int j = *jj;
   return((lopoci[i].d1 != lopoci[j].d1)?lopoci[i].d1 < lopoci[j].d1:lopoci[i].d2 < lopoci[j].d2)?-1:1;
}
int cmp_d2(const void*pa, const void*pb){
   int*ii=(int*)pa;
   int*jj=(int*)pb;
   int i = *ii;
   int j = *jj;
   return((lopoci[i].d2 != lopoci[j].d2) ? lopoci[i].d2 < lopoci[j].d2 : lopoci[i].d1 < lopoci[j].d1)?-1:1;
}
int main(){
   scanf( "%d%d ", &n, &k );
   gets( niz );
   for( int i = 0; i < n; ++i ) {
      scanf( "%d%d", &lopoci[i].x, &lopoci[i].y );
      lopoci[i].d1 = lopoci[i].x + lopoci[i].y;
      lopoci[i].d2 = lopoci[i].x - lopoci[i].y;
      for( int j = 0; j < 4; ++j )
         lopoci[i].skok[j] = -1;
      sorted[i] = i;
   }
   qsort( sorted, n, sizeof(int), cmp_d1 );
   for(int i = 1; i < n; ++i){
      if(lopoci[sorted[i-1]].d1 == lopoci[sorted[i]].d1){
         lopoci[sorted[i-1]].skok[1] = sorted[i];
         lopoci[sorted[i]].skok[2] = sorted[i-1];
      }
   }
   qsort(sorted, n, sizeof(int), cmp_d2);
   for(int i = 1; i < n; ++i){
      if( lopoci[sorted[i-1]].d2 == lopoci[sorted[i]].d2 ) {
         lopoci[sorted[i-1]].skok[0] = sorted[i  ];
         lopoci[sorted[i  ]].skok[3] = sorted[i-1];
      }
   }
   int barica = 0;
   for( char *c = niz; *c; ++c ) {
      int next = lopoci[barica].skok[*c-'A'];
      if( next == -1 ) 
         continue;
      for( int j = 0; j < 4; ++j )
         if( lopoci[barica].skok[j] != -1 )
            lopoci[lopoci[barica].skok[j]].skok[3-j] = lopoci[barica].skok[3-j];
      barica = next;
   }
   printf( "%d %d\n", lopoci[barica].x, lopoci[barica].y );
   return 0;
}

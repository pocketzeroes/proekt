#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ inf = 1000000000};
enum{NIZSZ = 1500};

typedef struct{
   short r, c;
   int val;
   int dp;
}skakavac;
skakavac niz[NIZSZ*NIZSZ+1];
int cmpS(const void*pa, const void*pb){
   skakavac*A=(skakavac*)pa;
   skakavac*B=(skakavac*)pb;
   return(A->val > B->val)?-1:1;
}

typedef struct{
   skakavac*best[4];
}best4;
void update(best4*b, skakavac *S){
   for( int i = 3; i >= 0; --i ){
      if( S->dp <= b->best[i]->dp)
         break;
      if( i+1 < 4 )
         b->best[i+1] = b->best[i];
      b->best[i] = S;
   }
}
int query(best4*b, int r, int c ){
   for( int i = 0; i < 4; ++i ){
      if( abs(r-b->best[i]->r)<=1 && abs(c-b->best[i]->c)<=1)
         continue;
      return b->best[i]->dp;
   }
   return -inf;
}
best4 R[NIZSZ];
best4 C[NIZSZ];

int n, r0, c0;

int main(){
   scanf( "%d%d%d", &n, &r0, &c0 );
   --r0, --c0;
   skakavac *next = niz;
   for( int i = 0; i < n; ++i ){
      for( int j = 0; j < n; ++j ){
         next->r = i;
         next->c = j;
         next->dp = 1;
         scanf( "%d", &next->val );
         ++next;
      }
   }
   next->r = -5;
   next->c = -5;
   next->dp = -inf;
   for( int i = 0; i < n; ++i )
      for( int j = 0; j < 4; ++j )
         R[i].best[j] = C[i].best[j] = next;
   qsort(niz, n*n, sizeof(skakavac), cmpS);
   for( int i = 0, j; i < n*n; i = j ) {
      for( j = i; j < n*n && niz[j].val == niz[i].val; ++j ) {
         skakavac *S = &niz[j];
         if( S->r-1 >= 0 )niz[j].dp = max( niz[j].dp, 1+query(&R[S->r-1], S->r, S->c));
         if( S->c-1 >= 0 )niz[j].dp = max( niz[j].dp, 1+query(&C[S->c-1], S->r, S->c));
         if( S->r+1 <  n )niz[j].dp = max( niz[j].dp, 1+query(&R[S->r+1], S->r, S->c));
         if( S->c+1 <  n )niz[j].dp = max( niz[j].dp, 1+query(&C[S->c+1], S->r, S->c));
      }
      for( j = i; j < n*n && niz[j].val == niz[i].val; ++j ) {
         skakavac *S = &niz[j];
         update(&R[S->r], S);
         update(&C[S->c], S);
         if( S->r == r0 && S->c == c0)
            printf( "%d\n", S->dp);
      }
   }
   return 0;
}

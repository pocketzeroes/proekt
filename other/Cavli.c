#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef enum{
   LEFT,
   RIGHT,
   DOWN,
   UP
}direction;

typedef struct pt{
   ll x, y;
   bool flag;
   struct pt*next[4];
   struct pt*CCW;
   struct pt*CW;
}pt;
pt newpt(){
   pt rez;
   rez.flag = false;
   for(int i=0; i<4; ++i)
      rez.next[i] = NULL;
   rez.CCW = rez.CW = NULL;
   return rez;
}
int ccw( pt *A, pt *B, pt *C ) {
   ll t = (B->x-A->x)*(C->y-A->y) - (C->x-A->x)*(B->y-A->y);
   if( t < 0 )
      return -1;
   if( t > 0 )
      return 1;
   return 0;
}

void connect( int n, pt**order, pt**extreme, direction A, direction B){
   extreme[A] = order[0  ];
   extreme[B] = order[n-1];
   for( int i = 1; i < n; ++i ) {
      order[i  ]->next[A] = order[i-1];
      order[i-1]->next[B] = order[i  ];
   }
}
void go_inwards( char *chosen, pt **order, int steps, pt **extreme ){
   for( int i = 0; i < steps; ++i ) {
      if( chosen[i] == 'L' ) order[i] = extreme[LEFT ];
      if( chosen[i] == 'R' ) order[i] = extreme[RIGHT];
      if( chosen[i] == 'D' ) order[i] = extreme[DOWN ];
      if( chosen[i] == 'U' ) order[i] = extreme[UP   ];
      order[i]->flag = 1;
      for( int d = 0; d < 4; ++d )
         while( extreme[d]->flag )
            extreme[d] = extreme[d]->next[d^1];
   }
}
void add(ll*area, pt*P){
   P->CCW->CW = P;
   P->CW->CCW = P;
  (*area) += P->x     * P->CCW->y  - P->y     * P->CCW->x;
  (*area) += P->CW->x * P->y       - P->CW->y * P->x;
  (*area) -= P->CW->x * P->CCW->y  - P->CW->y * P->CCW->x;
}
void sub(ll*area, pt*P){
   P->CCW->CW = P->CW;
   P->CW->CCW = P->CCW;
   (*area) -= P->x     * P->CCW->y  - P->y     * P->CCW->x;
   (*area) -= P->CW->x * P->y       - P->CW->y * P->x;
   (*area) += P->CW->x * P->CCW->y  - P->CW->y * P->CCW->x;
}
ll*go_outwards( char *chosen, pt**order, int steps, pt**extreme){
   ll*result = calloc(steps, sizeof(ll));
   ll area = 0;
   for( int i = steps-1; i >= 0; --i ){
      direction d;
      if( chosen[i] == 'L' ) d = LEFT ;
      if( chosen[i] == 'R' ) d = RIGHT;
      if( chosen[i] == 'D' ) d = DOWN ;
      if( chosen[i] == 'U' ) d = UP   ;
      pt *A = order[i];
      for( A->CCW = extreme[d]; A->CCW != extreme[d^1] && ccw( A, A->CCW, A->CCW->CCW ) <= 0; A->CCW = A->CCW->CCW )
         if( A->CCW != extreme[d] )
            sub(&area, A->CCW );
      for( A->CW  = extreme[d]; A->CW  != extreme[d^1] && ccw( A, A->CW,  A->CW->CW   ) >= 0; A->CW  = A->CW->CW   )
         if( A->CW != extreme[d] )
            sub(&area, A->CW );
      if( A->CW != extreme[d] && A->CCW != extreme[d] )
         sub(&area, extreme[d] );
      add(&area, A );
      if( A->x < extreme[LEFT ]->x ) extreme[LEFT ] = A;
      if( A->x > extreme[RIGHT]->x ) extreme[RIGHT] = A;
      if( A->y < extreme[DOWN ]->y ) extreme[DOWN ] = A;
      if( A->y > extreme[UP   ]->y ) extreme[UP   ] = A;
      result[i] = area;
   }
   return result;
}
typedef pt*ppoint;
int cmp_x(const void*pa, const void*pb){
   ppoint*A=(ppoint*)pa;
   ppoint*B=(ppoint*)pb;
   pt*a = *A;
   pt*b = *B;
   return(a->x < b->x)?-1:1;
}
int cmp_y(const void*pa, const void*pb){
   ppoint*A=(ppoint*)pa;
   ppoint*B=(ppoint*)pb;
   pt*a = *A;
   pt*b = *B;
   return(a->y < b->y)?-1:1;
}

int main(){
   int n;
   scanf( "%d", &n );
   pt*data = calloc(n, sizeof(pt));
   for( int i = 0; i < n; ++i )
      scanf( "%lld%lld ", &data[i].x, &data[i].y );
   ppoint*order = calloc(n, sizeof(ppoint));
   for( int i = 0; i < n; ++i )
      order[i] = data + i;
   pt *extreme[4];
   qsort(order, n, sizeof(ppoint), cmp_x);
   connect( n, order, extreme, LEFT, RIGHT );
   qsort(order, n, sizeof(ppoint), cmp_y);
   connect( n, order, extreme, DOWN, UP  );
   char*chosen = calloc(n,sizeof(char));
   gets(chosen);
   go_inwards( chosen, order, n-2, extreme );
   extreme[LEFT ]->CCW = extreme[LEFT ]->CW = extreme[RIGHT];
   extreme[RIGHT]->CCW = extreme[RIGHT]->CW = extreme[LEFT ];
   ll*result = go_outwards( chosen, order, n-2, extreme);
   for(int i=0; i<n-2; ++i)
      printf( "%lld.%lld\n", result[i]>>1, (result[i]&1)*5 );
   free(order );
   free(data  );
   free(chosen);
   free(result);
   return 0;
}

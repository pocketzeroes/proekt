#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
      a[++j] = a[i];
	return j + 1;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef long long ll;
enum{ MAX = 4000};
int gcd( int a, int b ) { return b == 0 ? a : gcd( b, a%b ); }
int A, B, L;
vec rastav[MAX+1];

vec umnozak(vec*a, vec*b){
   vec ret=newVec();
   for(int z=0;z<a->sz;z++){int it=a->ptr[z];
      for(int q=0;q<b->sz;q++){int jt=b->ptr[q];
         if(it == jt)
            ret.ptr = pushback(ret.ptr, &ret.sz, it);
         else
            ret.ptr = pushback(ret.ptr, &ret.sz, it*jt);
      }
   }
   qsort(ret.ptr, ret.sz, sizeof(int), cmp);
   ret.sz = unique(ret.ptr, ret.sz);
   return ret;
}
ll ne_vidi(vec*a){
   ll ret = 0;
   int n = a->sz;
   for( int mask = 1; mask < (1<<n); ++mask ){
      int x = 1;
      int bits = 0;
      for( int i = 0; i < n; ++i ){
         if( (mask>>i) & 1 ) {
            x = x / gcd( x, a->ptr[i] ) * a->ptr[i];
            ++bits;
         }
      }
      if( bits & 1 )
         ret += L / x;
      else
         ret -= L / x;
   }
   return ret;
}
int main(){
   scanf("%d %d %d", &A, &B, &L);
   for(int i = 1; i <= MAX; ++i){
      int x = i;
      for( int d = 2; d*d <= x; ++d){
         if( x%d == 0){
            while( x%d == 0 )
               x /= d;
            rastav[i].ptr = pushback(rastav[i].ptr, &rastav[i].sz, d);
         }
      }
      if(x>1)
         rastav[i].ptr = pushback(rastav[i].ptr, &rastav[i].sz, x);
   }
   ll vidi[3] = { 0LL, 0LL, 0LL };
   for( int dx = 0; dx <= (A+B)/2; ++dx ){
      ll nevidi1 = dx == 0 ? L-1 : ne_vidi(&rastav[dx]);
      ll nevidi2 = ne_vidi(&rastav[(A+B)-dx]);
      vec vv;
      if(rastav[dx].sz>0 && rastav[(A+B)-dx].sz>0)
         vv = umnozak(&rastav[dx], &rastav[(A+B)-dx]);
      else
         goto here;
      ll nevidi12;
      nevidi12 = dx == 0 ? nevidi2 : ne_vidi(&vv);
if(0){
here:
      nevidi12 = dx == 0 ? nevidi2 : 0;
}
      int koliko = (2*dx == (A+B)) ? 1 : 2;
      vidi[0] += koliko*nevidi12;
      vidi[1] += koliko*(nevidi1 + nevidi2 - 2*nevidi12);
      vidi[2] += koliko*(L - nevidi1 - nevidi2 + nevidi12);
   }
   for( int i = 0; i < 3; ++i ) 
      printf( "%lld\n", vidi[i] );
   return 0;
}

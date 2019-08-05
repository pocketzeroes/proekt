#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
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
int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}

enum{ MAX = 500000};

typedef struct{
   int L, R;
}cvor;
cvor lista[MAX+2];
int prosli[MAX+1];
int M[MAX+1];

int main(){
   int n, m;
   scanf( "%d%d", &n, &m );
   for( int i = 0; i <= n+1; ++i ) {
      lista[i].L = i-1;
      lista[i].R = i+1;
   }
   for( int i = 0; i < m; ++i ) {
      char c; int x, y;
      scanf( " %c%d%d", &c, &x, &y );
      lista[lista[x].R].L = lista[x].L;
      lista[lista[x].L].R = lista[x].R;
      if( c == 'A' ) {
         lista[x].L = lista[y].L;
         lista[x].R = y;
      }
      else {
         lista[x].L = y;
         lista[x].R = lista[y].R;
      }
      lista[lista[x].R].L = x;
      lista[lista[x].L].R = x;
   }
   M[0] = 0;
   for( int i = 1; i <= n; ++i )
      M[i] = 1000000000;
   int najdulji = 0;
   for( int x = lista[0].R; x != n+1; x = lista[x].R ) {
      int d = upper_bound(M, n, x);
      M[d] = x;
      prosli[x] = M[d-1];
      najdulji = max(najdulji, d);
   }
   printf( "%d\n", n - najdulji );
   vec A = newVec();
   for(int x = M[najdulji]; x != 0; x = prosli[x])
      A.ptr = pushback(A.ptr, &A.sz, x);
   reverse(A.ptr, 0, A.sz-1);
   int i = 0, j = 1;
   while( i < najdulji){
      if( j == A.ptr[i] ) 
         ++i;
      else
         printf( "A %d %d\n", j, A.ptr[i] );
      ++j;
   }
   int zadnji = A.ptr[A.sz-1];
   while( j <= n ){
      printf( "B %d %d\n", j, zadnji );
      zadnji = j;
      ++j;
   }
   return 0;
}

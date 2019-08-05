#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define Row first
#define Col second
vecs rez;
vecp koord;
int R, S, mat[ 105 ][ 105 ], niz[ 10005 ];
int recon[ 20005 ], moguce[ 20005 ] = { 1 };
int sumuk[ 20005 ] = { 0 }, negativnih = 0;
int por[ 10005 ], tmp[ 105 ], cnt = 0;
char tmpbuff[ 105 ], ozn[ 105 ][ 105 ];


void rotaterow( int row, int K ){
    for( int i = 0; i < S; ++i )
        tmp[ ( i + K ) % S ] = mat[ row ][ i ];
    for( int i = 0; i < S; ++i )
        mat[ row ][ i ] = tmp[ i ];
    for( int i = 0; i < koord.sz; ++i)
        if(koord.ptr[ i ].Row == row )
           koord.ptr[ i ].Col = ( koord.ptr[ i ].Col + K ) % S;
    sprintf( tmpbuff, "rotR %d %d", row + 1, K );
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(tmpbuff));
}
void rotatecol( int col, int K ) {
    for( int i = 0; i < R; ++i )
        tmp[ ( i + K ) % R ] = mat[ i ][ col ];
    for( int i = 0; i < R; ++i )
        mat[ i ][ col ] = tmp[ i ];
    for( int i = 0; i < ( int )koord.sz; ++i )
        if( koord.ptr[ i ].Col == col )
            koord.ptr[ i ].Row = ( koord.ptr[ i ].Row + K ) % R;
    sprintf( tmpbuff, "rotS %d %d", col + 1, K );
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(tmpbuff));
}
void changerow( int row ) {
    for( int i = 0; i < S; ++i )
        mat[ row ][ i ] = -mat[ row ][ i ];
    sprintf( tmpbuff, "negR %d", row + 1 );
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(tmpbuff));
}
void changecol( int col ) {
    for( int i = 0; i < R; ++i )
        mat[ i ][ col ] = -mat[ i ][ col ];
    sprintf( tmpbuff, "negS %d", col + 1 );
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(tmpbuff));
}
int suma( int a, int b ){
    if( a > b )
        return 0;
    return (sumuk[ b ] - ( a == 0 ? 0 : sumuk[ a-1 ] ));
}
int evalpod( int X ){
    return( suma( X, R * S - 1 ) - suma( 0, X - 1 ) );
}
pair pronadji( int X ){
    for( int i = 0; i < R; ++i )
        for( int j = 0; j < S; ++j )
            if( !ozn[ i ][ j ]  &&  mat[ i ][ j ] == X ) {
                ozn[ i ][ j ] = 1;
                return newPair( i, j );
            }
    return newPair( -1, -1 );
}
void sredi_stupac(){
    int len = ( int )koord.sz;
    for( int i = 0; i < len; ++i ) {
        int razl = i - koord.ptr[ i ].Row;
        if( razl < 0 )
            razl += R;
        if( koord.ptr[ i ].Col == 0 )
            rotaterow( koord.ptr[ i ].Row, 1 );
        if( koord.ptr[ i ].Row != i )
            rotatecol( koord.ptr[ i ].Col, razl );
        rotaterow( koord.ptr[ i ].Row, S - koord.ptr[ i ].Col );
    }
}
void sredi_redak(){
    int len = ( int )koord.sz;
    for( int i = 0; i < len; ++i ) {
        int razl = i - koord.ptr[ i ].Col;
        if( razl < 0 ) razl += S;
        if( koord.ptr[ i ].Row == 0 ) rotatecol( koord.ptr[ i ].Col, 1 );
        if( koord.ptr[ i ].Col != i ) rotaterow( koord.ptr[ i ].Row, razl );
        rotatecol( koord.ptr[ i ].Col, R - koord.ptr[ i ].Row );
    }
}
int main(){
    scanf( "%d %d", &R, &S );
    for( int i = 0; i < R; ++i ){
        for( int j = 0; j < S; ++j ) {
            scanf( "%d", &mat[ i ][ j ] );
            niz[ S * i + j ] = mat[ i ][ j ];
        }
    }
    qsort(niz, R*S, sizeof(int), cmp);
    for( int i = 0; i < R * S; ++i ) {
        negativnih += ( niz[ i ] < 0 );
        sumuk[ i ] = ( i > 0 ? sumuk[ i-1 ] : 0 ) + niz[ i ];
        if( !moguce[ i ] )
            continue;
        moguce[ i + R ] = 1;
        moguce[ i + S ] = 1;
        recon [ i + R ] = i;
        recon [ i + S ] = i;
    }
    int X, A = -1, B = -1;
    for( int i = 0; i <= R * S; ++i ) {
        if( !moguce[ i ] )
            continue;
        if( i <= negativnih )
            A = i;
        if( i >= negativnih && B == -1 )
            B = i;
    }
    if( A == -1 ) 
        X = B; 
    else if( B == -1 ) 
        X = A;
    else 
        X = ( evalpod( A ) > evalpod( B ) ? A : B );
    int prez = evalpod( X );
    while( X != 0 ){
        por[ cnt++ ] = X;
        X = recon[ X ];
    }
    por[ cnt++ ] = 0;
    reverse(por, 0, cnt-1);
    for( int i = 0; i < cnt-1; ++i ) {
        memset( ozn, 0, sizeof( ozn ) );
        koord.sz=0;
        for(int j = por[ i ]; j < por[ i + 1 ]; ++j)
            koord.ptr = pushbackP(koord.ptr, &koord.sz, pronadji(niz[j]));
        if( por[ i + 1 ] - por[ i ] == R ){
            sredi_stupac();
            changecol( 0 );
        }
        else{
            sredi_redak();
            changerow( 0 );
        }
    }
    printf("%d %d\n", prez, rez.sz);
    for(int i = 0; i < rez.sz; ++i)
        puts(rez.ptr[i]);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////
enum{ MAXNODE = 2*132072};
enum{ MAXQ = 100100};
typedef long long ll;
int n, q;
int _L, _R;
int _A, _B;

ll solve(ll a, ll b, ll n);

typedef struct{
    int a,
        b,
        poc;
    int size;
    ll  suma;
}node;
void update(node*tva, node*A, node*B){
    tva->suma = A->suma + B->suma;
}
void set_it(node*tva, int aa, int bb, int pocc){
    tva->a   = aa;
    tva->b   = bb;
    tva->poc = pocc;
    tva->suma = solve(tva->a, tva->b, tva->poc + tva->size-1 ) -
                solve(tva->a, tva->b, tva->poc-1 );
}
void spread(node*tva, node*A, node*B){
    if(tva->b != 0){
        set_it(A, tva->a, tva->b, tva->poc );
        set_it(B, tva->a, tva->b, tva->poc + A->size);
    }
    tva->b = 0;
}
    
node h[ MAXNODE ];
vec Rez;
//typedef struct{
void init( int x, int l, int r ){
    h[x].size = Rez.ptr[r] - Rez.ptr[l];
    if( l+1 == r )
        return ;
    int mid = ( l + r ) / 2;
    init( 2*x, l, mid );
    init( 2*x+1, mid, r );
}
ll query( int x, int l, int r ){
    if( _R <= l || r <= _L )
        return 0;
    if( _L <= l && r <= _R )
        return h[x].suma;
    spread(&h[x], &h[2*x], &h[2*x+1]);
    int mid = ( l + r ) / 2;
    return query( 2*x, l, mid ) +
           query( 2*x+1, mid, r );
}
void T_update(int x, int l, int r){
    if( _R <= l || r <= _L )
        return;
    if( _L <= l && r <= _R ){
        set_it(&h[x], _A, _B, Rez.ptr[l]-Rez.ptr[_L]+1 );
        return ;
    }
    spread(&h[x], &h[2*x], &h[2*x+1]);
    int mid = ( l + r ) / 2;
    T_update( 2*x, l, mid );
    T_update( 2*x+1, mid, r );
    update(&h[x], &h[2*x], &h[2*x+1]);
}
//}tournament;
//tournament T;

typedef struct{
    int type;
    int l, r;
    int a, b;
}qry;
qry Q[ MAXQ ];

qry newquery(int p1, int p2, int p3, int p4, int p5){
    qry rez;
    rez.type=p1;
    rez.l=p2;
    rez.r=p3;
    rez.a=p4;
    rez.b=p5;
    return rez;
}



ll gcd( ll a, ll b ){
    return b ? gcd( b, a%b ) : a;
}
ll calc( ll a, ll b, ll n ){
    ll x = a / b;
    ll sum = x*n*(n+1) / 2;
    a %= b;
    if( a == 0 || b == 0 )
        return sum;
    ll diag = n/b;
    ll zadnji = a*n/b;
    return sum + n*zadnji - calc( b, a, zadnji ) + diag;
}
ll solve(ll a, ll b, ll n){
    if( n < 1 )
        return 0;
    ll g = gcd( a, b );
    return n*(n+1)/2*a - b*calc( a/g, b/g, n );
}
int main(){
    scanf("%d %d", &n, &q);
//  Rez.reserve(2*q + 100);
    Rez.ptr = pushback(Rez.ptr, &Rez.sz, 0);
    Rez.ptr = pushback(Rez.ptr, &Rez.sz, n);
    for(int counter = 0; counter < q; ++counter){
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        _L = --l;
        _R = --r;
        Rez.ptr = pushback(Rez.ptr, &Rez.sz, l );
        Rez.ptr = pushback(Rez.ptr, &Rez.sz, r+1 );
        if( type == 1 ){
            scanf( "%d %d", &_A, &_B ); _A %= _B;
            Q[counter] = newquery( type, l, r, _A, _B );
        }
        else
            Q[counter] = newquery( type, l, r, 0, 0 );
    }
    qsort( Rez.ptr, Rez.sz, sizeof(int), cmp);
    init( 1, 0, Rez.sz-1);
    for( int counter = 0; counter < q; ++counter ){
        _L = lower_bound( Rez.ptr, Rez.sz, Q[counter].l );
        _R = upper_bound( Rez.ptr, Rez.sz, Q[counter].r );
        _A = Q[counter].a;
        _B = Q[counter].b;
        if( Q[counter].type == 1 )
            T_update( 1, 0, Rez.sz - 1 );
        else
            printf( "%lld\n", query( 1, 0, Rez.sz - 1 ) );
    }
    return 0;
}

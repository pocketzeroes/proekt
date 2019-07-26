#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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


enum{ MAXN = 100100};
enum{ MAXE = 200100 + 2*MAXN};
int  n, e;
int  A[ MAXE ], B[ MAXE ];
char E_ziv[ MAXE ];
char pobojaj[ MAXE ];
char posjetio[ MAXN ];
char bio[ MAXN ][ 2 ];
vec  E[ MAXN ];
int  OrgSize[ MAXN ];
int  e_tmp = 0;
int  n_tmp = 0;
int  last_boja = 0;

typedef struct{
    int x;
    int i;
    int e;
}trip;
trip newtrip(int a, int b, int c){
    return(trip){a,b,c};
}

#include<stddef.h>
#include<stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef trip T;

typedef struct{
    T *bottom;
    T *top;
    T *allocated_top;
}
stack;
stack * new(void){
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
void destroy(stack *s){
  free(s->bottom);
  free(s);
}
bool empty(stack *s){
    return s->top < s->bottom ? true : false;
}
void push(stack *s, T x){
    if (s->top == s->allocated_top)
    {
        ptrdiff_t qtty = s->top - s->bottom + 1;
        ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
        s->bottom = realloc(s->bottom, new_qtty * sizeof(T));
        check_pointer(s->bottom);
        s->top = s->bottom + qtty - 1;
        s->allocated_top = s->bottom + new_qtty - 1;
    }
    *(++s->top) = x;
}
T pop(stack *s){
    return *(s->top--);
}
T top(stack *s){
    return *(s->top);
}

stack*Stk;//of trip

void euler_iterativni(int Pocetak){
    for( push(Stk, newtrip(Pocetak, 0, -1)); !empty(Stk);){
        trip P = top(Stk); pop(Stk);
        int x = P.x;
        posjetio[ x ] = true;
        if( P.e != -1 ){
            bio[ A[ P.e ] ][ last_boja ] = true;
            bio[ B[ P.e ] ][ last_boja ] = true;
            pobojaj[ P.e ] = last_boja;
            last_boja ^= 1;
        }
        for( ; E[x].sz>0; ){
            int ind = E[x].ptr[E[x].sz-1];
            if( E_ziv[ ind ] == false ){
                E[x].sz--;
                continue;
            }
            E_ziv[ ind ] = false;
            E[x].sz--;
            int y = A[ind] + B[ind] - x;
            push(Stk, newtrip( x, -1, ind));
            push(Stk, newtrip( y, -1, -1 ));
            break;
        }
    }
}
int main(){
    Stk=new();
    memset( bio, 0, sizeof bio );
    memset( E_ziv, 1, sizeof bio );
    memset( posjetio, 0, sizeof posjetio );
    scanf( "%d %d", &n, &e );
    for( int i = 0; i < e; ++i ) {
        int a, b; scanf( "%d %d", &a, &b ); --a, --b;
        A[i] = a; B[i] = b;
        E[a].ptr = pushback(E[a].ptr, &E[a].sz, i);
        E[b].ptr = pushback(E[b].ptr, &E[b].sz, i);
    }
    for(int i=0; i<n; ++i)
        OrgSize[i] = E[i].sz;
    n_tmp = n+1;
    e_tmp = e;
    for( int i = 0; i < n; ++i ){
        if(E[i].sz%2 ==1){
            A[ e_tmp ] = i; B[ e_tmp ] = n;
            E[i].ptr=pushback(E[i].ptr, &E[i].sz, e_tmp);
            E[n].ptr=pushback(E[n].ptr, &E[n].sz, e_tmp);
            ++e_tmp;
        }
    }
    for( int i = n; i >= 0; --i ){
        if( posjetio[i] == true )
            continue;
        if( i == n || E[i].sz >= 4)
            euler_iterativni( i );
    }
    for( int i = 0; i < n; ++i ){
        if( posjetio[i] == true )
            continue;
        euler_iterativni( i );
    }
    int ok = true;
    for( int i = 0; i < n; ++i )
        if( OrgSize[i] > 0 && bio[i][0] + bio[i][1] != 2 )
            ok = false;
    if( ok )
        for( int i = 0; i < e; ++i )
            printf( "%d\n", pobojaj[i] + 1 );
    else
        printf( "0\n" );
    return 0;
}

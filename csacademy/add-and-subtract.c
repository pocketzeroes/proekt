#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

#define swapp(a,b) do\
    {\
     pair tmp = a;\
     a        = b;\
     b        = tmp;\
    } while (0)        

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}




typedef long long ll;

enum{ MAX =(int) 100005};
enum{ oo  =(ll ) 1e14+7};
enum{ mod =(ll ) 1e9+7 };
typedef pair pii;



ll n,arr[MAX],sol[MAX];

typedef struct node_s{
    bool active,lazy;
    ll mx,mn,lmx,lmn,rmx,rmn,s;
    pii imx,imn,ilmx,ilmn,irmx,irmn;
}node;

node Tree[4*MAX];




void join( node l , node r , node*p){
    if( l.active == 0 && r.active == 0 ){
        p->active = 0; return;
    }
    p->active = 1;
    if( l.active == 0 ){
       *p = r; return;
    }
    if( r.active == 0 ){
       *p = l; return;
    }
    if( l.mx > r.mx ){p->mx = l.mx; p->imx = l.imx; }
    else { p->mx = r.mx; p->imx = r.imx; }
    if( (l.rmx + r.lmx) > p->mx ){ p->mx = (l.rmx + r.lmx); p->imx = newPair( l.irmx.first , r.ilmx.first ); }
    if( l.mn < r.mn ){p->mn = l.mn; p->imn = l.imn; }
    else { p->mn = r.mn; p->imn = r.imn; }
    if( (l.rmn + r.lmn) < p->mn ){ p->mn = (l.rmn + r.lmn); p->imn = newPair( l.irmn.first , r.ilmn.first ); }
    if( l.lmx > (2*l.s + r.lmx) ){ p->lmx = l.lmx; p->ilmx = l.ilmx;}
    else{ p->lmx = (2*l.s + r.lmx); p->ilmx = r.ilmx; }
    if( l.lmn < (2*l.s + r.lmn) ){ p->lmn = l.lmn; p->ilmn = l.ilmn;}
    else{ p->lmn = (2*l.s + r.lmn); p->ilmn = r.ilmn; }
    if( r.rmx > (2*r.s + l.rmx) ){ p->rmx = r.rmx; p->irmx = r.irmx; }
    else { p->rmx = (2*r.s + l.rmx); p->irmx = l.irmx; }
    if( r.rmn < (2*r.s + l.rmn) ){ p->rmn = r.rmn; p->irmn = r.irmn; }
    else { p->rmn = (2*r.s + l.rmn); p->irmn = l.irmn; }
    p->s = l.s + r.s;
    return;
}
void propagate( int a , int b , int key , node*p){
    if( p->lazy == 1 ){
        p->lazy = 0;
        if( a != b ){
            swap( p->mx , p->mn ); p->mx *= -1; p->mn*=-1;
            swap( p->lmx , p->lmn );p->lmx*= -1 ; p->lmn*= -1;
            swap( p->rmx , p->rmn );p->rmx*= -1; p->rmn*= -1;
            
            swapp( p->imx , p->imn );
            swapp( p->ilmx , p->ilmn );
            swapp( p->irmx , p->irmn );
            p->s *= -1;
            Tree[2*key].lazy ^= 1;
            Tree[2*key+1].lazy ^= 1;
        }
        else{
            swap( p->lmx , p->lmn );p->lmx*= -1 ; p->lmn*= -1;
            swap( p->rmx , p->rmn );p->rmx*= -1; p->rmn*= -1;
            
            swapp( p->imx , p->imn );
            swapp( p->ilmx , p->ilmn );
            swapp( p->irmx , p->irmn );
            p->s *= -1;
        }
    }
}
void update1( int id , int a , int b , int key ){
    propagate( a , b , key , &Tree[key] );
    if( id < a || id > b )
        return;
    if( id == a && id == b ){
        Tree[ key ].active = 0;
        return;
    }
    int m = (a+b)/2;
    update1( id , a , m , 2*key );
    update1( id , m+1 , b , 2*key + 1);
    join( Tree[2*key] , Tree[2*key+1] , &Tree[key] );
}
void update2( int l , int r , int a , int b , int key ){
    propagate( a , b , key , &Tree[key] );
    if( a > r || b < l )
        return;
    if( a >= l && b <= r ){
        Tree[key].lazy ^= 1;
        propagate( a , b , key , &Tree[key] );
        return;
    }
    int m = (a+b)/2;
    update2( l , r , a , m , 2*key );
    update2( l , r , m+1 , b , 2*key+1 );
    join( Tree[2*key] , Tree[2*key+1] , &Tree[key] );
}
void query( int l , int r , int a , int b , int key , node*p){
    propagate( a , b , key , &Tree[key] );
    if( a > r || b < l )
        return;
    if( a >= l && b <= r ){
        node ax;
        join(*p , Tree[key] , &ax );
       *p = ax;
        propagate( a , b , key , &Tree[key] );
        return;
    }
    int m = (a+b)/2;
    query( l , r , a , m , 2*key , p );
    query( l , r , m+1 , b , 2*key+1 , p );
    join( Tree[2*key] , Tree[2*key+1] , &Tree[key] );
}
void init( int a , int b , int key ){
    Tree[key].active = 1;
    Tree[key].lazy = 0;
    Tree[key].mx = -oo; Tree[key].mn = oo;
    Tree[key].lmx = Tree[key].lmn = Tree[key].rmx = Tree[key].rmn = Tree[key].s = arr[a];
    Tree[key].ilmx = Tree[key].ilmn = Tree[key].irmx = Tree[key].irmn = newPair( a,0 );
    if( a == b )
        return;
    int m = (a+b)/2;
    init( a , m , 2*key );
    init( m+1 , b , 2*key+1 );
    join( Tree[2*key] , Tree[2*key+1] , &Tree[key] );
}
node INF(){
    node res;
    res.mx = res.lmx = res.rmx = -oo;
    res.mn = res.lmn = res.rmn = oo;
    res.s = 0;
    res.active = 1;
    return res;
}
int main(){
    scanf("%lld", &n);
    for( int i = 1 ; i <= n ; i++ )
        scanf("%lld", &arr[i]);
    if( (n%2) != 0 )
        arr[n+1] = oo;
    else
        arr[n+1] = -oo;
    for( int i = 1 ; i <= n+1 ; i++ )
        if( i%2 == 0 )
            arr[i] *= -1;
    init(1,n,1);
    for( int i = n ; i > 0 ; i-=2 ){
        sol[i] = Tree[1].s;
        node ax = INF();
        query( 1 , n , 1 , n , 1 , &ax );
        update2( ax.imn.first , ax.imn.second , 1 , n , 1 );
        update1( ax.imn.first , 1 , n , 1 );
        update1( ax.imn.second , 1 , n , 1 );
    }
    n++;
    init(1,n,1);
    for( int i = n ; i > 0 ; i-=2 ){
        sol[i] = Tree[1].s;
        node ax = INF();
        query( 1 , n , 1 , n , 1 , &ax );
        update2( ax.imn.first , ax.imn.second , 1 , n , 1 );
        update1( ax.imn.first , 1 , n , 1 );
        update1( ax.imn.second , 1 , n , 1 );
    }
    for( int i = 1 ; i < n ; i++ )
        printf("%lld ", sol[i]);
    puts("");
}

























































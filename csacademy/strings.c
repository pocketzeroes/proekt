#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<time.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
typedef long long Lint;

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


#define all(x) x.begin() , x.end()
#define fi first
#define se second
#define pb push_back
#define umax( x , y ) x = max( x , (y) )
#define umin( x , y ) x = min( x , (y) )
#define For( i , a ) for(int i=1;i<=a;i++)
#define ort (b+s)/2
#define y2 asrwjaelkf
#define y1 asseopirwjaelkf
#define set multiset


inline int read() {
    int res = 0 ;int neg ;
    while(true){char ch = getchar();if(ch>='0' && ch<='9' || ch=='-'){if(ch=='-') neg = -1;else neg = 1 , res = ch-'0';break;} }
    while(true){char ch = getchar();if(ch>='0' && ch<='9') res*=10 , res+=ch-'0';else break;}
    return res*neg;
}


enum{ maxn = 400020 };
enum{ maxm = 1000020};
enum{ MOd  =(int) 1e9 + 7};
enum{ P    = 43     };
int N, root;

typedef struct treap_s{
    int lh, rh, y, sz, rev, n, l, r;
}treap;

treap ar[maxn];

void create(treap*rez){
    rez->lh  = 0;
    rez->rh  = 0;
    rez->l   = 0;
    rez->r   = 0;
    rez->rev = 0;
    rez->n   = 0;
    rez->sz  = 1;
    rez->y   = (rand() << 16) ^ rand();
}

int a, q, prime[maxn];
char str[maxn];

int mul( int a, int b ) {
    return (Lint)a * b % MOd;
}
int add( int a, int b ) {
    return (a+b>=MOd)? a+b-MOd:a+b;
}
void push( int ss ) {
#define x ar[ss]
    if( x.rev ) {
        swap( x.l, x.r );
        swap( x.lh, x.rh );
        x.rev = 0;
        ar[x.l].rev ^= 1;
        ar[x.r].rev ^= 1;
    }
#undef x
}
void relax( int ss ) {
    if( ss == 0 ) return;
    push( ss );
#define x ar[ss]
    push( x.l );
    push( x.r );
    assert( x.rev == 0 );
    x.lh = add( add( ar[x.l].lh, mul( prime[ar[x.l].sz], x.n ) ), mul( prime[ar[x.l].sz+1], ar[x.r].lh ) );
    x.rh = add( add( ar[x.r].rh, mul( prime[ar[x.r].sz], x.n ) ), mul( prime[ar[x.r].sz+1], ar[x.l].rh ) );
    x.sz = ar[x.l].sz + ar[x.r].sz + 1;
#undef x
}
int merge( int L, int R ) {
    push( L );
    push( R );
    if( L == 0 ) return R;
    if( R == 0 ) return L;
    if( ar[L].y < ar[R].y ) {
        ar[L].r = merge( ar[L].r, R );
        relax( L );
        return L;
    } else {
        ar[R].l = merge( L, ar[R].l );
        relax( R );
        return R;
    }
}
void split( int root, int div, int*L, int*R ){
    push( root );
    if( root == 0 ) {
       *R = *L = 0;
        return;
    }
    if( div == 0 ) {
       *L = 0;
       *R = root;
        relax( root );
        return;
    }
    if( ar[ar[root].l].sz >= div ) {
        split( ar[root].l, div, L, R );
        ar[root].l = *R;
       *R = root;
        relax( *R );
        relax( *L );
    } 
    else {
        split( ar[root].r, div - ar[ar[root].l].sz - 1, L, R );
        ar[root].r = *L;
       *L = root;
        relax( *L );
        relax( *R );
    }
}
pair get( int x, int y, int tp ) {
    pair ret = newPair( 0, 0 );
    int l = 0, m = 0, r = 0;
    split( root, y, &l, &r );
    split( l, x-1,  &l, &m );
    ret = newPair( ar[m].lh, ar[m].rh );
    root = merge( l, m );
    root = merge( root, r );
    return ret;
}
int main() {
    srand( time( 0 ) );
    scanf("%d %d",&a,&q);
    scanf(" %s",str+1);
    prime[0] = 1;
    for(int i=1;i<=a+q;i++) 
        prime[i] = mul( prime[i-1], P );
    for(int i=1;i<=a;i++) {
        create(&ar[++N]);
        ar[N].lh = ar[N].rh = ar[N].n = str[i] - 'a' + 1;
        root = merge( root, N );
    }
    while( q-- ) {
        char c;
        int x, y, k;
        scanf(" %c",&c);
        if( c == 'Q' ) {
            scanf("%d %d",&x,&y);
            int len = (y-x+1)/2;
            pair t  = get( x, x+len-1, 0 );
            pair t2 = get( y-len+1, y, 1 );
            if( t.fi == t2.se ) 
                printf("YES\n");
            else 
                printf("NO\n");
        }
        else {
            int tp;
            scanf("%d",&tp);
            if( tp == 1 ) {
                scanf("%d %d %d",&x,&y,&k);
                int l = 0, m = 0, r = 0;
                split( root, y, &l, &r );
                split( l, x-1,  &l, &m );
                root = merge( l, r );
                split( root, k, &l, &r );
                root = merge( l, m );
                root = merge( root, r );
            }
            else if( tp == 2 ) {
                scanf("%d %d",&x,&y);
                int l = 0, m = 0, r = 0;
                split( root, y, &l, &r );
                split( l, x-1,  &l, &m );
                ar[m].rev ^= 1;
                root = merge( l, m );
                root = merge( root, r );
            }
            else if( tp == 3 ) {
                char ch;
                scanf("%d %c",&x,&ch);
                int l=0, r=0;
                split( root, x-1, &l, &r );
                create(&ar[++N]);
                ar[N].lh = ar[N].rh = ar[N].n = ch - 'a' + 1;
                root = merge( l, N );
                root = merge( root, r );
            }
        }
    }
    return 0;
}




















































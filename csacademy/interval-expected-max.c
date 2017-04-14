#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif

typedef  double ld;
typedef  long long ll;

enum{ MAXN =(int) 1e5 + 17}; 
enum{ MOD  =(int) 1e9 + 7 }; 
enum{ sq   =(int) 333     };

typedef struct queryS{
    int l, r, ind;
}query;
query*v=NULL;int vSz=0;

query newQuery(int _x, int _y, int _z)
{
    query rez;
    rez.l=_x;
    rez.r=_y;
    rez.ind=_z;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
query*pushback(query*array, int *size, query value){
    query*output = resizeArray(array, query, *size + 1);
    output[(*size)++] = value;
    return output;
}




int a    [MAXN];
ll ans   [MAXN];
ll fen[2][MAXN];
ll k;
ll sz    [MAXN];

int cmp(const void*pa,const void*pb)
{
   query*ptra=(query*)pa;
   query*ptrb=(query*)pb;
   query a= *ptra;
   query b= *ptrb;
   if(a.l/sq != b.l/sq)
      return(a.l/sq < b.l / sq)?-1:1;
   return (a.r < b.r)?-1:1;
}
inline void ad(int x , int f)
{
    int k = x ;
    for(  ; x < MAXN ; x += x&-x)
        fen[0][x] += f , fen[1][x] += f*k ;
}
inline int get1(int x)
{
    int ans = 0 ;
    for( ; x ; x -= x&-x  )
        ans += fen[0][x] ;
    return ans ;
}
inline ll get2(int x)
{
    ll ans = 0 ;
    for( ; x ; x -= x&-x  )
        ans += fen[1][x] ;
    return ans ;
}
inline void add(int i)
{
    ll x = get1(a[i]) ;
    k += (2*x+1) * a[i] ;
    k += 2 * ( get2(MAXN-1) - get2(a[i]) );
    ad(a[i],1) ;
}
inline void rem(int i)
{
    ll x = get1(a[i]) ;
    k -= (2*x-1) * a[i] ;
    k -= 2 * ( get2(MAXN-1) - get2(a[i]) );
    ad(a[i],-1) ;
}
int main()
{
   int n,q;
   scanf("%d%d",&n,&q);
   for(int i = 0 ; i < n ; i++)
      scanf("%d",&a[i]);
   v=pushback(v, &vSz, newQuery(0,1,q));
   for(int i = 0 ; i < q ; i++)
   {
      int l , r;
      scanf("%d%d",&l,&r);
      l--;
      r--;
      sz[i] = 1LL * (r-l+1)*(r-l+1);
      v=pushback(v,&vSz,newQuery(l,r,i));
   }
   if(n+q>1000)
      qsort(v, vSz, sizeof(query), cmp);
   add(0);
   int x = 0 , y = 0 ;
   for(int i = 1 ; i <= q; i ++ )
   {
      while(y<v[i].r)  add(++y);
      while(x>v[i].l)  add(--x);
      while(x<v[i].l)  rem(x++);
      while(y>v[i].r)  rem(y--);
      ans[v[i].ind] = k;
   }
   for(int i = 0 ; i < q ; i++)
      printf("%.8lf\n",(ld)ans[i]/sz[i]);
}



























































#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper") 
#pragma GCC target("avx") 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
static inline int min(int a, int b){return a<b?a:b;}
static inline int max(int a, int b){return a>b?a:b;}

#define STB_(prefix,name)     stb__##prefix##name

#define stb_declare_sort(FUNCNAME, TYPE)    \
                       void FUNCNAME(TYPE *p, int n)
#define stb_define_sort(FUNCNAME,TYPE,COMPARE) \
                       stb__define_sort(       void, FUNCNAME,TYPE,COMPARE)
#define stb_define_sort_static(FUNCNAME,TYPE,COMPARE) \
                       stb__define_sort(static void, FUNCNAME,TYPE,COMPARE)

#define stb__define_sort(MODE, FUNCNAME, TYPE, COMPARE)                       \
                                                                              \
static void STB_(FUNCNAME,_ins_sort)(TYPE *p, int n)                          \
{                                                                             \
   int i,j;                                                                   \
   for (i=1; i < n; ++i) {                                                    \
      TYPE t = p[i], *a = &t;                                                 \
      j = i;                                                                  \
      while (j > 0) {                                                         \
         TYPE *b = &p[j-1];                                                   \
         int c = COMPARE;                                                     \
         if (!c) break;                                                       \
         p[j] = p[j-1];                                                       \
         --j;                                                                 \
      }                                                                       \
      if (i != j)                                                             \
         p[j] = t;                                                            \
   }                                                                          \
}                                                                             \
                                                                              \
static void STB_(FUNCNAME,_quicksort)(TYPE *p, int n)                         \
{                                                                             \
   /* threshold for transitioning to insertion sort */                       \
   while (n > 12) {                                                           \
      TYPE *a,*b,t;                                                           \
      int c01,c12,c,m,i,j;                                                    \
                                                                              \
      /* compute median of three */                                           \
      m = n >> 1;                                                             \
      a = &p[0];                                                              \
      b = &p[m];                                                              \
      c = COMPARE;                                                            \
      c01 = c;                                                                \
      a = &p[m];                                                              \
      b = &p[n-1];                                                            \
      c = COMPARE;                                                            \
      c12 = c;                                                                \
      /* if 0 >= mid >= end, or 0 < mid < end, then use mid */                \
      if (c01 != c12) {                                                       \
         /* otherwise, we'll need to swap something else to middle */         \
         int z;                                                               \
         a = &p[0];                                                           \
         b = &p[n-1];                                                         \
         c = COMPARE;                                                         \
         /* 0>mid && mid<n:  0>n => n; 0<n => 0 */                            \
         /* 0<mid && mid>n:  0>n => 0; 0<n => n */                            \
         z = (c == c12) ? 0 : n-1;                                            \
         t = p[z];                                                            \
         p[z] = p[m];                                                         \
         p[m] = t;                                                            \
      }                                                                       \
      /* now p[m] is the median-of-three */                                   \
      /* swap it to the beginning so it won't move around */                  \
      t = p[0];                                                               \
      p[0] = p[m];                                                            \
      p[m] = t;                                                               \
                                                                              \
      /* partition loop */                                                    \
      i=1;                                                                    \
      j=n-1;                                                                  \
      for(;;) {                                                               \
         /* handling of equality is crucial here */                           \
         /* for sentinels & efficiency with duplicates */                     \
         b = &p[0];                                                           \
         for (;;++i) {                                                        \
            a=&p[i];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         a = &p[0];                                                           \
         for (;;--j) {                                                        \
            b=&p[j];                                                          \
            c = COMPARE;                                                      \
            if (!c) break;                                                    \
         }                                                                    \
         /* make sure we haven't crossed */                                   \
         if (i >= j) break;                                                   \
         t = p[i];                                                            \
         p[i] = p[j];                                                         \
         p[j] = t;                                                            \
                                                                              \
         ++i;                                                                 \
         --j;                                                                 \
      }                                                                       \
      /* recurse on smaller side, iterate on larger */                        \
      if (j < (n-i)) {                                                        \
         STB_(FUNCNAME,_quicksort)(p,j);                                       \
         p = p+i;                                                             \
         n = n-i;                                                             \
      } else {                                                                \
         STB_(FUNCNAME,_quicksort)(p+i, n-i);                                  \
         n = j;                                                               \
      }                                                                       \
   }                                                                          \
}                                                                             \
                                                                              \
MODE FUNCNAME(TYPE *p, int n)                                                 \
{                                                                             \
   STB_(FUNCNAME, _quicksort)(p, n);                                           \
   STB_(FUNCNAME, _ins_sort)(p, n);                                            \
}                                                                             \

enum{maxn=14000+15  };
enum{mod =(int)1e9+7};

typedef struct{
    int from, to, cost;
}edge;
edge Edge[maxn<<2];

stb_define_sort(sort_f, edge, a->cost > b->cost)

int Power(int x, int y){
    int ret=1;
    while(y){
        if(y&1)
            ret=1ll*ret*x%mod;
        y>>=1;
        x=1ll*x*x%mod;
    }
    return ret;
}

int Poly[maxn],
    PolyDegree,
    TempDiv[maxn],
    Temp[maxn],
    n,m,
    Fa[maxn],
    Sz[maxn];
double answer;


inline void Update(int*x, int y){
    (*x) += y;
    if(*x >= mod)
      (*x)-= mod;
}
int Find_Fa(int u){
    return Fa[u]!=u ? Fa[u]=Find_Fa(Fa[u]):u;
}
void PolyDivide(int z){
    for(int i=PolyDegree-z;i>=0;--i){
        Update(&Poly[i], mod-Poly[i+z]);
        TempDiv[i]=Poly[i+z];
    }
    PolyDegree-=z;
    memcpy(Poly, TempDiv, (PolyDegree+1)<<2);
}
void PolyMultiply(int z){
    memset(Poly+PolyDegree+1,0,(z+1)<<2);
    for(int i=PolyDegree;i>=0;--i)
        Update(&Poly[i+z], Poly[i]);
    PolyDegree+=z;
}
void Union_Set(int u, int v){
    int p1=Find_Fa(u), 
        p2=Find_Fa(v);
    if(p1==p2)
        return;
    PolyMultiply(Sz[p1]+Sz[p2]);
    Fa[p1]=p2;
    Sz[p2]+=Sz[p1];
}
void Solve(int from, int to, int cost){
    int p1=Find_Fa(from), 
        p2=Find_Fa(to);
    if(p1==p2)
        return;
    PolyDivide(Sz[p1]);
    PolyDivide(Sz[p2]);
    int ret=0;
    for(int i=0;i<=PolyDegree;++i)
        if(Poly[i]){
            int a=i, b=PolyDegree-i;
            ret = max(ret, min(Sz[p1]+a+b, Sz[p2]    ));
            ret = max(ret, min(Sz[p1]+a  , Sz[p2]+b  ));
            ret = max(ret, min(Sz[p1]+b  , Sz[p2]+a  ));
            ret = max(ret, min(Sz[p1]    , Sz[p2]+a+b));
        }
    answer = fmin(answer, 1.*cost/ret);
}
int main(){
    scanf("%d %d", &n, &m);
    answer=1e66;
    for(int i=0; i<n; i++)
        Fa[i]=i, Sz[i]=1;
    for(int i=0; i<m; i++)
        scanf("%d %d %d", &Edge[i].from, &Edge[i].to, &Edge[i].cost);
    sort_f(Edge, m);
    for(int i=0,j=1; i<=n; ++i)
        Poly[i]=j, j=1ll*j*(n-i)%mod*Power(i+1,mod-2)%mod;
    PolyDegree=n;
    for(int i=0; i<m; ++i){
        Solve(Edge[i].from, Edge[i].to, Edge[i].cost);
        Union_Set(Edge[i].from, Edge[i].to);
    }
    printf("%.10lf\n", answer);
    return 0;
}

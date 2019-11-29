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




typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

enum{ MAXN = 2005};
enum{ MAXK = 9   };
typedef long long ll;
int n, k;
int mat[MAXN][MAXN];

typedef struct Field{
  pair pos;
  bool dir;
  int  sum;
}Field;

stb_define_sort(sort_f, Field, a->sum > b->sum)


Field newField(pair pos, bool dir){
  Field rez;
  rez.pos = pos;
  rez.dir = dir;
  int x = pos.first;
  int y = pos.second;
  rez.sum = mat[x][y] + mat[x+dir][y+(1-dir)];
  return rez;
}
pair*get_fields(Field*f){
  int x = f->pos.first;
  int y = f->pos.second;
  pair*ret = calloc(2, sizeof(pair));
  ret[0] = newpair(x, y);
  ret[1] = newpair(x + f->dir, y+(1 - f->dir));
  return ret;
}
bool intersect(Field*A, Field*B){
  pair*Af = get_fields(A);
  pair*Bf = get_fields(B);
  for(int i=0;i<2;i++){pair a = Af[i];
    for(int j=0;j<2;j++){pair b = Bf[j];
      if(a.first  == b.first&&
         a.second == b.second)
        return true;
    }
  }
  return false;
}

short val      [MAXN];
ll    mask     [MAXN];
short best_left[1<<20][MAXK];

void solve_left (int pos, int sz, int cmask, ll blocked, short sum, int cnt){
  if (cnt > k) 
    return;
  if(pos == sz){
    best_left[cmask][cnt] = sum;
    return;
  }
  solve_left(pos+1, sz, cmask, blocked, sum, cnt);
  if(!(blocked & (1LL << pos)))
    solve_left(pos+1, sz, cmask | (1LL << pos), blocked | mask[pos], sum + val[pos], cnt + 1);
}
int  solve_right(int pos, int sz, int szl,   ll blocked, short sum, int cnt){
  if (cnt > k)
    return 0;
  if (pos == sz)
    return sum + best_left[(~blocked) & ((1 << szl) - 1)][k - cnt];
  int ret = solve_right(pos+1, sz, szl, blocked, sum, cnt);
  if(!(blocked & (1LL << pos)))
    ret = fmax(ret, solve_right(pos+1, sz, szl, blocked | mask[pos], sum + val[pos], cnt + 1));
  return ret;
}
int  solve(int sz){
 int lsz = sz / 2;
  while (lsz > 20)
    --lsz;
  solve_left(0, lsz, 0, 0, 0, 0);
  for(int i = 0; i < (1 << lsz); ++i){
    int pos = i;
    while(pos > 0){
      int bit = pos&-pos;
      for (int j = 0; j <= k; ++j)
        best_left[i][j] = fmax(best_left[i][j], best_left[i - bit][j]);
      pos -= bit;
    }
  }
  return solve_right(lsz, sz, lsz, 0, 0, 0);
}

int main(){
  scanf("%d%d", &n, &k);
  int Vsize=n*n*2;
  Field*V = calloc(Vsize, sizeof(Field));
  int fsz=0;
  ll sum = 0;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      scanf("%d", &mat[i][j]);
      sum += mat[i][j];
    }
  }
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      V[fsz++] = newField(newpair(i, j), 0);
      V[fsz++] = newField(newpair(i, j), 1);
    }
  }
  int sz = fmin(Vsize, (k - 1)*7 + 1);
  sort_f(V, Vsize);
  for(int i=0; i<sz; ++i)
    val[i] = V[i].sum;
  for(int i=0; i<sz; ++i)
    for(int j=0; j<sz; ++j)
      if(intersect(&V[i], &V[j]))
        mask[i] |= (1LL << j);
  printf("%lld\n", sum - solve(sz));
  return 0;
}

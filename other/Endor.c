#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#define pos first
#define col second

enum{ MAXN = 100010};
enum{ MAXK = 55    };

typedef double* dblp;

int n, k, l;
dblp dp[2][MAXK];
int last_color[2][MAXK];
dblp sol;
vecp L, R, tL, tR;
pair kam[MAXN];
char dir[MAXN];

inline void add(dblp a, dblp b){
  for(int i=0; i<k; ++i)
    a[i] += b[i];
}
inline void add3(dblp values, int color, double to_add){
  values[color] += to_add;
}
void calculateDP(){
  int i = 0;
  for(; i < n && dir[i] == 'L'; ++i)
    add3(sol, kam[i].col, kam[i].pos);
  int first_right = i++, w = 0;
  for(int col_left = 0; col_left < k; ++col_left) {
    dp[w][col_left] = calloc(k, sizeof(double));
    last_color[w][col_left] = (col_left + kam[first_right].col) % k;
  }
  int prev_right = first_right;
  for(; i < n; ++i){
    if(dir[i] == 'L'){
      add(sol, dp[w][kam[i].col]);
      add3(sol, kam[i].col, (kam[i].pos - kam[prev_right].pos)/2.0);
      add3(sol, last_color[w][kam[i].col], (kam[i].pos + kam[first_right].pos) / 2.0);
    }
    else{
      w ^= 1;
      for (int col_left = 0; col_left < k; ++col_left){
        int new_col = (kam[i].col + col_left) % k;
        dp[w][col_left] = dp[w ^ 1][new_col];
        last_color[w][col_left] = last_color[w ^ 1][new_col];
        add3(dp[w][col_left], new_col, (kam[i].pos - kam[prev_right].pos) / 2.0);
      }
      prev_right = i;
    }
  }
}
void calculateDirection(){
  qsort(L.ptr, L.sz, sizeof(pair), cmpP);
  qsort(R.ptr, R.sz, sizeof(pair), cmpP);
  int a = 0, b = 0, j = 0;
  for(; a < L.sz && b < R.sz; ++j){
    if(L.ptr[a].pos < R.ptr[b].pos){
      kam[j] = L.ptr[a++];
      dir[j] = 'L';
    }
    else{
      kam[j] = R.ptr[b++];
      dir[j] = 'D';
    }
  }
  for(; a < L.sz; ++a, ++j){
    kam[j] = L.ptr[a];
    dir[j] = 'L';
  }
  for(; b < R.sz; ++b, ++j){
    kam[j] = R.ptr[b];
    dir[j] = 'D';
  }
  calculateDP();
  for(int z=0;z<R.sz;z++){pair k = R.ptr[z];
    sol[k.col] += l - k.pos;
  }
}
void init(){
  scanf("%d %d %d", &n, &k, &l);
  for(int i=0; i<n; ++i){
    int pos, col;
    char dir[10];
    scanf("%d %d %s", &pos, &col, dir);
    if (dir[0] == 'L')L.ptr=pushbackP(L.ptr, &L.sz, newPair(pos, col));
    else              R.ptr=pushbackP(R.ptr, &R.sz, newPair(pos, col));
  }
  sol = calloc(k, sizeof(double));
}
void solve(){
  calculateDirection();
  for(int i=0; i<k; ++i)
    printf("%.1lf\n", sol[i]);
}
int main(){
  init();
  solve();
  return 0;
}


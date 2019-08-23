#include<stdio.h>          //  treehugging
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int vl){
  for(int i=0; i<sz; i++)
    arr[i] = vl;
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
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

////////////////////////////////////////
int N;
vec*gr; int grsz;
int*values;
int*val;
int*comp;
vec z; 
int time;

void TwoSat(int n){
  N = n;
  grsz = 55*N;  // was 2*n
  gr = calloc(grsz, sizeof(vec));
}
int add_var(){
//  grsz+=2;
//  gr = realloc(gr, grsz*sizeof(vec));
  return N++;
}
void either(int f, int j){
  f = (f >= 0 ? 2*f : -1-2*f);
  j = (j >= 0 ? 2*j : -1-2*j);
  gr[f^1].ptr = pushback(gr[f^1].ptr, &gr[f^1].sz, j);
  gr[j^1].ptr = pushback(gr[j^1].ptr, &gr[j^1].sz, f);
}
void at_most_one(vec*li){
  if(li->sz <= 1)
    return;
  int cur = ~li->ptr[0];
  for(int i = 2; i < li->sz; ++i){
    int next = add_var();
    either(cur, ~li->ptr[i]);
    either(cur, next);
    either(~li->ptr[i], next);
    cur = ~next;
  }
  either(cur, ~li->ptr[1]);
}
int dfs(int i){
  int low = val[i] = ++time, x;
  z.ptr = pushback(z.ptr, &z.sz, i);
  for(int q=0;q<gr[i].sz;q++){int e = gr[i].ptr[q];
    if(!comp[e])
      low = fmin(low, val[e] ?: dfs(e));
  }
  ++time;
  if (low == val[i]){
    do{
      x = z.ptr[z.sz-1];
      z.sz--;
      comp[x] = time;
      if(values[x>>1] == -1)
        values[x>>1] = !(x&1);
    }while (x != i);
  }
  return val[i] = low;
}
bool solve(){
  values=calloc(N,sizeof(int)); fill(values, N, -1);
  val  = calloc(2*N, sizeof(int));
  comp = calloc(2*N, sizeof(int));
  for(int i = 0; i < (2*N); ++i)
    if(!comp[i])
      dfs(i);
  for(int i = 0; i < (N); ++i)
    if(comp[2*i] == comp[2*i+1])
      return 0;
  return 1;
}
int main(){
  int N;
  scanf("%d", &N);
  TwoSat(2*(N-1));
  vec left [N]; clr(left );
  vec right[N]; clr(right);
  for(int i = 0; i < (2*(N-1)); ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    --a, --b;
    right[a].ptr=pushback(right[a].ptr, &right[a].sz,  i);
    left [b].ptr=pushback(left [b].ptr, &left [b].sz, ~i);
  }
  for(int i = 0; i < (N-1); ++i){
   at_most_one(&right[i]);
   at_most_one(&left[i+1]);
  }
  bool r = solve();
  if (!r)
    puts("impossible");
  else{
    for(int i = 0; i < (2*(N-1)); ++i)
      putchar(values[i] ? 'R' : 'L');
    puts("");
  }
  return 0;
}

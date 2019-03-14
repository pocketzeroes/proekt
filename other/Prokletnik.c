#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;

typedef struct
{
    T *bottom;
    T *top;
    T *allocated_top;
} 
stack;
 
stack * new(void)
{
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
 
void destroy(stack *s)
{
  free(s->bottom);
  free(s);
}
 
bool empty(stack *s)
{
    return s->top < s->bottom ? true : false;
}
 
void push(stack *s, T x)
{
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
 
T pop(stack *s)
{
    return *(s->top--);
}
T top(stack *s)
{
    return *(s->top);
}

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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
//////
enum{ MAXN   = 1001000};
enum{ offset = 1 << 20};
int alive[2 * offset];
int prop_max[2 * offset];
int real_max[2 * offset];

void set_alive(int x, int lo, int hi, int k, int val);
void set_max(int x, int lo, int hi, int from, int to, int val);
int get_max(int x, int lo, int hi, int from, int to);
void propagate(int x);
void update(int x);

void clear() {
  fill(alive,    2 * offset, -1);
  fill(prop_max, 2 * offset, 0);
  fill(real_max, 2 * offset, 0);
}
void set_alive(int x, int lo, int hi, int k, int val){
  if (k < lo || k >= hi) 
    return;
  if (lo + 1 == hi) {
    alive[x] = val;
    return;
  }
  propagate(x);
  int mid = (lo + hi) / 2;
  set_alive(2 * x, lo, mid, k, val);
  set_alive(2 * x + 1, mid, hi, k, val);
  update(x);
}
void set_max(int x, int lo, int hi, int from, int to, int val){
  if (lo >= to || hi <= from) 
    return;
  if (lo >= from && hi <= to) {
    prop_max[x] = val;
    real_max[x] = max(real_max[x], alive[x] == -1 ? 0 : val - alive[x]);
    return;
  }
  propagate(x);
  int mid = (lo + hi) / 2;
  set_max(2 * x, lo, mid, from, to, val);
  set_max(2 * x + 1, mid, hi, from, to, val);
  update(x);
}
int get_max(int x, int lo, int hi, int from, int to){
  if (lo >= to || hi <= from) return 0;
  if (lo >= from && hi <= to) return real_max[x];
  propagate(x);
  int mid = (lo + hi) / 2;
  return max(get_max(2 * x, lo, mid, from, to),
      get_max(2 * x + 1, mid, hi, from, to));
}
void propagate(int x){
  prop_max[2 * x] = max(prop_max[2 * x], prop_max[x]);
  prop_max[2 * x + 1] = max(prop_max[2 * x + 1], prop_max[x]);
  real_max[2 * x] = max(real_max[2 * x],
      alive[2 * x] == -1 ? 0 : prop_max[2 * x] - alive[2 * x]);
  real_max[2 * x + 1] = max(real_max[2 * x + 1],
      alive[2 * x + 1] == -1 ? 0 : prop_max[2 * x + 1] - alive[2 * x + 1]);
  prop_max[x] = 0;
}
void update(int x){
  alive[x] = alive[2 * x] == -1 ? alive[2 * x + 1] : alive[2 * x];
  real_max[x] = max(real_max[2 * x], real_max[2 * x + 1]);
}
int n, q;
int a[MAXN];
pair b[MAXN];
vec queries[MAXN];
int sol[MAXN];
stack*maxs;
stack*mins;

void clr(){
  while(!empty(maxs))
    pop(maxs);
  while(!empty(mins))
    pop(mins);
  clear();
}
void insert(int x){
  while(!empty(maxs) && a[x] >= a[top(maxs)])
    pop(maxs);
  int from = !empty(maxs) ? top(maxs) + 1 : 0;
  while(!empty(mins) && a[x] < a[top(mins)]){
    set_alive(1, 0, offset, top(mins), -1);
    pop(mins);
  }
  push(maxs, x);
  push(mins, x);
  set_alive(1, 0, offset, x, x);
  set_max(1, 0, offset, from, x + 1, x + 1);
}
void solve(){
  clr();
  for (int i = 0; i < n; ++i) {
    insert(i);
    for(int z=0;z<queries[i].sz;z++){int j = queries[i].ptr[z];
      sol[j] = max(sol[j], get_max(1, 0, offset, b[j].first, b[j].second + 1));
    }
  }
}
int main(){
  maxs = new();
  mins = new();
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &b[i].first, &b[i].second);
    --b[i].first;
    --b[i].second;
    queries[b[i].second].ptr = pushback(queries[b[i].second].ptr, &queries[b[i].second].sz, i);
  }
  solve();
  for (int i = 0; i < n; ++i){
    a[i] = -a[i];
  }
  solve();
  for (int i = 0; i < q; ++i){
    printf("%d\n", sol[i]);
  }
  return 0;
}

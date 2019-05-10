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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
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
//////////////////////////////
typedef long long ll;

enum{ MAXN = 1000100};
const ll inf =(ll)1e18;

typedef struct{
  ll L[MAXN];
}loga;
loga L, Lcnt;

void add(loga*l, int x, ll v){
  for(++x; x < MAXN; x += x&-x)
    l->L[x] += v;
}
ll sum(loga*l, int x){
  ll r = 0;
  for(++x; x > 0; x -= x&-x)
    r += l->L[x];
  return r;
}

vec vx    [MAXN];
int x     [MAXN],
    y     [MAXN];
int h     [MAXN];
int lastX [MAXN];
ll  lt    [MAXN],
    gt    [MAXN];
int ltCnt [MAXN],
    gtCnt [MAXN];
ll  f     [MAXN];
int reconX[MAXN],
    reconY[MAXN];

int main(){
  int n, w, n_s, mjera;
  scanf("%d %d %d", &n, &n_s, &mjera);
  int last_x = -1;
  for (int i = 0; i < (n/2); ++i) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    assert(x1 < x2);
    assert(y1 == y2);
    for (int j = x1; j < x2; ++j)
      h[j] = y2;
    last_x = x2;
  }
  w = last_x;
  for (int i = 0; i < (n_s); ++i) {
    scanf("%d %d", x+i, y+i);
    vx[x[i]].ptr = pushback(vx[x[i]].ptr, &vx[x[i]].sz, y[i]);
  }
  ll total = 0, 
     total_cnt = 0;
  void addColumn(int h){
    if(mjera == 1)
      add(&L, h, 1), total++;
    else
      add(&L, h, h), total += h;
    add(&Lcnt, h, 1), total_cnt++;
  }
  memset(lastX, -1, sizeof(lastX));
  f[0] = 0;
  for(int z=0;z<vx[0].sz;z++){int y = vx[0].ptr[z];
    lastX[y] = 0;
  }
  addColumn(h[0]);
  for(int x = 1; x <= w; ++x){
    f[x] = inf;
    for(int z=0;z<vx[x].sz;z++){int y = vx[x].ptr[z];
      int lx = lastX[y];
      ll lt_now = sum(&L, y-1) - lt[y];
      ll gt_now = total - sum(&L, y) - gt[y];
      int lt_now_cnt = sum(&Lcnt, y-1) - ltCnt[y];
      int gt_now_cnt = total_cnt - sum(&Lcnt, y) - gtCnt[y];
      if (lx != -1){
        ll cost;
        if (mjera == 1) 
          cost = lt_now_cnt + gt_now_cnt;
        else
          cost = gt_now - lt_now + (ll)(y)*(lt_now_cnt - gt_now_cnt);
        if (f[lx] + cost < f[x]) {
          f[x] = f[lx] + cost;
          reconX[x] = lx, reconY[x] = y;
        }
      }
      lastX[y] = x;
      lt[y] += lt_now, ltCnt[y] += lt_now_cnt;
      gt[y] += gt_now, gtCnt[y] += gt_now_cnt;
    }
    addColumn(h[x]);
  }
  if (f[w] >= inf) 
    printf("-1\n"); 
  else {
    printf("%lld\n", f[w]);
    stack*hx=new();
    stack*hy=new();
    int x = w, ly = 0, cnt = 0;
    while (x > 0) {
      int y = reconY[x],
         nx = reconX[x];
      if (y != ly){
        push(hx, x) , push(hy, y);
        push(hx, nx), push(hy, y);
        cnt += 2;
      }
      else{
        pop(hx), push(hx, nx);
      }
      x = nx, ly = y;
    }
    printf("%d\n", cnt);
    while(!empty(hx)){
      printf("%d %d\n", top(hx), top(hy));
      pop(hx), pop(hy);
    }
  }
  return 0;
}

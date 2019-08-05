#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 1005};

int n, m, k;
int a[MAXN][MAXN];
int s[MAXN][MAXN];

typedef long long ll;

typedef struct{
  int cnt;
  int v, h;
  ll  ms;
}tva;

tva newtva(int cnt, int v, int h, ll ms){
  tva rez;
  rez.cnt = cnt;
  rez.v   = v;
  rez.h   = h;
  rez.ms  = ms;
  return rez;
}
#include<stddef.h>
#include<stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef tva T;

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

ll ans;

int main(){
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);
  for (int i = 0; i < n; ++i){
    stack*S=new();//of tva
    push(S, newtva(0, -1, 0, 0));
    for(int j = 0; j < m; ++j){
      s[i][j] = 1;
      if (i > 0 && a[i-1][j] == a[i][j])
        s[i][j] += s[i-1][j];
      int sum = 1;
      while(top(S).v == a[i][j] && top(S).h >= s[i][j]){
        sum += top(S).cnt;
        pop(S);
      }
      ll my_s = sum * (ll)s[i][j];
      if(top(S).v == a[i][j])
        my_s += top(S).ms;
      ans += my_s;
      push(S, newtva(sum, a[i][j], s[i][j], my_s));
    }
  }
  printf("%lld\n", ans);
  return 0;
}

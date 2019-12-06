#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#include<stddef.h>
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
int size(stack*s){
  return s->top-s->bottom+1;
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

enum{ MAXN = 300000};
enum{ inf = 1000000000};
int dp   [MAXN+1];
int how  [MAXN+1];
int max_x[100001];
int max_y[100001];
int order[MAXN  ];
int n;
typedef struct{
  int x, y, m;
}pt;
pt p[MAXN+1];

int cmp(const void*pa, const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  if(p[*a].x != p[*b].x)
    return(p[*a].x < p[*b].x)?-1:1;
  return(p[*a].y < p[*b].y)?-1:1;
}
int main(){
  memset(max_x, 0, sizeof max_x);
  memset(max_y, 0, sizeof max_y);
  int n, k;
  scanf("%d %d", &n, &k);
  for(int i=1; i<=n; ++i){
    scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].m);
    order[i-1] = i;
  }
  qsort(order, n, sizeof(int), cmp);
  dp[0] = -inf;
  for(int i=0; i<n; ++i){
    int a = order[i];
    dp[a] = -inf;
    if(a == 1)
      dp[a] = p[a].m;
#define xx max_x[p[a].x]
#define yy max_y[p[a].y]
    if(dp[xx] >= k && dp[a] < dp[xx] + p[a].m - k){
      dp [a] = dp[xx] + p[a].m - k;
      how[a] = xx;
    }
    if(dp[yy] >= k && dp[a] < dp[yy] + p[a].m - k){
      dp [a] = dp[yy] + p[a].m - k;
      how[a] = yy;
    }
    if(dp[a] > dp[xx])
      xx = a;
    if(dp[a] > dp[yy])
      yy = a;
  }
  stack*S = new();
  for(int a=n; a!=1; a = how[a])
    push(S, a);
  push(S, 1);
  printf("%d\n", dp[n]);
  printf("%d\n", size(S));
  while(!empty(S)){
    printf("%d %d\n", p[top(S)].x, p[top(S)].y);
    pop(S);
  }
  return 0;
}

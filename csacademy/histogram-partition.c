#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stddef.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;
typedef struct{
  T *bottom;
  T *top;
  T *allocated_top;
} stack;
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
  if (s->top == s->allocated_top){
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


ll m, n, kei;
ll aa[100010];
int main(){
    scanf("%lld", &n);
    for(int i=0;i<n;i++)
        scanf("%lld", &aa[i]);
    stack*stk=new();
    int count = -1;
    push(stk, 0);
    for(ll i = 0ll;(i)<(n);++(i)) {
        while(top(stk) > aa[i]) {
            ++count;
            pop(stk);
        }
        if(top(stk) < aa[i])
            push(stk,aa[i]);
    }
    while (!empty(stk)) {
        ++count;
        pop(stk);
    }
    printf("%d\n", count);
    return 0;
}

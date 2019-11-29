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
typedef struct{
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

int main(){
  int N;
  scanf("%d", &N);
  stack*original =new();
  stack*auxiliary=new();
  for(int i=0; i<2*N; i++){
    int a;
    scanf("%d", &a);
    push(original, a);
  }
  int moves = 0;
  while(!empty(original)){
    push(auxiliary, top(original));
    pop(original);
    moves++;
    while(!empty(original) && !empty(auxiliary) && top(original) == top(auxiliary)){
      pop(original);
      pop(auxiliary);
      moves++;
    }
  }
  if(!empty(auxiliary))
    puts("impossible");
  else
    printf("%d\n", moves);
  return 0;
}
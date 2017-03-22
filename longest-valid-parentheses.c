#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

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
int longestValidParentheses(char* sChars) {
    stack*stak = new();
    int longest = 0;
    for( int i=0;sChars[i];i++){
        char chr=sChars[i];
        if( chr == '(' || empty(stak) || sChars[top(stak)] == ')' ){
            push(stak, i);
        }
        else {
            int _ = pop(stak);
            if( empty(stak) ){
                longest = MAX(longest, i + 1);
            } 
            else {
                longest = MAX(longest, i - top(stak));
            }
        }
    }
    return longest;
}
#if 0 
int main(){
    int rv = longestValidParentheses( ")()())");
    printf("result is %d\n", rv);
}
#endif

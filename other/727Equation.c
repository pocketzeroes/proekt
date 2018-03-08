#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stddef.h>

/*///////////////////*/
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef char T;

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
/*///////////////////*/


int Priority(char c){
    switch (c){
        case '(': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
    }
}
int main(){
    int kase, i;
    char s[10], c;
    scanf("%d", &kase);
    gets(s);
    gets(s);
    while (kase--) {
        stack*st = new();
        while(gets(s) && strlen(s)){
            c = s[0];
            if (c==' ')
                break;
            if (c=='(')
                push(st, c);
            else if (c=='+' || c=='-' || c=='*' || c=='/'){
                while (!empty(st) && Priority(c) <= Priority(top(st))){
                    printf("%c", top(st));
                    pop(st);
                }
                push(st, c);
            }
            else if (c==')'){
                while(top(st)!='('){
                    printf("%c", top(st));
                    pop(st);
                }
                pop(st);
            }
            else 
                printf("%c", c);
        }
        while(!empty(st)){
            printf("%c", top(st));
            pop(st);
        }
        puts("");
        if (kase) 
            puts("");
    }
}

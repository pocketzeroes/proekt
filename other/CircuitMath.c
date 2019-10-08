#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char line[100000];
char*getln(){
  gets(line);
  return strdup(line);
}

#include <stddef.h>
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
T pop(stack *s){
    return *(s->top--);
}
T top(stack*s){
    return*(s->top);
}



enum{ N = 27};
int n;
int c[N];
char*str;
int pt;

int main(){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        getchar();
        char ch=getchar();
        c[i] = (ch == 'T');
    }
    getchar();
    str = getln();
    stack*S = new();
    int slen=strlen(str);
    for(int i=0; i<slen; i+=2){
        if(str[i] >= 'A' && str[i] <= 'Z')
            push(S, c[str[i] - 'A']);
        else if(str[i] == '-')
            *(S->top) = !top(S);
        else if(str[i] == '+'){
            int a = top(S); pop(S);
            *(S->top) |= a;
        }
        else{
            int a = top(S); pop(S);
            *(S->top) &= a;
        }
    }
    printf("%c\n",(top(S) ? 'T' : 'F'));
    return 0;
}

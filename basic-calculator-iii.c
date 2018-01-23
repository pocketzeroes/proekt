#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 

#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef double T;

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
////////////////////////////////

double calculate(char*s){
    int ssize = strlen(s);
    if(ssize == 0) return 0;
    stack*nums = new();
    char sign = '+';
    double number = 0;
    for (int i = 0; i <= ssize; ++i){
        if(i < ssize && s[i] == ' ')
            continue;
        else if (i < ssize && isdigit(s[i]))
            number = number * 10 + s[i] - '0';
        else if (i < ssize && s[i] == '(') {
            int start = i + 1, count = 0;
            while (i < ssize){
                if (s[i] == '(')
                    ++count;
                else if (s[i] == ')')
                    --count;
                if (count == 0)
                    break;
                ++i;
            }
            number = calculate(substr(s, start, i - start));
        }
        else{
            if (sign == '+')
                push(nums, number);
            else if (sign == '-')
                push(nums, -number);
            else if (sign == '*'){
                double temp = top(nums); pop(nums);
                push(nums, temp*number);
            }
            else if (sign == '/') {
                double temp = top(nums); pop(nums);
                push(nums, floor(temp / number));
            }
            if(i < ssize)
                sign = s[i];
            number = 0;
        }
    }
    double res = 0;
    while(!empty(nums)){
        res += top(nums); pop(nums);
    }
    return res;
}

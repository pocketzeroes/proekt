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


int largestRectangleArea(int* heights, int heightsSize) {
    stack*increasing_heights=new();
    int max_area = 0;
    for (int i = 0; i <= heightsSize;){
        if ( empty(increasing_heights) || (i < heightsSize && heights[i] > heights[ top(increasing_heights) ])) {
            push(increasing_heights,i);
            ++i;
        }
        else {
            int h = heights[ top(increasing_heights) ];
            pop(increasing_heights);
            int left = empty(increasing_heights) ? -1 : top(increasing_heights);
            max_area = MAX(max_area, h * (i - left - 1));
        }
    }
    return max_area;
}


































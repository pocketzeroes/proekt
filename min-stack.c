#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int64_t T;
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

////----
typedef struct msS {
    int a;
} MinStack;
MinStack*ptr;
stack*myStack;
int iStackMin;

MinStack* minStackCreate(int maxSize) {
    myStack=new();
    iStackMin=0;
    ptr=NULL;
    return ptr;
}
void minStackPush(MinStack* obj, int number) {
    if (empty(myStack)) {
        push(myStack,0);
        iStackMin = number;
    } 
    else {
        push(myStack, (int64_t) number - iStackMin);
        if (number < iStackMin)
            iStackMin = number;
    }
}
void minStackPop(MinStack* obj) {
    int diff = top(myStack);
    pop(myStack);
    if (diff < 0) 
        iStackMin -= diff;
}
int minStackTop(MinStack* obj) {
    if (top(myStack) > 0) 
        return iStackMin + top(myStack);
    else 
        return iStackMin;
}
int minStackGetMin(MinStack* obj) {
    return iStackMin;
}
void minStackFree(MinStack* obj) {
    myStack=NULL;
    iStackMin=0;
}






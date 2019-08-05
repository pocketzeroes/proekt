#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
#include<stddef.h>
#include<stdbool.h>
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MAXN = 5010};

typedef struct{
    bool   vertical;
    double a, b;
    int    x1, y1, x2, y2;
}line;
line newline(int x1, int y1, int x2, int y2){
    line rez;
    rez.x1 = x1;
    rez.x2 = x2;
    rez.y1 = y1;
    rez.y2 = y2;
    rez.vertical = (x1 == x2);
    if(!rez.vertical)
        rez.a = (double)(y1 - y2)/(x1 - x2);
    else
        rez.a = 0;
    rez.b = y1 - rez.a * x1;
    return rez;
}
double get_y(line l, double x){
    return l.a * x + l.b;
}
const double eps = 1e-10;
bool bio[MAXN];
int n;
line l[MAXN];
vec v[MAXN];
stack*sol;

inline bool lt(const double a, const double b){
    return b - a > eps;
}
inline bool connected(int i, int j){
    double x1 = fmax(l[i].x1, l[j].x1), 
           x2 = fmin(l[i].x2, l[j].x2);
    if(i == j || lt(x2, x1))
        return false;
    return lt(get_y(l[i], x1), get_y(l[j], x1));
}
void dfs(int stick) {
    bio[stick] = true;
    for(int i=0; i<v[stick].sz; ++i)
        if(!bio[v[stick].ptr[i]])
            dfs(v[stick].ptr[i]);
    push(sol, stick+1);
}
int main(){
    sol=new();
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 > x2){
            swap(x1, x2);
            swap(y1, y2);
        }
        l[i] = newline(x1, y1, x2, y2);
    }
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            if(connected(i, j))
                v[i].ptr = pushback(v[i].ptr, &v[i].sz, j);
    for(int i=0; i<n; ++i)
        if (!bio[i])
            dfs(i);
    while(!empty(sol)){
        printf("%d ", top(sol));
        pop(sol);
    }
    puts("");
    return 0;
}

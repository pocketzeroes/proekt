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

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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

enum{ MAX = 100000};
int n;
int a   [3][MAX];
int erased [MAX];
vec columns[MAX];
int freq[MAX][3];
stack*jobs;

int main(){
  jobs=new();
  scanf("%d", &n);
  for(int r=0; r<3; ++r)
    for(int c=0; c<n; ++c){
      scanf( "%d", &a[r][c]);
      --a[r][c];
      pb(columns[a[r][c]], c);
      ++freq[a[r][c]][r];
    }
  for(int i=0; i<n; ++i)
    if(freq[i][1] == 0 || freq[i][2] == 0)
      push(jobs, i);
  int ret = 0;
  while(!empty(jobs)){
    int number = top(jobs); pop(jobs);
    for(int z=0;z<columns[number].sz;z++){int it = columns[number].ptr[z];
      if(erased[it])
        continue;
      erased[it] = 1;
      ++ret;
      if(--freq[a[0][it]][0] == 0 ) push(jobs, a[0][it]);
      if(--freq[a[1][it]][1] == 0 ) push(jobs, a[1][it]);
      if(--freq[a[2][it]][2] == 0 ) push(jobs, a[2][it]);
    }
  }
  printf( "%d\n", ret );
  return 0;
}

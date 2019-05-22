#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#include <stddef.h>
#include <stdbool.h>
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
//////////////////////
enum{ MAX   = 10000};
enum{ STAZA = 0,
      DJIR  = 1};

int n, m;
int n_prstena;
int traversal_time;

vec adj     [MAX];
vec prsten  [MAX];
vec prsteni [MAX];
vec mostovi [MAX];
int discover[MAX];
int lowlink [MAX];
stack*S;
int memo    [MAX][2];

void dfs(int i, int dad){
   discover[i] = traversal_time++;
   lowlink [i] = discover[i];
   push(S, i);
   for(int z=0;z<adj[i].sz;z++){int it=adj[i].ptr[z];
      if(it == dad)
         continue;
      if( discover[it] != -1 )
         lowlink[i] = min(lowlink[i], discover[it]);
      else{
         dfs(it, i );
         if( lowlink[it] < discover[i] )
             lowlink[i] = min(lowlink[i], lowlink[it]);
         else if( lowlink[it] == discover[i] ){
            prsteni[i].ptr = pushback(prsteni[i].ptr, &prsteni[i].sz, n_prstena );
            do {
               prsten[n_prstena].ptr = pushback(prsten[n_prstena].ptr, &prsten[n_prstena].sz, top(S));
               pop(S);
            }
            while( prsten[n_prstena].ptr[prsten[n_prstena].sz-1] != it );
            ++n_prstena;
         }
         else{
            mostovi[i].ptr = pushback(mostovi[i].ptr, &mostovi[i].sz, top(S));
            pop(S);
         }
      }
   }
}
int rec(int X, int sto_racunam){
#define ret memo[X][sto_racunam]
   if( ret >= 0 )
      return ret;
   ret = 0;
   int profit = 0;
   for( int i = 0; i < mostovi[X].sz; ++i )
      profit = max(profit, 1+rec(mostovi[X].ptr[i], STAZA));
   for( int i = 0; i < prsteni[X].sz; ++i ) {
      vec*P = &prsten[prsteni[X].ptr[i]];
      int best = 0;
      int smjer1 = 1, smjer2 = 1;
      int ciklus = P->sz + 1;
      for( int j = 0; j < P->sz; ++j ) {
         best    = max(best, smjer1+rec( P->ptr[j], STAZA));
         smjer1 += 1 + rec( P->ptr[j], DJIR );
         best    = max(best, smjer2 + rec( P->ptr[P->sz-j-1], STAZA ));
         smjer2 += 1 + rec( P->ptr[P->sz-j-1], DJIR );
         ciklus += rec( P->ptr[j], DJIR );
      }
      ret += ciklus;
      profit = max(profit, best-ciklus);
   }
   if( sto_racunam == STAZA )
      ret += profit;
   return ret;
   #undef ret
}
int main(){
   S=new();
   scanf("%d %d", &n, &m);
   for( int i = 0; i < m; ++i){
      int a, b;
      scanf("%d %d", &a, &b );
      --a, --b;
      adj[a].ptr=pushback(adj[a].ptr, &adj[a].sz, b);
      adj[b].ptr=pushback(adj[b].ptr, &adj[b].sz, a);
   }
   memset( discover, -1, sizeof discover );
   dfs( 0, -1 );
   memset( memo, -1, sizeof memo );
   printf( "%d\n", rec( 0, 0 ) );
   return 0;
}

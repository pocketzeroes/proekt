#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


////////////////////////////////////////////////////
enum{ GRID  = 1000000};
enum{ MAX_N =  10000 };
int N;
pair*points;
vecp conflicts;
vec  out [2*MAX_N];
vec  in  [2*MAX_N];
int  tree[2*MAX_N];

void dfs(vec*adj,  vec*order, vec*finished){
    for(int j=0; j < 2*N; j++)
        tree[j] = -1;
    int count=-1;
    for(int j=2*N-1; j >= 0; j--){
        int s = order->ptr[j];
        if(tree[s] == -1){
            count++;
            tree[s] = count;
            stack*S = new();
            push(S, s);
            while(!empty(S)){
                int u = top(S);
                bool foundMore = false;
                for(int z=0;z<adj[u].sz;z++){int v = adj[u].ptr[z];
                    if(tree[v] == -1){
                        foundMore = true;
                        tree[v] = count;
                        push(S, v);
                    }
                }
                if(!foundMore){
                    pop(S);
                    finished->ptr = pushback(finished->ptr, &finished->sz, u);
                }
            }
        }
    }
}
bool feasible(int P){
    for (int j=0; j < 2*N; j++) {
        out[j].sz=0;
        in [j].sz=0;
    }
    for(int z=0;z<conflicts.sz;z++){pair pir = conflicts.ptr[z];
        int u = pir.first;
        int v = pir.second;
        pair pu = points[u%N];
        pair pv = points[v%N];
        if (abs(pu.first - pv.first ) <= 2*P&&
            abs(pu.second- pv.second) <= 2*P){
            int notV = (v+N)%(2*N);
            int notU = (u+N)%(2*N);
            pb(out[u], notV);
            pb(in[notV], u);
            pb(out[v], notU);
            pb(in[notU], v);
        }
    }
    vec initial=newVec();
    for(int j=0; j < 2*N; j++)
        pb(initial, j);
    vec finishA = newVec();
    vec finishB = newVec();
    dfs(out, &initial, &finishA);
    dfs(in , &finishA, &finishB);
    for(int j=0; j < N; j++)
        if(tree[j] == tree[N+j])
            return false;
    return true;
}
int main(){
    scanf("%d", &N);
    points = calloc(N, sizeof(pair));
    for(int j=0; j<N; j++){
        int x, y;
        scanf("%d %d", &x, &y);
        points[j] = (pair){x, y};
    }
    for(int j=0; j < N; j++){
      for(int k=1+j; k < N; k++){
        if(points[j].first == points[k].first)
            pbp(conflicts, newpair(j+N, k+N));
        if(points[j].second == points[k].second)
            pbp(conflicts, newpair(j, k));
      }
    }
    int P=1;
    while(P < (1+GRID) && feasible(P))
        P *= 2;
    if(P >= 1+GRID)
        puts("UNLIMITED");
    else{
        int low  = P/2;
        int high = P;
        while(low != high-1){
            int mid = (low+high)/2;
            if(feasible(mid))
                low = mid;
            else
                high = mid;
        }
        printf("%d\n", low);
    }
    return 0;
}

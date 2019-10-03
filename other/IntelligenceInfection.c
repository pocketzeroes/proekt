#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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
////////////////////////////

vec*adj_list;
bool*scc_dirty;
int scc_index;
vec*scc_adj_list;
vec*scc_adj_list_from;
int*scc_for_node;
vec scc_size;
int*Index;
int*lowlink;
int current_index = 1;
stack*s;
bool*on_stack;
int S, E, C;
ll send_count;

void dfs(int u){
    if(scc_dirty[u])
        return;
    for(int z=0;z<scc_adj_list[u].sz;z++){int idx = scc_adj_list[u].ptr[z];
        dfs(idx);
        if(scc_dirty[idx]){
            scc_dirty[u] = true;
            break;
        }
    }
}
void strongly_connected(int v){
    Index[v] = current_index;
    lowlink[v] = current_index;
    current_index++;
    push(s, v);
    on_stack[v] = true;
    for(int i = 0; i < adj_list[v].sz; i++){
        int w = adj_list[v].ptr[i];
        if(!Index[w]){
            strongly_connected(w);
            lowlink[v] = fmin(lowlink[v], lowlink[w]);
        } 
        else if(on_stack[w])
            lowlink[v] = fmin(lowlink[v], Index[w]);
    }
    if(lowlink[v] == Index[v]){
        int w;
        vec items_in_scc = newVec();
        do {
            w = top(s); pop(s);
            on_stack[w] = false;
            pb(items_in_scc, w);
            scc_for_node[w] = scc_index;
        }
        while(w != v);
        pb(scc_size, items_in_scc.sz);
        scc_index++;
    }
}
void create_scc_graph(){
    for(int u=0; u<S; u++){
        int already_added[S]; clr(already_added);
        for(int j = 0; j < adj_list[u].sz; j++){
            int v = adj_list[u].ptr[j];
            int u_scc = scc_for_node[u];
            int v_scc = scc_for_node[v];
            if(u_scc != v_scc && !already_added[v_scc] && !scc_dirty[u_scc] && !scc_dirty[v_scc]){
                pb(scc_adj_list[u_scc], v_scc);
                pb(scc_adj_list_from[v_scc], u_scc);
                already_added[v_scc] = true;
            }
        }
    }
}
int main(){
    s=new();
    scanf("%d %d %d", &S, &E, &C);
    adj_list=calloc(S, sizeof(vec));
    scc_for_node = calloc(S, sizeof(int)); fill(scc_for_node, S, -1);
    Index = calloc(S, sizeof(int));
    lowlink=calloc(S, sizeof(int));
    on_stack = calloc(S, sizeof(bool));
    for(int i = 0; i < C; i++){
        int from, to;
        scanf("%d %d", &from, &to);
        pb(adj_list[from], to);
    }
    vec enemies = newVec();
    for(int i=0; i<E; i++){
        int e;
        scanf("%d", &e);
        pb(enemies, e);
    }
    for(int i = 0; i < S; i++)
        if(!Index[i])
            strongly_connected(i);
    scc_adj_list      = calloc(scc_index, sizeof(vec));
    scc_adj_list_from = calloc(scc_index, sizeof(vec));
    scc_dirty = calloc(scc_index, sizeof(bool));
    create_scc_graph();
    for(int z=0;z<enemies.sz;z++){int e = enemies.ptr[z];
        int scc = scc_for_node[e];
        scc_dirty[scc] = true;
    }
    for(int i = 0; i < scc_index; i++)
        dfs(i);
    for(int i = 0; i < scc_index; i++){
        if(scc_dirty[i])
            send_count += scc_size.ptr[i];
    }
    send_count -= E;
    for(int v = 0; v < scc_index; v++){
        if(scc_dirty[v])
            continue;
        bool has_incoming = false;
        for(int z=0;z<scc_adj_list_from[v].sz;z++){int u = scc_adj_list_from[v].ptr[z];
            if(!scc_dirty[u])
                has_incoming = true;
        }
        if(!has_incoming)
            send_count++;
    }
    printf("%lld\n", send_count);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

#include <stddef.h>
#include <stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef ll T;

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

ll dr[4] = {1, 0, -1, 0};
ll dc[4] = {0, 1,  0,-1};

typedef struct{
  ll to, id, from;
}Edge;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

//struct Graph{
ll v_count, e_count;
vece*adj;
vece edges;
void newGraph(ll n){
  v_count = n;
  adj=calloc(n, sizeof(vece));
  e_count = 0;
}
void add_undirected(ll a, ll b){
  Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
  adj[a].ptr = pushbackE(adj[a].ptr, &adj[a].sz, ab);
  Edge ba; ba.id = e_count; ba.from = b; ba.to = a;
  adj[b].ptr = pushbackE(adj[b].ptr, &adj[b].sz, ba);
  e_count++;
  edges.ptr = pushbackE(edges.ptr, &edges.sz, ab);
}
void add_directed(ll a, ll b){
  Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
  adj[a].ptr = pushbackE(adj[a].ptr, &adj[a].sz, ab);
  e_count++;
  edges.ptr = pushbackE(edges.ptr, &edges.sz, ab);
}
//};
//struct SCC{
  ll*age;
  ll*lowlink;
  ll*component;
  ll time;
  ll count;
  stack*path;
  
  void dfs(ll a){
    time++;
    age[a] = lowlink[a] = time;
    push(path, a);
    for(int z=0;z<adj[a].sz;z++){Edge e = adj[a].ptr[z];
      ll b = e.to;
      if(!age[b])
        dfs(b);
      lowlink[a] = min(lowlink[a], lowlink[b]);
    }
    if (lowlink[a] == age[a]){
      while (1){
        ll t = top(path); pop(path);
        lowlink  [t] = LLONG_MAX;
        component[t] = count;
        if(t == a)
          break;
      }
      count++;
    }
  }
  void newscc(){
    path=new();
    age       = calloc(v_count, sizeof(ll));
    lowlink   = calloc(v_count, sizeof(ll));
    component = calloc(v_count, sizeof(ll));
    time  = 0;
    count = 0;
    for(ll i = 0; i < v_count; i++)
      if(! age[i])
        dfs(i);
  }


//};
//struct SAT2{
  ll size;
  void newsat(ll n){
    newGraph(n*2);
    size=n;
  }
  ll neg(ll x){
    return (x + size) % (2 * size);
  }
  void add_or(ll x, ll y){
    add_directed(neg(x), y);
    add_directed(neg(y), x);
  }
  void add_true(ll x){
    add_directed(neg(x), x);
  }
  void add_xor(ll x, ll y){
    add_or(x, y);
    add_or(neg(x), neg(y));
  }
  bool is_solvable() {
    newscc();
    for(ll i=0; i<size; i++)
      if(component[i] == component[neg(i)])
        return false;
    return true;
  }
//};
bool in_bounds(ll r, ll c, ll rows, ll cols){
  return 0 <= r && r < rows && 0 <= c && c < cols;
}
int main(){
  ll rows, cols;
  scanf("%lld %lld", &rows, &cols);
  char*grid[rows];
  for (ll i = 0; i < (ll)(rows); i++)
    grid[i]=getstr();
  ll term_id[4][rows][cols];// -1)));
  ll black_count = 0,
     white_count = 0;
  ll id = 0;
  for (ll i = 0; i < (ll)(rows); i++){
    for (ll j = 0; j < (ll)(cols); j++){
      term_id[0][i][j] = term_id[1][i][j] = term_id[2][i][j] = term_id[3][i][j] = -1;
      if (grid[i][j] == 'B') {
        black_count++;
        for (ll d = 0; d < (ll)(4); d++)
          term_id[d][i][j] = id++;
      }
      if (grid[i][j] == 'W')
        white_count++;
    }
  }
  newsat(id);
  bool ok = (black_count * 2 == white_count);
  if (ok){
    for (ll i = 0; i < (ll)(rows); i++){
      for (ll j = 0; j < (ll)(cols); j++){
        if (grid[i][j] == 'W') {
          vecl bb = newVecL();
          for (ll d = 0; d < (ll)(4); d++) {
            ll ni = i + dr[d],
               nj = j + dc[d];
            if(!in_bounds(ni, nj, rows, cols) || grid[ni][nj] != 'B')
              continue;
            bb.ptr = pushbackL(bb.ptr, &bb.sz, term_id[(d + 2) % 4][ni][nj]);
          }
          ok = ok && ! bb.sz==0;
          if(!ok)
            break;
          for (ll x = 0; x < (ll)(bb.sz); x++)
            for (ll y = (ll)(x + 1); y < (ll)(bb.sz); y++)
              add_or(neg(bb.ptr[x]), neg(bb.ptr[y]));
        }
        if (grid[i][j] == 'B'){
          for (ll d = 0; d < (ll)(4); d++) {
            ll r = i + dr[d],
               c = j + dc[d];
            if(!in_bounds(r, c, rows, cols) || grid[r][c] != 'W')
              add_true(term_id[(d + 2) % 4][i][j]);
          }
          add_xor(term_id[0][i][j], term_id[2][i][j]);
          add_xor(term_id[1][i][j], term_id[3][i][j]);
        }
      }
    }
  }
  ok = (ok) && (is_solvable());
  puts(ok?"YES":"NO");
  return 0;
}

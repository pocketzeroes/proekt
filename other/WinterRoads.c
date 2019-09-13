#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


#if 1// de que
enum{ START_SIZE = 4};
struct dynarray {
    void ** buffer;
    unsigned int size;
    unsigned int count;
};
typedef struct dynarray dynarray;
typedef void (*dynarray_forfn)(void *);
dynarray * dynarray_create(unsigned int startsize);
void dynarray_empty(dynarray * array);
void dynarray_delete(dynarray * array);
void dynarray_add_tail(dynarray * array, void * data);
void dynarray_add_head(dynarray * array, void * data);
void * dynarray_remove_tail(dynarray * array);
void * dynarray_remove_head(dynarray * array);
void dynarray_insert(dynarray *array, unsigned int pos, void *data);
void * dynarray_remove(dynarray *array, unsigned int pos);
void * dynarray_get(const dynarray * array, unsigned int pos);
void * dynarray_set(dynarray * array, unsigned int pos, void * data);
void dynarray_for_each(const dynarray * array, dynarray_forfn fun);
unsigned int dynarray_get_count(const dynarray * array);
void dynarray_set_size(dynarray * array, unsigned int size);
dynarray * dynarray_create(unsigned int size){
    dynarray * array = malloc(sizeof(dynarray));
    if (array != NULL) {
        if (size) {
            array->buffer = malloc(size * sizeof(void*));
            if (array->buffer) {
                array->size = size;
            }
            else {
                free(array);
                array = NULL;
            }
        }
        else {
            array->buffer = NULL;
            array->size = 0;
        }
        array->count = 0;
    }
    return array;
}
void dynarray_empty(dynarray * array){
    array->count = 0;
}
void dynarray_delete(dynarray * array){
    if (array) {
        free(array->buffer);
        free(array);
    }
}
void dynarray_add_tail(dynarray * array, void * data){
    if (array->count == array->size) {
        if (array->buffer != NULL) {
            void **buffer = realloc(array->buffer, array->size * 2 * sizeof(void*));
            array->buffer = buffer;
            array->size *= 2;
        }
        else {
            array->buffer = malloc(START_SIZE * sizeof(void*));
            array->size = START_SIZE;
        }
    }
    if (array->buffer != NULL) {
        array->buffer[array->count] = data;
        array->count++;
    }
}
void dynarray_add_head(dynarray * array, void * data){
    if (array->count == array->size) {
        if (array->buffer != NULL) {
            void **temp = malloc(array->size * 2 * sizeof(void*));
            if (temp) {
                memcpy(temp + 1, array->buffer, array->count * sizeof(void*));
                free(array->buffer);
                array->buffer = temp;
                array->size *= 2;
            }
        }
        else {
            array->buffer = malloc(START_SIZE * sizeof(void*));
            if (array->buffer) {
                array->size = START_SIZE;
            }
        }
    }
    else {
        memmove(array->buffer + 1, array->buffer, array->count * sizeof(void*));
    }
    if (array->buffer != NULL) {
        array->buffer[0] = data;
        array->count++;
    }
}
void * dynarray_remove_tail(dynarray * array){
    void * data = NULL;
    if (array->count > 0) {
        data = array->buffer[array->count - 1];
        array->count--;
    }
    return data;
}
void * dynarray_remove_head(dynarray * array){
    void * data = NULL;
    if (array->count > 0) {
        data = array->buffer[0];
        memmove(array->buffer, array->buffer + 1, (array->count - 1) * sizeof(void*));
        array->count--;
    }
    return data;
}
void dynarray_insert(dynarray *array, unsigned int pos, void *data){
    if (pos == 0) {
        dynarray_add_head(array, data);
    }
    else if (pos == array->count) {
        dynarray_add_tail(array, data);
    }
    else if (pos < array->count) {
        unsigned int i;
        if (array->count == array->size) {
            void **temp = malloc(array->size * 2 * sizeof(void*));
            if (temp) {
                memcpy(temp, array->buffer, pos * sizeof(void*));
                memcpy(temp + pos + 1, array->buffer + pos, (array->count - pos) * sizeof(void*));
                free(array->buffer);
                array->buffer = temp;
                array->size *= 2;
            }
        }
        else {
            memmove(array->buffer + pos + 1, array->buffer + pos, (array->count - pos) * sizeof(void*));
        }
        array->buffer[pos] = data;
        array->count++;
    }
}
void * dynarray_remove(dynarray *array, unsigned int pos){
    void *data;
    if (array->count < pos + 1) {
        data = NULL;
    }
    else if (pos == 0) {
        data = dynarray_remove_head(array);
    }
    else if (pos == array->count - 1) {
        data = dynarray_remove_tail(array);
    }
    else {
        unsigned int i;
        data = array->buffer[pos];
        memmove(array->buffer + pos, array->buffer + pos + 1, (array->count - pos - 1) * sizeof(void*));
        array->count--;
    }
    return data;
}
void * dynarray_get(const dynarray * array, unsigned int pos){
    void * data = NULL;
    if (pos < array->count) {
        data = array->buffer[pos];
    }
    return data;
}
void * dynarray_set(dynarray * array, unsigned int pos, void * data){
    void * temp = NULL;
    if (pos == array->count) {
        dynarray_add_tail(array, data);
    }
    else if (pos < array->count) {
        temp = array->buffer[pos];
        array->buffer[pos] = data;
    }
    return temp;
}
void dynarray_set_size(dynarray * array, unsigned int size){
    array->buffer = realloc(array->buffer, size);
    if (array->buffer) {
        array->size = size;
        if (array->size < array->count) {
            array->count = array->size;
        }
    }
    else {
        array->size = 0;
        array->count = 0;
    }
}
void dynarray_for_each(const dynarray * array, dynarray_forfn fun){
    unsigned int i;
    for (i = 0; i < array->count; i++) {
        fun(array->buffer[i]);
    }
}
unsigned int dynarray_get_count(const dynarray * array){
    return array->count;
}
/////////////////
typedef struct {
    dynarray *arrays;
    unsigned int arraysize;
    unsigned int front;
    unsigned int back;
    unsigned int firstempty;
    unsigned int lastempty;
    unsigned int count;
} deque;
typedef void (*deque_forfn)(void*);
deque * newDeque(void);
void delDeque(deque * queue);
void push_front(deque * queue, void * data);
void push_back(deque * queue, void * data);
void * pop_front(deque * queue);
void * pop_back(deque * queue);
void * getpoz(const deque *queue, unsigned int index);
void * deque_set_at(deque *queue, unsigned int index, void * data);
void * front(const deque * queue);
void * back(const deque * queue);
void deque_for_each(const deque * queue, deque_forfn fun);

deque * newDeque(void){
    deque *queue = malloc(sizeof(deque));
    if (queue) {
        queue->arrays = dynarray_create(0);
        queue->arraysize = 4;
        queue->firstempty = 1;
        queue->lastempty = 1;
        queue->count = 0;
        dynarray_add_head(queue->arrays, malloc(queue->arraysize * sizeof(void*)));
    }
    return queue;
}
void delDeque(deque * queue){
    if (queue) {
        dynarray_for_each(queue->arrays, free);
        dynarray_delete(queue->arrays);
        free(queue);
    }
}
void push_front(deque * queue, void * data){
    unsigned int index;
    if (queue->count == 0) {
        index = queue->arraysize / 2;
    }
    else if (queue->firstempty) {
        index = queue->arraysize - 1;
    }
    else if (queue->front == 0) {
        dynarray_add_head(queue->arrays, malloc(queue->arraysize * sizeof(void*)));
        index = queue->arraysize - 1;
    }
    else {
        index = queue->front - 1;
    }
    ((void**)dynarray_get(queue->arrays, 0))[index] = data;
    queue->front = index;
    queue->firstempty = 0;
    if (queue->arrays->count == 1) {
        queue->lastempty = 0;
    }
    queue->count++;
    if (queue->count == 1) {
        queue->back = queue->front;
    }
}
void push_back(deque * queue, void * data){
    unsigned int index;
    if (queue->count == 0) {
        index = queue->arraysize / 2;
    }
    else if (queue->lastempty) {
        index = 0;
    }
    else if (queue->back == queue->arraysize - 1) {
        dynarray_add_tail(queue->arrays, malloc(queue->arraysize * sizeof(void*)));
        index = 0;
    }
    else {
        index = queue->back + 1;
    }
    ((void**)dynarray_get(queue->arrays, queue->arrays->count - 1))[index] = data;
    queue->back = index;
    queue->lastempty = 0;
    if (queue->arrays->count == 1) {
        queue->firstempty = 0;
    }
    queue->count++;
    if (queue->count == 1) {
        queue->front = queue->back;
    }
}
void * pop_front(deque * queue){
    void *data = NULL;
    if (queue->count) {
        if (queue->firstempty) {
            free(dynarray_remove_head(queue->arrays));
            queue->firstempty = 0;
        }
        data = ((void**)dynarray_get(queue->arrays, 0))[queue->front];
        queue->front++;
        if (queue->front == queue->arraysize) {
            queue->firstempty = 1;
            queue->front = 0;
        }
        queue->count--;
        if (queue->count == 1) {
            queue->back = queue->front;
        }
        else if (queue->count == 0 && queue->arrays->count == 2) {
            free(dynarray_remove_head(queue->arrays));
        }
    }
    return data;
}
void * pop_back(deque * queue){
    void *data = NULL;
    if (queue->count) {
        if (queue->lastempty) {
            free(dynarray_remove_tail(queue->arrays));
            queue->lastempty = 0;
        }
        data = ((void**)dynarray_get(queue->arrays, queue->arrays->count - 1))[queue->back];
        if (queue->back == 0) {
            queue->lastempty = 1;
            queue->back = queue->arraysize - 1;
        }
        else {
            queue->back--;
        }
        queue->count--;
        if (queue->count == 1) {
            queue->front = queue->back;
        }
        else if (queue->count == 0 && queue->arrays->count == 2) {
            free(dynarray_remove_tail(queue->arrays));
        }
    }
    return data;
}

void*getpoz(const deque*queue, unsigned int index){
    void * data = NULL;
    if (index < queue->count) {
        const unsigned int pos = index + queue->front;
        data = ((void**)dynarray_get(queue->arrays, pos / queue->arraysize + queue->firstempty))[pos % queue->arraysize];
    }
    return data;
}
void * deque_set_at(deque *queue, unsigned int index, void * data){
    void * result = NULL;
    if (index == queue->count)
        push_back(queue, data);
    else if (index < queue->count) {
        const unsigned int pos = index + queue->front;
        result = getpoz(queue, index);
        ((void**)dynarray_get(queue->arrays, pos / queue->arraysize + queue->firstempty))[pos % queue->arraysize] = data;
    }
    return result;
}
void * front(const deque * queue){
    void *data = NULL;
    if (queue->count > 0)
        data = ((void**)dynarray_get(queue->arrays, queue->firstempty))[queue->front];
    return data;
}
void * back(const deque * queue){
    void *data = NULL;
    if (queue->count > 0)
        data = ((void**)dynarray_get(queue->arrays, dynarray_get_count(queue->arrays) - 1 - queue->lastempty))[queue->back];
    return data;
}
void deque_for_each(const deque * queue, deque_forfn fun){
    unsigned int i;
    for (i = 0; i < queue->count; i++) {
        fun(getpoz(queue, i));
    }
}
int qsize(deque*q){
  return q->count;
}
#endif

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

enum{ MAX_N = 1010};
bool v    [MAX_N];
int  color[MAX_N];
int  size [MAX_N];


typedef struct{
  int i, j, w;
}Edge;
Edge newEdge(int i, int j, int w){
  return(Edge){i,j,w};
}
int cmpE(const void*pa, const void*pb){
  Edge*tva=(Edge*)pa;
  Edge*ono=(Edge*)pb;
  return ono->w - tva->w;
}
#define pb(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
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

vece graph[MAX_N];
//////////////////////////////////////
typedef struct Node{
  vece edges;
  struct Node*left;
  struct Node*right;
  struct Node*parent;
}Node;
void kruskall(Node*n);

Node*newNode2(Node*l, Node*r){
  Node*rv = calloc(1, sizeof(Node));
  rv->parent       = NULL;
  rv->left         = l;
  rv->right        = r;
  rv->left->parent = rv;
  rv->right->parent= rv;
  rv->edges        = newVecE();
  kruskall(rv);
  return rv;
}
Node*newNode1(Edge e){
  Node*rv = calloc(1, sizeof(Node));
  pb(rv->edges, e);
  return rv;
}
int getColor(Node*n, int x){
  if(x == color[x])
    return x;
  else{
    color[x] = getColor(n, color[x]);
    return color[x];
  }
}
void unite(Node*n, int x, int y){
  x = getColor(n, x);
  y = getColor(n, y);
  if (size[x] < size[y]){
    int t = x;
    x     = y;
    y     = t;
  }
  size [x] += size[y];
  color[y]  = x;
}
void updateParent(Node*n){
  Node*t = n->parent;
  while(t != NULL){
    kruskall(t);
    t = t->parent;
  }
}
void kruskall(Node*n){
  n->edges.sz=0;
  for(int i = 0; i < MAX_N; i++){
    color[i] = i;
    size [i] = 1;
  }
  Edge e;
  int p = 0, q = 0;
  while(p < n->left->edges.sz && q < n->right->edges.sz){
    if(n->left->edges.ptr[p].w > n->right->edges.ptr[q].w)
      e = n->left->edges.ptr[p++];
    else
      e = n->right->edges.ptr[q++];
    if(getColor(n,e.i) != getColor(n,e.j)){
      pb(n->edges, e);
      unite(n, e.i, e.j);
    }
  }
  while(p < n->left->edges.sz){
    e = n->left->edges.ptr[p++];
    if(getColor(n,e.i) != getColor(n,e.j)){
      pb(n->edges, e);
      unite(n,e.i, e.j);
    }
  }
  while(q < n->right->edges.sz){
    e = n->right->edges.ptr[q++];
    if(getColor(n,e.i) != getColor(n,e.j)){
      pb(n->edges, e);
      unite(n,e.i, e.j);
    }
  }
}
///////////////////////////////////////////////////////

int dfs(int x, int y){
  if(x == y)
    return INT_MAX;
  v[x] = true;
  for(int z=0;z<graph[x].sz;z++){Edge e = graph[x].ptr[z];
    int next = e.i + e.j - x;
    if(!v[next]){
      int temp = dfs(next, y);
      if(temp != -1)
        return fmin(e.w, temp);
    }
  }
  return -1;
}
void updateGraph(Node*t){
  for(int i = 0; i < MAX_N; i++)
    graph[i].sz=0;
  for(int z=0;z<t->edges.sz;z++){Edge e = t->edges.ptr[z];
    pb(graph[e.i], e);
    pb(graph[e.j], e);
  }
}
int main(){
  for(int i = 0; i < MAX_N; i++)
    graph[i] = newVecE();
  do{
    int n = in_nextInt();
    int m = in_nextInt();
    deque*que = newDeque();//of Node
    Node*leaf[m];
    for(int i=0; i<m; i++){
      int x = in_nextInt();
      int y = in_nextInt();
      int z = in_nextInt();
      leaf[i] = newNode1(newEdge(x, y, z));
      push_front(que, leaf[i]);
    }
    while(qsize(que)>1){
      Node*left   = pop_front(que);
      Node*right  = pop_front(que);
      Node*parent = newNode2(left, right);
      push_back(que, parent);
    }
    Node*root = pop_front(que);
    updateGraph(root);
    int events = in_nextInt();
    while(events-- > 0){ getchar();
      char type = getchar();
      int x = in_nextInt();
      int y = in_nextInt();
      if(type == 'S'){
        int truck = in_nextInt();
        if(getColor(root, x) != getColor(root, y))
          puts("0");
        else{
          memset(v, 0, sizeof(v));
          int worst = dfs(x, y);
          printf("%d\n", worst >= truck ? 1 : 0);
        }
      }
      else{
        leaf[x-1]->edges.ptr[0].w = y;
        updateParent(leaf[x-1]);
        updateGraph(root);
      }
    }
  }while(0);
  return 0;
}

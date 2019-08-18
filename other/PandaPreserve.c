#pragma GCC optimize "-O3"
#include<stdio.h>  // panda
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
typedef double db;
db eps = 1e-6;

int sign(db k){
  if(k > eps)
    return 1;
  else if(k < -eps)
    return -1;
  return 0;
}
int cmp(db k1, db k2){
  return sign(k1 - k2);
}
int inmidd(db k1, db k2, db k3){
  return sign (k1 - k3) * sign (k2 - k3) <= 0;
}
typedef struct{
  db x, y;
}pt;

pt opAdd(pt t, pt o){
  return(pt){o.x+t.x, o.y+t.y};
}
pt opSub(pt t, pt o){
  return (pt){t.x-o.x, t.y-o.y};
}
pt opMul(pt t, db o){
  return(pt){t.x*o, t.y*o};
}
pt opDiv(pt t, db o){
  return(pt){t.x/o, t.y/o};
}
int opEq(pt t, pt o){
  return cmp(t.x, o.x) == 0 &&
         cmp(t.y, o.y) == 0;
}
pt turn90(pt t){
  return (pt){-t.y, t.x};
}
bool opLt(pt t, pt o){
  int a = cmp(t.x, o.x);
   if(a == -1)
    return 1;
  else if(a == 1)
    return 0;
  else
    return cmp(t.y, o.y) == -1;
}
db Abs(pt t){
  return sqrt(t.x*t.x + t.y*t.y);
}
int getP(pt t){
  return sign(t.y) == 1 ||
        (sign(t.y) == 0 &&
         sign(t.x) == -1);
}

int inmid(pt k1, pt k2, pt k3){
  return inmidd(k1.x, k2.x, k3.x) &&
         inmidd(k1.y, k2.y, k3.y);
}
db cross (pt k1, pt k2){
  return k1.x * k2.y - k1.y * k2.x;
}
db dot (pt k1, pt k2){
  return k1.x * k2.x + k1.y * k2.y;
}
int compareangle (pt k1, pt k2){
  return getP(k1) <  getP(k2) ||
        (getP(k1) == getP(k2) && sign (cross (k1, k2)) > 0);
}
pt getLL (pt k1, pt k2, pt k3, pt k4){
  db w1 = cross(opSub(k1, k3), opSub(k4, k3));
  db w2 = cross(opSub(k4, k3), opSub(k2, k3));
  return opDiv(opAdd(opMul(k1,w2), opMul(k2,w1)),(w1+w2));
}
int intersect (db l1, db r1, db l2, db r2){
  if (l1 > r1)
    swap(l1, r1);
  if (l2 > r2)
    swap(l2, r2);
  return cmp (r1, l2) != -1 && cmp (r2, l1) != -1;
}
int checkSS (pt k1, pt k2, pt k3, pt k4){
  return intersect (k1.x, k2.x, k3.x, k4.x) &&
         intersect (k1.y, k2.y, k3.y, k4.y) &&
         sign (cross(opSub(k3, k1), opSub(k4, k1))) *
         sign (cross(opSub(k3, k2), opSub(k4, k2))) <= 0 &&
         sign (cross(opSub(k1, k3), opSub(k2, k3))) *
         sign (cross(opSub(k1, k4), opSub(k2, k4))) <= 0;
}
int onS (pt k1, pt k2, pt q){
  return inmid (k1, k2, q) && sign (cross (opSub(k1, q), opSub(k2, k1))) == 0;
}
typedef struct{
  pt a, b;
}line;
line newline(pt a, pt b){
  return(line){a,b};
}
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
line getpos(deque*q, unsigned i){
    line*kvo=(line*)getpoz(q,i);
    line rez = *kvo;
    return rez;
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
int size(deque*q){
    return q->count;
}
#endif

int include(line p, pt k){
  return sign(cross(opSub(p.b, p.a), opSub(k, p.a))) > 0;
}
pt dir(line p){
  return opSub(p.b, p.a);
}
pt getLL2(line k1, line k2){
  return getLL(k1.a, k1.b, k2.a, k2.b);
}
int parallel (line k1, line k2){
  return sign(cross(dir(k1), dir(k2))) == 0;
}
int sameDir (line k1, line k2){
  return parallel(k1, k2) && sign(dot(dir(k1), dir(k2))) == 1;
}
int cmpL(const void*pa, const void*pb){
  line*aa=(line*)pa;
  line*bb=(line*)pb;
  line k1= *aa;
  line k2= *bb;
  if(sameDir (k1, k2))
    return include(k2, k1.a)?-1:1;
  return compareangle(dir(k1), dir(k2))?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
line*pushbackL(line*array, int *size, line value){
  line*output = resizeArray(array, line, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	line*ptr;
	int sz;
}vecl;
vecl newVecL(){
	vecl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int checkpos(line k1, line k2, line k3){
  return include(k3, getLL2(k1, k2));
}
vecl getHL(vecl*L){
  qsort(L->ptr, L->sz, sizeof(line), cmpL);
  deque*q=newDeque();//of line
  for(int i=0; i<L->sz; i++){
    if(i && sameDir(L->ptr[i], L->ptr[i-1]))
      continue;
    while(size(q) > 1 && !checkpos(getpos(q, size(q)-2), getpos(q, size(q)-1), L->ptr[i]))
      pop_back(q);
    while(size(q) > 1 && !checkpos(getpos(q,1), getpos(q,0), L->ptr[i]))
      pop_front(q);
    push_back(q, &L->ptr[i]);
  }
  while(size(q) > 2 && !checkpos(getpos(q, size(q)-2), getpos(q, size(q)-1), getpos(q,0)))
    pop_back(q);
  while(size(q) > 2 && !checkpos(getpos(q,1), getpos(q,0), getpos(q, size(q)-1)))
    pop_front(q);
  vecl ans = newVecL();
  for(int i=0; i< size(q); i++)
    ans.ptr = pushbackL(ans.ptr, &ans.sz, getpos(q, i));
  return ans;
}
int contain(pt*A, int Asz, pt q){
  int pd = 0;
  for(int i = 1; i < Asz; i++){
    pt u = A[i-1],
       v = A[i];
    if(onS (u, v, q))
      return 1;
    if(cmp (u.y, v.y) > 0)
      swap (u, v);
    if(cmp (u.y, q.y) >= 0 || cmp (v.y, q.y) < 0)
      continue;
    if(sign(cross(opSub(u, v), opSub(q, v))) < 0)
      pd ^= 1;
  }
  return pd << 1;
}
int main(){
  int n;
  double ans = 0;
  scanf ("%d", &n);
  pt p[n+1];
  for (int i = 0; i < n; ++i)
    scanf ("%lf %lf", &p[i].x, &p[i].y);
  for (int i = 0; i < n; ++i){
    vecl L=newVecL();
    L.ptr=pushbackL(L.ptr, &L.sz, (line){(pt){ -20000, -20000}, (pt){ 20000, -20000}});
    L.ptr=pushbackL(L.ptr, &L.sz, (line){(pt){  20000, -20000}, (pt){ 20000,  20000}});
    L.ptr=pushbackL(L.ptr, &L.sz, (line){(pt){  20000,  20000}, (pt){-20000,  20000}});
    L.ptr=pushbackL(L.ptr, &L.sz, (line){(pt){ -20000,  20000}, (pt){-20000, -20000}});
    for(int j = 0; j < n; ++j){
      if(i == j)
        continue;
      pt mid = opDiv(opAdd(p[i], p[j]), 2);
      L.ptr=pushbackL(L.ptr, &L.sz, (line){ mid, opAdd(turn90(opSub(p[j], mid)), mid)});
    }
    L = getHL(&L);
    int sz = L.sz;
    if(sz > 2){
      pt v[sz];
      for(int j = 0; j < sz; ++j){
        v[j] = getLL2(L.ptr[j], L.ptr[(j + 1) % sz]);
        p[n]=p[0];
        if(contain(p, n+1, v[j]))
          ans = fmax(ans, Abs(opSub(p[i], v[j])));
      }
      for(int j = 0; j < sz; ++j){
        line l1 = (line){v[j], v[(j + 1) % sz]};
        for(int k = 0; k < n; ++k){
          line l2 = (line){p[k], p[(k + 1) % n]};
          if(checkSS(v[j], v[(j + 1) % sz], p[k], p[(k + 1) % n])){
            pt u = getLL2(l1, l2);
            ans = fmax(ans, Abs(opSub(p[i], u)));
          }
        }
      }
    }
  }
  printf ("%.9f\n", ans);
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef unsigned long long ll;
typedef long double ld;

ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

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


enum{ maxn =(int)5e4 + 5};
int id[maxn];

typedef struct Tree{
    int N;
    vec G[maxn];
    int child[maxn];
    ll  sumDn[maxn], sumUp[maxn];
    ll  sqDn [maxn], sqUp [maxn];
}Tree;

void read(Tree*t){
    scanf("%d", &t->N);
    for(int i=1; i<t->N; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        t->G[u].ptr = pushback(t->G[u].ptr, &t->G[u].sz, v);
        t->G[v].ptr = pushback(t->G[v].ptr, &t->G[v].sz, u);
    }
}
void dfs_down(Tree*t, int v, int par){
    t->child[v] = 1;
    t->sumDn[v] = 0;
    t->sqDn [v] = 0;
    for(int z=0;z<t->G[v].sz;z++){int u = t->G[v].ptr[z];
        if(u == par)
            continue;
        dfs_down(t, u, v);
        t->child[v] += t->child[u];
        t->sumDn[v] += t->sumDn[u] + t->child[u];
        t->sqDn [v] += t->sqDn [u] + 2*t->sumDn[u] + t->child[u];
    }
}
void dfs_up(Tree*t, int v, int par, int cnt, ll sum, ll sq){
    t->sumUp[v] = sum;
    t->sqUp [v] = sq;
    for(int z=0;z<t->G[v].sz;z++){int u = t->G[v].ptr[z];
        if(u == par)
            continue;
        int cntOut = t->child[v] - t->child[u];
        ll  sumOut = t->sumDn[v] - t->sumDn[u] - t->child[u];
        ll  sqOut  = t->sqDn [v] - t->sqDn [u]-2*t->sumDn[u] - t->child[u];
        dfs_up(t, u, v, cnt+cntOut, sum+sumOut+cnt+cntOut, sq+sqOut+2*(sumOut+sum)+cntOut+cnt);
    }
}
void run(Tree*t){
    read(t);
    dfs_down(t, 1, 0);
    dfs_up(t, 1, 0, 0, 0, 0);
}
ll sum(Tree*t, int v){
    return t->sumUp[v] + t->sumDn[v];
}
ll sq(Tree*t, int v){
    return t->sqUp[v] + t->sqDn[v];
}

Tree A, B;

typedef struct{
    ll a, b;
}line;
ll val(line l, ll x){
    return l.a*x+l.b;
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
void * pop_front(deque * queue);
void * pop_back(deque * queue);
void * getpoz(const deque *queue, unsigned int index);
void * deque_set_at(deque *queue, unsigned int index, void * data);
line front(const deque * queue);
line back(const deque * queue);
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
void push_back(deque * queue, line data){
    unsigned int index;
    if (queue->count == 0)
        index = queue->arraysize / 2;
    else if (queue->lastempty)
        index = 0;
    else if (queue->back == queue->arraysize - 1) {
        dynarray_add_tail(queue->arrays, malloc(queue->arraysize * sizeof(void*)));
        index = 0;
    }
    else
        index = queue->back + 1;
    line*ldt = calloc(1, sizeof(line));
    ldt->a = data.a;
    ldt->b = data.b;
    ((void**)dynarray_get(queue->arrays, queue->arrays->count - 1))[index] = ldt;
    queue->back = index;
    queue->lastempty = 0;
    if (queue->arrays->count == 1)
        queue->firstempty = 0;
    queue->count++;
    if (queue->count == 1)
        queue->front = queue->back;
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

line front(const deque*queue){
    void *data = NULL;
    if (queue->count > 0)
        data = ((void**)dynarray_get(queue->arrays, queue->firstempty))[queue->front];
    if(data)
        return(*(line*)data);
    assert(!"front error");
    line err;
    return err;
}
line back(const deque*queue){
    void*data = NULL;
    if(queue->count > 0)
        data = ((void**)dynarray_get(queue->arrays, dynarray_get_count(queue->arrays) - 1 - queue->lastempty))[queue->back];
    if(data)
        return(*(line*)data);
    line err = (line){0, 0};
    return err;
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

deque*q;
ld intx(line a, line b){
    return(1.0L*b.b-1.0L*a.b)*1.0L/(a.a-b.a);
}
bool bad(line a, line b, line c){
    return intx(a, b) > intx(b, c);
}
void add(line l){
    line backq = back(q);
    if(size(q) && backq.a == l.a){
        l.b = min(l.b, backq.b);
        pop_back(q);
        backq = back(q);
    }
    int sz = size(q);
    while(size(q) >= 2 && bad(getpos(q,sz-2), getpos(q, sz-1), l))
        --sz, pop_back(q);
    push_back(q, l);
}
ll query(ll x){
    while(size(q)>1 && val(getpos(q,0), x) >= val(getpos(q, 1), x))
        pop_front(q);
    return val(front(q), x);
}



int cmp1(const void*pa, const void*pb){
    int a = *((int*)pa);
    int b = *((int*)pb);
    return sum(&B, a) > sum(&B, b);
}
int cmp2(const void*pa, const void*pb){
    int a = *((int*)pa);
    int b = *((int*)pb);
    return sum(&A, a) < sum(&A, b);
}
int main(){
    q = newDeque();//of line
    run(&A);
    run(&B);
    for(int i=1; i<=B.N; ++i)
        id[i] = i;
    qsort(id+1, B.N, sizeof(int), cmp1);
    for(int i=1; i<=B.N; ++i){
        int pos = id[i];
        add((line){2*sum(&B, pos), 2*sum(&B, pos)*A.N+A.N*sq(&B, pos)});
    }
    ll ans = -1ll;
    for(int i=1; i<=A.N; ++i)
        id[i] = i;
    qsort(id+1, A.N, sizeof(int), cmp2);
    for(int i=1; i<=A.N; ++i){
        int pos = id[i];
        ans = min(ans, sq(&A, pos)*B.N+2 * sum(&A, pos)*B.N+query(sum(&A, pos))+1LL*A.N*B.N);
    }
    ll sum = 0;
    for(int i=1; i<=A.N; ++i)
        sum += sq(&A, i);
    for(int j=1; j<=B.N; ++j)
        sum += sq(&B, j);
    printf("%lld\n", ans + sum / 2);
    return 0;
}

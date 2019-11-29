#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

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
int size(deque*q){
  return q->count;
}
#endif
typedef long long ll;
int main(){
    int n;
    scanf("%d", &n);
    int t[n];
    int c[n];
    for(int i=0; i<n; i++)
        scanf("%d %d", &t[i], &c[i]);
    int start[n]; clr(start);
    deque*Q = newDeque();
    for(int i=0; i<n; i++)
        push_back(Q, (intptr_t*)(ll)i);
    while(size(Q)>0){
        int fq = (ll)(intptr_t*)front(Q);
        int t_finish = start[fq]+t[fq];
        vec players = newVec();
        while(size(Q)>0 && start[fq]+t[fq] <= t_finish){
            pb(players, fq);
            pop_front(Q);
            fq = (ll)(intptr_t*)front(Q);
        }
        qsort(players.ptr, players.sz, sizeof(int), cmp);
        for(int z=0;z<players.sz;z++){int i = players.ptr[z];
            start[i] = t_finish;
            c[i]--;
            if(c[i]>0)
                push_back(Q, (intptr_t*)(ll)i);
        }
    }
    for(int i=0; i<n; i++)
        printf("%d\n", start[i]);
    return 0;
}

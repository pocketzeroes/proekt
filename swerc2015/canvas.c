#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
#define int ll
#if 1 //pq
#define INIT_CAP 100

inline void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
typedef struct HeapS{
    int *harr; 
    int capacity;
    int heap_size;
}Heap;


inline int parent(int i) { return (i-1)/2; }
inline int left  (int i) { return (2*i + 1); }
inline int right (int i) { return (2*i + 2); }
void MinHeapify(Heap*h, int i);

Heap*newHeap(){
    int cap = INIT_CAP;
    Heap*rez = (Heap*) malloc(sizeof(Heap));
    rez->heap_size = 0;
    rez->capacity  = cap;
    rez->harr      = (int*) calloc(cap,sizeof(int));
    return rez;
}
Heap*copyHeap(Heap*ori){
    Heap*rez = (Heap*) malloc(sizeof(Heap));
    rez->heap_size = ori->heap_size;
    rez->capacity  = ori->capacity;
    int cap = ori->capacity;
    rez->harr = (int*) calloc(cap, sizeof(int));
    memcpy(rez->harr, ori->harr, cap*sizeof(int));
    return rez;
}
inline int top(Heap*h) { 
    return h->harr[0]; 
}
inline size_t size(Heap*h){
    return h->heap_size;
}    
void push(Heap*h, int k){
    if (h->heap_size == h->capacity)
    {
        int newcap = 2*h->capacity;
        h->harr = realloc(h->harr, newcap*sizeof(int));
        h->capacity = newcap;
    }
    h->heap_size++;
    int i = h->heap_size - 1;
    h->harr[i] = k;
    while (i != 0 && h->harr[parent(i)] > h->harr[i]) // was >
    {
       swap(&h->harr[i], &h->harr[parent(i)]);
       i = parent(i);
    }
}
void decreaseKey(Heap*h, int i, int new_val){
    h->harr[i] = new_val;
    while (i != 0 && h->harr[parent(i)] > h->harr[i]) // was >
    {
       swap(&h->harr[i], &h->harr[parent(i)]);
       i = parent(i);
    }
}
int pop(Heap*h){
    if (h->heap_size <= 0) return INT_MAX;
    if (h->heap_size == 1)
    {
        h->heap_size--;
        return h->harr[0];
    }
    int root = h->harr[0];
    h->harr[0] = h->harr[h->heap_size-1];
    h->heap_size--;
    MinHeapify(h, 0);//was 0
    return root;
}
void MinHeapify(Heap*h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < h->heap_size && h->harr[l] < h->harr[i])         // was<
        smallest = l;
    if (r < h->heap_size && h->harr[r] < h->harr[smallest])  //was <
        smallest = r;
    if (smallest != i)
    {
        swap(&h->harr[i], &h->harr[smallest]);
        MinHeapify(h, smallest);
    }
}

#endif
#undef int
ll minPaint(Heap*seq){
    int nScans = size(seq) - 1;
    ll sum = 0L;
    for(int i = 0; i < nScans; i++ ){
        ll colorX = top(seq); pop(seq);
        ll colorY = top(seq); pop(seq);
        ll oldColor = colorX + colorY;
        push(seq, oldColor);
        sum += oldColor;
    }
    return sum;
}
int main(){
    int nTests;
    scanf("%d", &nTests);
    for(int t = 0; t < nTests; t++){
        int nCanvas;
        scanf("%d", &nCanvas);
        Heap*canvas = newHeap();
        for(int i = 0; i < nCanvas; i++){
            ll tokens_i;
            scanf("%lld", &tokens_i);
            push(canvas, tokens_i);
        }
        printf("%lld\n", minPaint(canvas));
    }
    return 0;
}

// secret-026 ok 9s
// secret-027 ok 9s
// secret-028 ok
// secret-029 ok
// secret-030 ok
// secret-031 ok
// secret-032 ok
// secret-033 ok
// secret-034 ok
// secret-035 ok
// secret-036 ok
// secret-037 ok
// secret-038 ok
// secret-039 ok
// secret-040 ok
// secret-041 ok
// secret-042 ok
// secret-043 ok
// secret-044 ok
// secret-045 ok
// secret-046 ok
#pragma GCC optimize "-O4"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif

typedef struct PairS{
    int first;
    int second;
}Pair;
Pair newPair(int a, int b) {
    Pair rez;
    rez.first = a;
    rez.second = b;
    return rez;
}
int cmpP(const void*pa, const void*pb)
{
    Pair*a = (Pair*)pa;
    Pair*b = (Pair*)pb;
    int diff;
    diff = a->first - b->first;  if (diff != 0) return diff;
    return a->second - b->second;
}


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
    while (i != 0 && h->harr[parent(i)] < h->harr[i]) // was >
    {
       swap(&h->harr[i], &h->harr[parent(i)]);
       i = parent(i);
    }
}
void decreaseKey(Heap*h, int i, int new_val){
    h->harr[i] = new_val;
    while (i != 0 && h->harr[parent(i)] < h->harr[i]) // was >
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
    if (l < h->heap_size && h->harr[l] > h->harr[i])         // was<
        smallest = l;
    if (r < h->heap_size && h->harr[r] > h->harr[smallest])  //was <
        smallest = r;
    if (smallest != i)
    {
        swap(&h->harr[i], &h->harr[smallest]);
        MinHeapify(h, smallest);
    }
}



//////////////
typedef long long ll;
typedef struct PartialS {
    int  t;
    int  curi;
    int  nphoto;
    int  dli;
    ll   sumstarts;
    bool after_photo;
}prt;
prt newPartial() {
    prt rez;
    rez.t           = 0;
    rez.curi        = 0;
    rez.nphoto      = 0;
    rez.dli         = 0;
    rez.sumstarts   = 0LL;
    rez.after_photo = false;
    return rez;
}
int cmpPa(prt a, prt b){
    if (a.t      != b.t)      return (a.t      > b.t     )?-1:1;
    if (a.nphoto != b.nphoto) return (a.nphoto < b.nphoto)?-1:1;
    return (a.sumstarts < b.sumstarts)?-1:1;
}
void p_swap(prt *x, prt *y){
    prt temp = *x;
    *x = *y;
    *y = temp;
}
#define INIT_CAP 100
typedef struct prtHeapS{
    prt *harr;
    int capacity;
    int heap_size;
}pHeap;

void p_MinHeapify(pHeap*h, int i);
pHeap p_newHeap(){
    int cap = INIT_CAP;
    pHeap rez;
    rez.heap_size = 0;
    rez.capacity  = cap;
    rez.harr      =(prt*) calloc(cap,sizeof(prt));
    return rez;
}
inline prt p_top(pHeap*h) {
    return h->harr[0];
}
inline size_t p_size(pHeap*h){
    return h->heap_size;
}
inline bool p_empty(pHeap*h){
    return (h->heap_size==0);
}
void p_push(pHeap*h, prt k){
    if (h->heap_size == h->capacity)
    {
        int newcap = 2*h->capacity;
        h->harr = realloc(h->harr, newcap*sizeof(prt));
        h->capacity = newcap;
    }
    h->heap_size++;
    int i = h->heap_size - 1;
    h->harr[i] = k;
    while (i != 0 && cmpPa(h->harr[parent(i)] , h->harr[i])<0 )//h->harr[parent(i)] < h->harr[i])
    {
       p_swap(&h->harr[i], &h->harr[parent(i)]);
       i = parent(i);
    }
}
void p_pop(pHeap*h){
    if (h->heap_size <= 0) assert( !"cannot p_pop INT_MAX");
    if (h->heap_size == 1)
    {
        h->heap_size--;
        return;// h->harr[0];
    }
    prt root = h->harr[0];
    h->harr[0] = h->harr[h->heap_size-1];
    h->heap_size--;
    p_MinHeapify(h, 0);
}
void p_MinHeapify(pHeap*h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < h->heap_size && cmpPa(h->harr[l] , h->harr[i])>0) //h->harr[l] > h->harr[i])
        smallest = l;
    if (r < h->heap_size && cmpPa(h->harr[r] , h->harr[smallest])>0)//h->harr[r] > h->harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        p_swap(&h->harr[i], &h->harr[smallest]);
        p_MinHeapify(h, smallest);
    }
}


//////////////



#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Heap**pushbackH(Heap**array, int *size, Heap*value){
    Heap**output = resizeArray(array, Heap*, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
    Heap**ptr;
    int sz;
}vec;
vec newVec() {
    vec rez;
    rez.ptr = NULL;
    rez.sz = 0;
    return rez;
}









int j;

int main() {
  int N, T;
  while(scanf("%d %d", &N, &T)==2) {
    Pair*V = (Pair*) calloc(N, sizeof(Pair));
    for (int i = 0; i < N; i++)
      scanf("%d %d", &V[i].first, &V[i].second);
    qsort(V, N, sizeof(Pair), cmpP);
    bool ret = false;
    pHeap q = p_newHeap();
    vec deadlines = newVec(); deadlines.ptr = pushbackH(deadlines.ptr, &deadlines.sz, newHeap());
    prt start; start.after_photo = false; start.t = start.curi = start.nphoto = start.dli = start.sumstarts = 0;
    p_push(&q, start);
    while (!p_empty(&q)) {
      prt p = p_top(&q);
      while (!p_empty(&q) && p_top(&q).t == p.t){

        p_pop(&q);

      }
      if (p.nphoto == N) {
        ret = true;
        break;
      }
      if (p.after_photo) {
        pop(deadlines.ptr[p.dli]);
      }
      else {
        deadlines.ptr = pushbackH(deadlines.ptr, &deadlines.sz, copyHeap(deadlines.ptr[p.dli]) );
        p.dli = deadlines.sz - 1;
      }
      Heap* dl = deadlines.ptr[p.dli];
      for (; p.curi < N && V[p.curi].first <= p.t; p.curi++) {
        push(dl, -V[p.curi].second);


      }
      if (size(dl) && -top(dl) < p.t + T){
//        printf("p.t = %d ; T = %d\n", p.t , T);
        continue;
      }
      if (p.curi < N && (!size(dl) || V[p.curi].first < p.t+T))
      {
        p.after_photo = false;
        int ot = p.t;
        p.t = V[p.curi].first;

        p_push(&q, p);
        p.t = ot;
      }
      if (size(dl))
      {
        p.after_photo = true;
        p.nphoto++;
        p.sumstarts += p.t;
        p.t += T;

        p_push(&q, p);
      }

      j++;
    }
    puts(ret ? "yes" : "no");
  }
}















































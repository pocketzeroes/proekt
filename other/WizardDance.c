#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
  ll first;
  ll second;
}pair;
pair newpair(ll a, ll b){
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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

#if 1 //queueue
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;  
  Q->Back = -1;  
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity) 
    Q->Back = 0;
  Q->Elements[Q->Back] = e;  
  Q->NumElements++;
  return 1;  
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif

//////////////////////////////////


int main(){
    int N;
    scanf("%d", &N);
    vecp E [N]; clr(E);
    int p  [N]; clr(p);
    int deg[N]; clr(deg);
    for(int i=0; i<N; ++i){
        scanf("%d", &p[i]);
        int l = (i + p[i]) % N,
            r = (N + i - p[i]) % N;
        if(l != r){
            pbp(E[l], newpair(r, i));
            pbp(E[r], newpair(l, i));
            deg[l]++, deg[r]++;
        }
        else{
            deg[l]++;
            pbp(E[l], newpair(l, i));
        }
    }
    Queue*q = newQueue();
    for(int i = 0; i < N; ++i)
        if(deg[i] == 1)
            push(q, i);
    int m[N]; fill(m, N, -1);
    while(!empty(q)){
        int u = front(q); pop(q);
        if(deg[u] <= 0)
            continue;
        for(int z=0;z<E[u].sz;z++){pair vw = E[u].ptr[z];
            int v = vw.first,
               id = vw.second;
            if(deg[v] == 0)
                continue;
            if(v != u){
                deg[v]--;
                m[id] = u;
                if(deg[v] == 1)
                    push(q, v);
            }
            else
                m[id] = u;
            break;
        }
        deg[u]--;
    }
    vec ord = newVec();
    for(int i = 0; i < N; ++i){
        if(m[i] < 0){
            if(deg[(i + p[i]) % N] > 0)
                pb(ord, (i + p[i]) % N);
            else if(deg[(N + i - p[i]) % N] > 0)
                pb(ord, (N + i - p[i]) % N);
        }
    }
    for(int z=0;z<ord.sz;z++){int u = ord.ptr[z];
        if(deg[u] == 0)
            continue;
        int v = u;
        while(1){
            pair vw = newpair(-1,-1);
            for(int q=0;q<E[v].sz;q++){pair _vw = E[v].ptr[q];
                if(m[_vw.second] < 0){
                    vw = _vw;
                    break;
                }
            }
            if(vw.first < 0) 
                break;
            int w  = vw.first;
            int id = vw.second;
            if(w == v){
                m[id] = w;
                deg[v] = 0;
                break;
            }
            else{
                m[id] = v;
                deg[v] = 0;
                v = w;
            }
            if(v == u)
                break;
        }
    }
    bool ok = true;
    for(int _=0;_<N;_++){int v = m[_];
        ok = ok && v >= 0;
    }
    if(ok){
        for(int i=0; i<N; ++i)
            putchar((i+p[i])%N == m[i] ? 'L' : 'R');
        puts("");
    }
    else 
        puts("no dance");
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1 //que
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

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int gcd(int a, int b){
  return (b == 0) ? a : gcd(b, a % b);
}
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
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
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

typedef long long ll;
enum{ maxm =(int)1e7 + 7};
int d[maxm];
ll pi[maxm];
vec good_mod;
int*in;
vec2d circles[10];
vec g [10];
vec id[10];
vec cc[10];

int fib(ll n, int mod){
    ll x = 0, y = 1;
    for (int i = 59; i >= 0; --i){
        ll ox = x, oy = y;
        y = (ox * ox + oy * oy) % mod;
        x = ox * (oy + oy - ox + mod) % mod;
        if (n >> i & 1)
            y = (y + x) % mod, x = (y - x + mod) % mod;
    }
    return x;
}
ll cal(ll n, ll k, int m){
    if (m == 1)
        return 0;
    if (k == 1)
        return fib(n, m);
    if (pi[m] != m)
        return fib(cal(n, k - 1, pi[m]), m);
    int idm = lower_bound(good_mod.ptr, good_mod.sz, m);
    int cur = fib(n, m);
    --k;
    while(!~cc[idm].ptr[cur]){
        cur = g[idm].ptr[cur];
        --k;
        if(k == 0)
            return cur;
    }
    int pos = cc[idm].ptr[cur],
        idx = id[idm].ptr[cur];
    idx = (idx + k) % circles[idm].ptr[pos].sz;
    return circles[idm].ptr[pos].ptr[idx];
}
int main(){
    for (int i = 1; i < maxm; ++i)
        d[i] = i;
    for (int i = 2; i < maxm; ++i){
        if (d[i] == i) {
            if (i == 2)
                pi[i] = 3;
            else if (i == 5)
                pi[i] = 20;
            else if (i % 10 == 1 || i % 10 == 9)
                pi[i] = i - 1;
            else
                pi[i] = 2 * (i + 1);
            for (int j = i + i; j < maxm; j += i)
                d[j] = i;
        }
        else{
            int t = d[i], m = 1, x = i;
            while (x % t == 0)
                x /= t, m *= t;
            if (x == 1)
                pi[i] = t * pi[i/t];
            else
                pi[i] = pi[m] / gcd(pi[m], pi[x]) * pi[x];
        }
        if (pi[i] == i){
            int idm = good_mod.sz;
            good_mod.ptr = pushback(good_mod.ptr, &good_mod.sz, i);
            id[idm].ptr=calloc(i,sizeof(int)); fill(id[idm].ptr, i, -1); id[idm].sz=i;
            cc[idm].ptr=calloc(i,sizeof(int)); fill(cc[idm].ptr, i, -1); cc[idm].sz=i;
            g [idm].ptr=calloc(i,sizeof(int)); g [idm].sz=i;
            in = calloc(i, sizeof(int));
            g[idm].ptr[0] = 0,
            g[idm].ptr[1] = 1;
            in[0] = in[1] = 1;
            for (int j = 2; j < i; ++j)
                g[idm].ptr[j] = (g[idm].ptr[j-1] + g[idm].ptr[j-2]) % i, ++in[g[idm].ptr[j]];
            Queue*q = newQueue();
            for(int j = 0; j < i; ++j)
                if(!in[j])
                    push(q, j);
            while(!empty(q)){
                int u = front(q); pop(q);
                int v = g[idm].ptr[u];
                --in[v];
                if (!in[v])
                    push(q, v);
            }
            for(int j = 0; j < i; ++j){
                if (in[j]){
                    int x = j;
                    circles[idm].ptr = pushback2d(circles[idm].ptr, &circles[idm].sz, newVec());
                    while (in[x]) {
                        cc[idm].ptr[x] = circles[idm].sz - 1;
                        id[idm].ptr[x] = circles[idm].ptr[circles[idm].sz-1].sz;
#define back circles[idm].ptr[circles[idm].sz-1]
                        back.ptr = pushback(back.ptr, &back.sz, x);
                        in[x] = 0;
                        x = g[idm].ptr[x];
                    }
                }
            }
        }
    }
    int ntest;
    scanf("%d", &ntest);
    while(ntest--){
        ll n, k, m;
        scanf("%lld %lld %lld", &n, &k, &m);
        printf("%lld\n", cal(n, k, m));
    }
    return 0;
}

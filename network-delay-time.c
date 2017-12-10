////////////////////////////////min max
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
////////////////////////////////vecp
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////////////queue
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
int size(Queue*Q){
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
    assert(!"error in pop -1\n");
    exit(0);
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
    printf("-1\n");
    exit(0);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)  
      return 1;  
    ++i;
    if (i == Q->Capacity)  
      i = 0;
  }
  return 0;
}

////////////////////////////////
vecp g  [110];
int  d  [110];
bool inq[110];
enum{ inf =(int) 1e9};

int networkDelayTime(int**times, int timesSz, int times0sz, int n, int s){
    for(int i = 1; i <= n; ++i) 
        g[i].sz = 0;
    for(int z=0; z<timesSz; z++){int*x = times[z];
        g[x[0]].ptr = pushbackP(g[x[0]].ptr, &g[x[0]].sz, newPair(x[1], x[2]));
    }
    for(int i = 1; i <= n; ++i) 
        d[i] = inf;
    d[s] = 0;
    memset(inq, 0, sizeof inq);
    Queue*q = newQueue();
    push(q, s);
    while(size(q)){
        int x = front(q); pop(q); inq[x] = false;
        for(int z=0;z<g[x].sz;z++){pair e = g[x].ptr[z];
            int y = e.first;
            int w = e.second;
            int nd = d[x] + w;
            if (nd < d[y]){
                d[y] = nd;
                if (!inq[y]){
                    inq[y] = true;
                    push(q, y);
                }
            }
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i){
        if(d[i] >= inf)
            return -1;
        mx = max(mx, d[i]);
    }
    return mx;
}

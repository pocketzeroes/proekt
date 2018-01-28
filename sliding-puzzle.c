#define swap(x, y) do { int tSWAP = x; x = y; y = tSWAP; } while (0)
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

#endif


////////////////////////////

int d[50010];
int**b;
int f(){
  int r = 0;
  for (int i = 0; i < (int)(2); ++i) for (int j = 0; j < (int)(3); ++j) r = r * 6 + b[i][j];
  return r;
}
void g(int r){
  for (int i = 1; i >= 0; --i)
    for (int j = 2; j >= 0; --j) {
      b[i][j] = r % 6;
      r /= 6;
    }
}
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int slidingPuzzle(int**board, int boardSz, int*board0szs){
  memset(d, -1, sizeof d);
  b = board;
  int s = f();
  Queue*q = newQueue();
  push(q, s);
  d[s] = 0;
  while(size(q)) {
    int x = front(q); pop(q); g(x);
    for (int i = 0; i < (int)(2); ++i) for (int j = 0; j < (int)(3); ++j) if (b[i][j] == 0) {
      for (int t = 0; t < (int)(4); ++t) {
        int ti = i + dx[t];
        int tj = j + dy[t];
        if (ti < 0 || tj < 0 || ti >= 2 || tj >= 3) continue;
        swap(b[i][j], b[ti][tj]);
        int y = f();
        if (d[y] == -1 || d[x] + 1 < d[y]) {
          d[y] = d[x] + 1;
          push(q,y);
        }
        swap(b[i][j], b[ti][tj]);
      }
      i = 3;
      break;
    }
  }

  b[0][0]=1;
  b[0][1]=2;
  b[0][2]=3;
  
  b[1][0]=4;
  b[1][1]=5;
  b[1][2]=0;
  
  int t = f();
  return d[t];
}

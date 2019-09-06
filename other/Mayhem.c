#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair make_pair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#if 1 //que
typedef pair QueueElementType;
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

enum{ MAXR = 5005,
      MAXC = 5005};
int R, C, total = 0, components = 0;
char G[MAXR][MAXC];
int lcol[MAXR][MAXC], rcol[MAXR][MAXC];
int urow[MAXR][MAXC], drow[MAXR][MAXC];

void init_pointers(){
  memset(lcol, -1, sizeof lcol);
  memset(rcol, -1, sizeof rcol);
  memset(urow, -1, sizeof urow);
  memset(drow, -1, sizeof drow);
  int curr;
  for (int i = 0; i < R; i++){
    curr = -1;
    for (int j = 0; j < C; j++) {
      if (G[i][j] == 'x') {
        lcol[i][j] = curr;
        curr = j;
      }
    }
    curr = -1;
    for (int j = C - 1; j >= 0; j--) {
      if (G[i][j] == 'x') {
        rcol[i][j] = curr;
        curr = j;
      }
    }
  }
  for (int j = 0; j < C; j++) {
    curr = -1;
    for (int i = 0; i < R; i++) {
      if (G[i][j] == 'x') {
        urow[i][j] = curr;
        curr = i;
      }
    }
    curr = -1;
    for (int i = R - 1; i >= 0; i--) {
      if (G[i][j] == 'x') {
        drow[i][j] = curr;
        curr = i;
      }
    }
  }
}
void update_pointers(int r, int c) {
  if (lcol[r][c] != -1) {
    if (rcol[r][c] != -1) {
      rcol[r][lcol[r][c]] = rcol[r][c];
      lcol[r][rcol[r][c]] = lcol[r][c];
    } 
    else {
      rcol[r][lcol[r][c]] = -1;
    }
  }
  if (urow[r][c] != -1) {
    if (drow[r][c] != -1) {
      drow[urow[r][c]][c] = drow[r][c];
      urow[drow[r][c]][c] = urow[r][c];
    } 
    else {
      drow[urow[r][c]][c] = -1;
    }
  }
  if (rcol[r][c] != -1) {
    if (lcol[r][c] != -1) {
      lcol[r][rcol[r][c]] = lcol[r][c];
      rcol[r][lcol[r][c]] = rcol[r][c];
    } 
    else {
      lcol[r][rcol[r][c]] = -1;
    }
  }
  if (drow[r][c] != -1) {
    if (urow[r][c] != -1) {
      urow[drow[r][c]][c] = urow[r][c];
      drow[urow[r][c]][c] = drow[r][c];
    } 
    else {
      urow[drow[r][c]][c] = -1;
    }
  }
}
void flood(int r, int c) {
  Queue*q=newQueue();//of pair
  for(push(q, make_pair(r, c)); !empty(q); pop(q)){
    r = front(q).first;
    c = front(q).second;
    if(G[r][c] == '.')
      continue;
    total++;
    G[r][c] = '.';
    update_pointers(r, c);
    if (lcol[r][c] != -1) push(q, make_pair(r, lcol[r][c]));
    if (urow[r][c] != -1) push(q, make_pair(urow[r][c], c));
    if (rcol[r][c] != -1) push(q, make_pair(r, rcol[r][c]));
    if (drow[r][c] != -1) push(q, make_pair(drow[r][c], c));
  }
}
int main(){
  scanf("%d %d", &R, &C);
  getchar();
  for(int i=0; i<R; i++){
    for(int j=0; j<C; j++){
      G[i][j]=getchar();
    }
    getchar();
  }
  init_pointers();
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      if(G[i][j] == 'x'){
        flood(i, j);
        components++;
      }
    }
  }
  printf("%d\n", total - components);
  return 0;
}

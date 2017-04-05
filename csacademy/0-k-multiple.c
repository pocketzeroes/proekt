
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *CreateQueue(int N);
void   DeleteQueue(Queue *Q);
int    isEmptyQueue(Queue *Q);
int    Enqueue(Queue *Q, QueueElementType e);
QueueElementType Dequeue(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *CreateQueue(int N)
{
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in CreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
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
int isEmptyQueue(Queue *Q)
{
  return Q->NumElements == 0;
}
int Enqueue(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in Enqueue: malloc failed to allocate\n\n");
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
QueueElementType Dequeue(Queue *Q)
{
  if (isEmptyQueue(Q))  
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType Front(Queue *Q)
{
  if (isEmptyQueue(Q))  
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
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


///
const int kNotFound = -1;

void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

char*Solve(int n, int d){
    int father[n];
    int letter[n];
    for (int i=0;i<n;i++)
        father[i]=letter[i]=kNotFound;
    father[d % n] = 0;
    letter[d % n] = d;
    Queue*q=CreateQueue(1024);
    Enqueue(q, d % n);
    while (father[0] == kNotFound) {
        int itr = Front(q);
        Dequeue(q);
        for(int digit=0,i=0;i<2;digit=d,i++){
            int next = (itr * 10 + digit) % n;
            if (father[next] == kNotFound) {
                letter[next] = digit;
                father[next] = itr;
                Enqueue(q,next);
            }
        }
    }
    char number[512];
    int numberLen=0;
    int l = 0;
    do {
        number[numberLen++] = '0' + letter[l];
        l = father[l];
    } 
    while (l != 0);
    number[numberLen]='\0';
    inplace_reverse(number);
    return strdup(number);
}
int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    puts(Solve(n, d));
    return 0;
}















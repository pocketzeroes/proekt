#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
typedef int QueueElementType;
typedef struct MyQueue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} MyQueue;

MyQueue *myQueueCreate(int N)
{
  MyQueue *Q;
  if (N < 1)
  {
    printf("\n**Error in CreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (MyQueue *)malloc(sizeof(MyQueue));
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
void myQueueFree(MyQueue *Q)
{
  free(Q->Elements);
  free(Q);
}
int myQueueEmpty(MyQueue *Q)
{
  return Q->NumElements == 0;
}
int myQueuePush(MyQueue *Q, QueueElementType e)
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
QueueElementType myQueuePop(MyQueue *Q)
{
  if (myQueueEmpty(Q))  
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
QueueElementType myQueuePeek(MyQueue *Q)
{
  if (myQueueEmpty(Q))  
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
typedef struct TreeNode TreeNode;
typedef TreeNode* TriqueEl;
typedef struct Trique
{
  TriqueEl  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Trique;
Trique * zCreateQueue(int N);
void     zDeleteQueue(Trique *Q);
int      zisEmptyQueue(Trique *Q);
int      zEnqueue(Trique *Q, TriqueEl e);
TriqueEl zDequeue(Trique *Q);
int      zisElementInQueue(Trique *Q, TriqueEl e);


Trique *zCreateQueue(int N)
{
  Trique *Q;
  if (N < 1)
  {
    printf("\n**Error in zCreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Trique *)malloc(sizeof(Trique));
  if (Q == NULL)
  {
    printf("\n**Error in zCreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (TriqueEl *)malloc(N * sizeof(TriqueEl));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in zCreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;  
  Q->Back = -1;  
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void zDeleteQueue(Trique *Q)
{
  free(Q->Elements);
  free(Q);
}
int zisEmptyQueue(Trique *Q)
{
  return Q->NumElements == 0;
}
int zEnqueue(Trique *Q, TriqueEl e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    TriqueEl *newE = (TriqueEl *)malloc(N * sizeof(TriqueEl));
    if (newE == NULL)
    {
      printf("\n**Error in zEnqueue: malloc failed to allocate\n\n");
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
TriqueEl zDequeue(Trique *Q)
{
  if (zisEmptyQueue(Q))  
  {
    printf("\n**Error in zDequeue: Q is empty?!\n\n");
    exit(-1);
  }
  TriqueEl e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
TriqueEl zFront(Trique *Q)
{
  if (zisEmptyQueue(Q))  
  {
    printf("\n**Error in zDequeue: Q is empty?!\n\n");
    exit(-1);
  }
  TriqueEl e = Q->Elements[Q->Front];
  return e;
}
int zisElementInQueue(Trique *Q, TriqueEl e)
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

int findBottomLeftValue(TreeNode* root) {
    Trique*q=zCreateQueue(1000);;
    Queue*level=CreateQueue(1000);
    zEnqueue(q,root);
    Enqueue(level,0);
    int m=0;
    while(q->NumElements){
        TreeNode *r = zFront(q); 
        zDequeue(q);
        int l = Front(level); 
        Dequeue(level);
        if(r->left) {
            zEnqueue(q,r->left);
            Enqueue(level,l+1);
        }
        if(r->right){
            zEnqueue(q,r->right);
            Enqueue(level,l+1);
        }
        if(l > m){
            m = l;
            root = r;
        }
    }
    return root->val;
}






























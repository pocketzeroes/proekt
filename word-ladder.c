#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

typedef char* QueueElementType;
typedef struct QueueS
{
  QueueElementType  *Elements;
  int  Front;       
  int  Back;        
  int  size; 
  int  Capacity;    
} Queue;

Queue*newQueue(int N)
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
  Q->size = 0;
  Q->Capacity = N;
  return Q;
}
int empty(Queue *Q)
{
  return Q->size == 0;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->size == Q->Capacity)  
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
    for (n = 0; n < Q->size; ++n)
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
  Q->Elements[Q->Back] = strdup(e);
  Q->size++;
  return 1;
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q)) 
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity) 
    Q->Front = 0;
  Q->size--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q)) 
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}

bool differOne(char*s1, char*s2) {
    int cnt = 0;
    for (size_t i = 0; s1[i]; ++i) {
        if (s1[i] != s2[i]) {
            ++cnt;
            if (cnt > 1)return false;
        }
    }
    return cnt == 1;
}
int ladderLength( char* beginWord, char* endWord, char** wordList,int wordListSz) {
    size_t n = wordListSz;
    Queue*q=newQueue(1024);
    push(q,beginWord);
    int step = 1;
    while (!empty(q)) {
        size_t len = q->size;
        for (size_t i = 0; i < len; ++i) {
            char* t = front(q);
            pop(q);
            if (strcmp(t , endWord)==0)return step;
            for (size_t j = 0; j < wordListSz; ++j) {
                if (wordList[j] != NULL&&differOne(t, wordList[j])) {
                    push(q,wordList[j]);
                    wordList[j] = NULL;
                }
            }
        }
        ++step;
    }
    return 0;
}
#if 0
int main()
{
    char**words=(char**)malloc(6*sizeof(char*));
    words[0]=strdup("hot");
    words[1]=strdup("dot");
    words[2]=strdup("dog");
    words[3]=strdup("lot");
    words[4]=strdup("log");
    words[5]=strdup("cog");
    char*w1=strdup("hit");
    char*w2=strdup("cog");
    printf( "length: %d", ladderLength(w1, w2, words, 6) );
    return 0;
}
#endif



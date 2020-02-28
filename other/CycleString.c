#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
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
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
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
      printf("\n**Error in push: malloc failed _to allocate\n\n");
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

////////////////////

int main(){
    char*s=getstr();
    int n = strlen(s);
    int cnt[26]; clr(cnt);
    for(int i = 0; i<n; i++)
        cnt[s[i]-'a']++;
    int nonZero = 0;
    for(int i = 0; i<26; i++)
        if(cnt[i])
            nonZero++;
    if(nonZero==1){
        puts("NO");
        return 0;
    }
    if(nonZero>=3){
        Queue*left = newQueue();
        int low = 0;
        while(cnt[low]==0 || cnt[low]>n/2)
            low++;
        int high = 25;
        while(cnt[high]==0 || cnt[high]>n/2)
            high--;
        for(int i = 0; i<26; i++)
            if(i!=low && i!=high){
                for(int j = 0; j<cnt[i]; j++)
                    push(left, (char)('a'+i));
            }
        puts("YES");
        for(int i = 0; i<cnt[low]; i++)
            putchar('a'+low);
        for(int i=cnt[low]; i<n/2; i++){
            putchar(front(left));
            pop(left);
        }
        for(int i=0; i<cnt[high]; i++)
            putchar('a'+high);
        for(int i = cnt[high]; i<n/2; i++){
            putchar(front(left));
            pop(left);
        }
        return 0;
    }
    int low=0;
    while(cnt[low]==0)
        low++;
    int high = 25;
    while(cnt[high]==0)
        high--;
    if(n==2){
        puts("YES");
        putchar('a'+low);
        putchar('a'+high);
        return 0;
    }
    if(cnt[low]==1 || cnt[high] == 1){
        puts("NO");
        return 0;
    }
    if(n>4 && (cnt[low]==2 || cnt[high]==2)){
        puts("NO");
        return 0;
    }
    if(n==4){
        puts("YES");
        putchar('a'+low );
        putchar('a'+low );
        putchar('a'+high);
        putchar('a'+high);
        return 0;
    }
    if(cnt[low]>cnt[high])
        swap(low, high);
    puts("YES");
    putchar('a'+low);
    for(int i=0; i<n/2-1; i++)
        putchar('a'+high);
    for(int i=0; i<cnt[low]-1; i++)
        putchar('a'+low);
    for(int i=0; i<n/2 - (cnt[low]-1); i++)
        putchar('a'+high);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

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
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
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
int empty(Queue *Q)
{
  return Q->NumElements == 0;
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



int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}



////////////////////
enum{ NMAX = 1000 + 5};
vec frq[NMAX];
vec graph[2 * NMAX];
bool freq[NMAX];
int S, T;
int cap[2 * NMAX][2 * NMAX];
Queue*q;
int father[2 * NMAX];
int flow;


void addEdge(int a, int b, int c) {
    cap[a][b] += c;
    graph[a].ptr = pushback(graph[a].ptr, &graph[a].sz ,b);
    graph[b].ptr = pushback(graph[b].ptr, &graph[b].sz ,a);
}
bool bfs(){
    for (int i = 1; i <= T; ++ i)
        father[i] = 0;
    push(q, S);
    while (!empty(q)) {
        int node = front(q);
        pop(q);
        for(int i=0;i<graph[node].sz;i++){int it = graph[node].ptr[i];
            if (!father[it] && cap[node][it] > 0) {
                father[it] = node;
                push(q, it);
            }
        }
    }
    return father[T];
}
void dinic() {
    while (bfs()){
        for(int i=0;i<graph[T].sz;i++){int it = graph[T].ptr[i];
            if (father[it] && cap[it][T] > 0) {
                int node = it;
                int minimum = cap[it][T];
                while (node != S) {
                    minimum = min(minimum, cap[father[node]][node]);
                    node = father[node];
                }
                flow += minimum;
                cap[it][T] -= minimum;
                cap[T][it] += minimum;
                node = it;
                while (node != S) {
                    cap[father[node]][node] -= minimum;
                    cap[node][father[node]] += minimum;
                    node = father[node];
                }
            }
        }
    }
}
int main() {
    q=CreateQueue(1024);
    int N, K;
    scanf("%d %d", &N, &K);
    int cntOneOk = 0;
    int where    = 0;
    for (int i = 1; i <= N; ++ i) {
        int L;
        scanf("%d", &L);
        int v[L+1];
        for (int j = 0; j < L; ++ j)
            scanf("%d", &v[j]);
        int oneOk = false;
        if( L==0 )
            oneOk = true;
        else if (v[0] == 1)
            oneOk = true;
        else {
            oneOk = true;
            for (int j = 1; j < L; ++ j)
                if (v[j] == 1) {
                    oneOk = false;
                    break;
                }
        }
        if (oneOk)
            ++ cntOneOk;
        else{
            memset(freq, 0, sizeof freq);
            for (int j = 1; j < L; ++ j)
                freq[v[j]] = 1;
            ++ where;
            for (int j = 1; j <= K; ++ j)
                if (!freq[j])
                    frq[where].ptr=pushback(frq[where].ptr, &frq[where].sz ,j);
        }
    }
    N = where;
    S = N + K + 1;
    T = N + K + 2;
    for (int i = 1; i <= N; ++ i) {
        addEdge(S, i, 1);
        for(int z=0;z<frq[i].sz;z++){int it = frq[i].ptr[z];
            addEdge(i, N + it, 1);
        }
    }
    for (int i = N + 1; i <= N + K; ++ i)
        addEdge(i, T, 0);
    bfs();
    int old = 0;
    for (int sup = 0; ; ++ sup) {
        int atMost = cntOneOk + sup - 1;
        if (atMost < 0)
            continue ;
        for(int i=0;i<graph[T].sz;i++){int it = graph[T].ptr[i];
            cap[it][T] += atMost - old;
        }
        dinic();
        if (flow == N) {
            printf("%d\n", sup);
            return 0;
        }
        old = atMost;
    }
    return 0;
}




















































#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

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
/////////////////////////////
int dx[5]={ 0, 0, 0, -1, 1 };
int dy[5]={ 0, -1, 1, 0, 0 };
enum{ INF = 1000000000,
     MAXV = 1000100,
     MAXE = 10001000};
int V, E, source, sink, count;
int head[MAXV];
int temp[MAXV];
int tail[MAXE];
int prev[MAXE];
int flow[MAXE];
int cap [MAXE];
int dist[MAXV];

bool bfs();
int dfs(int s, int f);

void addEdge(int s, int t, int forward, int backward){
  tail[count] = t;
  cap[count]  = forward;
  flow[count] = 0;
  prev[count] = head[s];
  head[s]     = count++;
  tail[count] = s;
  cap[count]  = backward;
  flow[count] = 0;
  prev[count] = head[t];
  head[t]     = count++;
}
int getMaxFlow(){
  int flow = 0;
  while (bfs()) {
    for (int i = 0; i < V; i++)
      temp[i] = head[i];
    while (true) {
      int augFlow = dfs(source, INF);
      if (augFlow == 0)
        break;
      flow += augFlow;
    }
  }
  return flow;
}
bool bfs(){
  fill(dist, MAXV, -1);
  dist[source] = 0;
  Queue*que = newQueue();
  push(que, source);
  while(!empty(que)){
    int s = pop(que);
    for(int e = head[s]; e >= 0; e = prev[e]){
      int t = tail[e];
      if(dist[t] == -1 && flow[e] < cap[e]){
        dist[t] = dist[s] + 1;
        push(que, t);
      }
    }
  }
  return dist[sink] >= 0;
}
int dfs(int s, int f){
  if (s == sink)
    return f;
  for (int e = temp[s]; e >= 0; temp[s] = e = prev[e]) {
    int t = tail[e];
    if (dist[t] == dist[s] + 1 && flow[e] < cap[e]) {
      int df = dfs(t, fmin(f, cap[e] - flow[e]));
      if (df > 0) {
        flow[e] += df;
        flow[e ^ 1] -= df;
        return df;
      }
    }
  }
  return 0;
}
int main(){
  do{
    int n     = in_nextInt();
    int cows  = in_nextInt();
    int hours = in_nextInt();
    int height[n][n];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        height[i][j] = in_nextInt();
    int nsqr = n * n;
    V = nsqr * (hours + 1) * 2 + 2;
    E = 10 * V;
    source = V - 2;
    sink = V - 1;
    fill(head, MAXV, -1);
    count = 0;
    for (int i = 0; i < cows; i++) {
      int cowpos = in_nextInt() * n + in_nextInt();
      addEdge(source, cowpos * 2, 1, 0);
      addEdge(cowpos * 2, cowpos * 2 + 1, 1, 0);
    }
    for (int hour = 0; hour < hours; hour++) {
      int level = in_nextInt();
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
          int oldpos = (hour * nsqr + i * n + j) * 2;
          for(int k = 0; k < 5; k++){
            int x = i + dx[k];
            int y = j + dy[k];
            int newpos = ((hour + 1) * nsqr + x * n + y) * 2;
            if (0 <= x && x < n && 0 <= y && y < n && height[x][y] > level)
              addEdge(oldpos + 1, newpos, 1, 0);
          }
          int newpos = ((hour + 1) * nsqr + i * n + j) * 2;
          addEdge(newpos, newpos + 1, 1, 0);
        }
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        int pos = (hours * nsqr + i * n + j) * 2;
        addEdge(pos, pos + 1, 1, 0);
        addEdge(pos + 1, sink, 1, 0);
      }
    printf("%d\n", getMaxFlow());
  }while(0);
  return 0;
}

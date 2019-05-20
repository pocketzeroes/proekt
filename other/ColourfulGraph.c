#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////////
typedef long long ll;
enum{ Maxn=222};
int n,m,K;
int col [Maxn], col2[Maxn];
int done[Maxn], pre [Maxn];
vec G   [Maxn];
vec way[102][102];
int fst[222];

void bfs(int st){
    for(int i=1;i<=n;i++)
        done[i]=i==st?1:0;
    Queue*q = newQueue();
    push(q, st);
    while(!empty(q)){
        int u=front(q);pop(q);
        for(int i=0; i<G[u].sz; i++){
            int v=G[u].ptr[i];
            if(done[v])
                continue;
            done[v]=1;
            pre[v]=u;
            push(q,v);
        }
    }
    for(int i=1;i<=n;i++){
        int u=i;
        way[st][i].sz=0;
        for(;u!=st;u=pre[u])
            way[st][i].ptr=pushback(way[st][i].ptr, &way[st][i].sz, u);
        way[st][i].ptr=pushback(way[st][i].ptr, &way[st][i].sz, st);
        reverse(way[st][i].ptr, 0, way[st][i].sz-1);
    }
}
void pt(){
    for(int i=1; i<=n; i++)
        printf("%d%c",col[i],i==n?'\n':' ');
}
void swp(int st, int ed, int ty){
    vec tmp = way[st][ed];
    for(int i=0;i<tmp.sz-1;i++){
        if(i==tmp.sz-2){
            if(ty)
                col[tmp.ptr[i+1]] = col[tmp.ptr[i]];
            else
                swap(col, tmp.ptr[i+1], tmp.ptr[i]);
        }
        else
            swap(col, tmp.ptr[i], tmp.ptr[i+1]);
        pt();
    }
    for(int i=tmp.sz-2;i>0;i--){
        swap(col, tmp.ptr[i], tmp.ptr[i-1]);
        pt();
    }
}
void solve (){
    for(int i=1;i<=n;i++)
        scanf("%d",col+i), G[i].sz=0;
    for(int i=1;i<=n;i++)
        scanf("%d",col2+i);
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d%d", &u, &v);
        G[u].ptr = pushback(G[u].ptr, &G[u].sz, v);
        G[v].ptr = pushback(G[v].ptr, &G[v].sz, u);
    }
    bool flag=1;
    for(int i=1;i<=n;i++){
        int t=0;
        for(int j=1;j<=n;j++)
            if(col2[i]==col[j]){
                t=1;
                break;
            }
        if(!t){
            flag=0;
            break;
        }
    }
    if(!flag){
        puts("Impossible");
        return;
    }
    pt();
    for(int i=1;i<=n;i++)
        bfs(i);
    memset(fst,0,sizeof fst);
    for(int i=1;i<=n;i++){
        if(!fst[col2[i]]){
            fst[col2[i]]=i;
            if(col[i]==col2[i])
                continue;
            for(int j=1;j<=n;j++){
                if(col[j]==col2[i]){
                    swp(j,i,0);
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]!=col2[i])
            swp(fst[col2[i]],i,1);
    }
}
int main(){
    while(~scanf("%d %d %d", &n, &m, &K))
        solve();
    return 0;
}

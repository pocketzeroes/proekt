#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)

char*s;
int  dist   [51][51][10002], inf =(int)1e9;
bool visited[51][51][10002];
vecp moves  [51][51];

typedef struct{
    int i, j, pos;
}node;
node newnode(int a, int b, int c){
    return(node){a,b,c};
}
#if 1 //que
typedef node QueueElementType;
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

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char*keyboard[n];
    for(int z=0;z<n;z++)
        keyboard[z]=getstr();
    s = getstr();
    s = concatc(s, '*');
    int pos;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            pos = i;
            while(pos < n && keyboard[i][j] == keyboard[pos][j]) pos++;
            if(pos < n) pb(moves[i][j], newpair(pos,j));
            pos = i;
            while(pos >= 0 && keyboard[i][j] == keyboard[pos][j]) pos--;
            if(pos >= 0) pb(moves[i][j], newpair(pos,j));
            pos = j;
            while(pos < m && keyboard[i][j] == keyboard[i][pos]) pos++;
            if(pos < m) pb(moves[i][j], newpair(i,pos));
            pos = j;
            while(pos >= 0 && keyboard[i][j] == keyboard[i][pos]) pos--;
            if(pos >= 0) pb(moves[i][j], newpair(i,pos));
        }
    }
    Queue*q=newQueue();//of node
    push(q, newnode(0,0,0));
    dist[0][0][0] = 0;
    int i,j, currDist;
    int slen=strlen(s);
    while(!empty(q)){
        i = front(q).i;
        j = front(q).j;
        pos = front(q).pos; pop(q);
        currDist = dist[i][j][pos];
        if(pos == slen){
            printf("%d\n", currDist);
            break;
        }
        if(keyboard[i][j] == s[pos] && !visited[i][j][pos+1]){
            visited[i][j][pos+1] = true;
            push(q, newnode(i,j,pos+1));
            dist[i][j][pos+1] = currDist + 1;
        }
        for(int z=0;z<moves[i][j].sz;z++){pair*move = &moves[i][j].ptr[z];
            if(!visited[move->first][move->second][pos]){
                push(q, newnode(move->first, move->second, pos));
                visited[move->first][move->second][pos] = true;
                dist[move->first][move->second][pos] = currDist + 1;
            }
        }
    }
    return 0;
}

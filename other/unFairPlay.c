#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

ll**newmat(ll x, ll y){
  ll**rv = calloc(x, sizeof(ll*));
  for(ll i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(ll));
  return rv;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

#if 1 //queueue
typedef ll QueueElementType;
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

///////////////////////////
int nbrsSz;

bool BFS(ll**costs, int numNodes, vecl*nbrs, int*backtrack, ll start, ll end){
    bool visited[numNodes]; clr(visited);
    Queue*unvisited = newQueue();//of ll
    visited[start] = 1;
    push(unvisited, start);
    while(!empty(unvisited)){
        int node = front(unvisited); pop(unvisited);
        for(int i=0; i<nbrs[node].sz; i++){
            ll neighbour = nbrs[node].ptr[i];
            if(costs[node][neighbour] > 0 && !visited[neighbour] && node != neighbour){
                push(unvisited, neighbour);
                backtrack[neighbour] = node;
                visited  [neighbour] = 1;
                if(neighbour == end)
                    return 1;
            }
        }
    }
    return 0;
}
ll fordFulkersson(ll**costs, vecl*nbrs, int numNodes, int start, int end){
    int backtrack[numNodes]; fill(backtrack, numNodes, -1);
    ll  totalFlow = 0;
    while(BFS(costs, numNodes, nbrs, backtrack, start, end)){
        ll flow = LLONG_MAX;
        ll cur  = end;
        while(backtrack[cur] != -1){
            if(flow > costs[backtrack[cur]][cur])
               flow = costs[backtrack[cur]][cur];
            cur = backtrack[cur];
        }
        cur = end;
        while(backtrack[cur] != -1){
            costs[backtrack[cur]][cur] -= flow;
            costs[cur][backtrack[cur]] += flow;
            cur = backtrack[cur];
        }
        totalFlow += flow;
    }
    return totalFlow;
}
int main(){
    int teams, matchesLeft;
    while(1){
        scanf("%d", &teams);
        if(teams == -1)
            return 0;
        scanf("%d", &matchesLeft);
        vec initialTeamScores = newVec();
        for(int i=0; i<teams; i++){
            int teamScore;
            scanf("%d", &teamScore);
            pb(initialTeamScores, teamScore);
        }
        nbrsSz = teams + matchesLeft + 2;
        int g0sz = teams+matchesLeft+2;
        ll**graph = newmat(nbrsSz, g0sz);
        ll  iSink = teams + matchesLeft + 1;
        vecl nbrs[nbrsSz]; clr(nbrs);
        for(int i=1; i<matchesLeft+1; i++)
            graph[0][i] = 2;
        vecp matches = newVecP();
        int matchesWithoutOurTeamInIt = 0;
        int ourTeamExtraPoints        = 0;
        for(ll i=1; i<matchesLeft+1; i++){
            int team1, team2;
            scanf("%d", &team1);
            scanf("%d", &team2);
            pbp(matches, newpair(team1, team2));
            if(team1 == teams || team2 == teams)
                ourTeamExtraPoints += 2;
            else{
                matchesWithoutOurTeamInIt += 2;
                graph[i][matchesLeft+team1] = 999;
                graph[i][matchesLeft+team2] = 999;
                pbl(nbrs[0], i);
                pbl(nbrs[i], 0);
                pbl(nbrs[i], matchesLeft+team1);
                pbl(nbrs[i], matchesLeft+team2);
                pbl(nbrs[matchesLeft+team1], i);
                pbl(nbrs[matchesLeft+team2], i);
            }
        }
        bool quit = false;
        int ourTeamFinalScore = initialTeamScores.ptr[initialTeamScores.sz-1]+ourTeamExtraPoints;
        for(int i=0; i<initialTeamScores.sz-1; i++){
            if(ourTeamFinalScore <= initialTeamScores.ptr[i]){
                puts("NO");
                quit = true;
                break;
            }
        }
        if(!quit){
            for(ll i=matchesLeft+1; i<matchesLeft+teams+1; i++){
                int capacity = ourTeamFinalScore - initialTeamScores.ptr[i-matchesLeft-1]-1;
                graph[i][iSink] = capacity;
                pbl(nbrs[i    ], iSink);
                pbl(nbrs[iSink], i);
            }
            int  numNodes = teams + matchesLeft + 2;
            ll flow = fordFulkersson(graph, nbrs, numNodes, 0, numNodes-1);
            ll** result = graph;
            ll   edgesUsed = 0;
            int  sum       = 0;
            for(int k=1; k<1+matchesLeft; k++)
                sum += result[k][0];
            if(sum != matchesWithoutOurTeamInIt)
                puts("NO");
            else{
                for(int i=0; i<matches.sz; i++){
                    pair match = matches.ptr[i];
                    if(match.first == teams)
                        printf("0 ");
                    else if(match.second == teams)
                        printf("2 ");
                    else{
                        int matchIndex = i + 1;
                        int teamIndex1 = matchesLeft + match.first;
                        int teamIndex2 = matchesLeft + match.second;
                        if(result[teamIndex1][matchIndex] == 2)
                            printf("0 ");
                        else if(result[teamIndex2][matchIndex] == 2)
                            printf("2 ");
                        else
                            printf("1 ");
                    }
                }
                puts("");
            }
        }
    }
    return 0;
}

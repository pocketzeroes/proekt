#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
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
enum{ MAXN = 1000000};
#define time first
#define nextHouse second

typedef long long ll;

vecp graph[MAXN];
int K[MAXN], nearestInK[MAXN];
int branch1[MAXN], branch2[MAXN];

ll furthest[MAXN];
ll maxTime1[MAXN], maxTime2[MAXN];
ll distToK [MAXN];
ll totalTimeInK;

int findK(int x, int previousHouse){
  int connected = 0;
  int d = graph[x].sz;
  for (int i=0; i<d; i++){
    int nextHouse = graph[x].ptr[i].nextHouse;
    if (nextHouse == previousHouse)
      continue;
    if (findK(nextHouse, x) == 1){
      K[x] = connected = 1;
      totalTimeInK += graph[x].ptr[i].time;
    }
  }
  if (K[x] == 1)
    connected = 1;
  return connected;
}
ll calcMaxBranches(int x, int previousHouse, ll currentPath){
  int d = graph[x].sz;
  for (int i=0; i<d; i++){
    int nextHouse = graph[x].ptr[i].nextHouse;
    if (previousHouse == nextHouse || K[nextHouse] != 1)
      continue;
    int time = graph[x].ptr[i].time;
    ll currentTime = time + calcMaxBranches(nextHouse, x, currentPath + time);
    if (currentTime > maxTime1[x]){
      maxTime2[x] = maxTime1[x]; branch2[x] = branch1[x];
      maxTime1[x] = currentTime; branch1[x] = i;
    }
    else if (currentTime > maxTime2[x]){
      maxTime2[x] = currentTime; branch2[x] = i;
    }
  }
  return maxTime1[x];
}
void calcFurthest(int x, int previousHouse, ll currentPath){
  furthest[x] = max(currentPath, maxTime1[x]);
  int d = graph[x].sz;
  for (int i=0; i<d; i++){
    int nextHouse = graph[x].ptr[i].nextHouse;
    if (previousHouse == nextHouse || K[nextHouse] != 1)
      continue;
    int time = graph[x].ptr[i].time;
    if (i != branch1[x])
      calcFurthest(nextHouse, x, time + max(currentPath, maxTime1[x]));
    else
      calcFurthest(nextHouse, x, time + max(currentPath, maxTime2[x]));
  }
}
void calcDistToK(int x, int previousHouse, int currentPath, int near){
  distToK[x] = currentPath;
  nearestInK[x] = near;
  int d = graph[x].sz;
  for (int i=0; i<d; i++){
    int nextHouse = graph[x].ptr[i].nextHouse; 
    if (previousHouse == nextHouse) 
      continue;
    int time = graph[x].ptr[i].time;
    if (K[nextHouse] == 1)
      calcDistToK(nextHouse, x, 0, nextHouse);
    else
      calcDistToK(nextHouse, x, time + currentPath, near);
  }
}
int main(){
  int n, k;
  scanf ("%d%d", &n, &k);
  for (int i=0; i<n-1; i++){
    int a, b, c;
    scanf ("%d%d%d", &a, &b, &c);
    a--, b--;
    graph[a].ptr = pushbackP(graph[a].ptr, &graph[a].sz, newPair(c, b));
    graph[b].ptr = pushbackP(graph[b].ptr, &graph[b].sz, newPair(c, a));
  }
  int a;
  for (int i=0; i<k; i++){
    scanf ("%d", &a);
    a--;
    K[a] = 1;
  }
  findK(a, -1);
  int beginning;
  for (int i=0; i<n; i++)
    if (K[i] == 1){
      beginning = i;
      break;
    }
  calcMaxBranches(beginning, -1, 0);
  calcFurthest   (beginning, -1, 0);
  calcDistToK    (beginning, -1, 0, beginning);
  for (int i=0; i<n; i++)
    printf ("%lld\n", distToK[i] + 2*totalTimeInK - furthest[nearestInK[i]]);
  return 0;
}

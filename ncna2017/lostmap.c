#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int minKey(int *key, int* mstSet, int V)
{ 
  int v, min = INT_MAX, min_index;
  for (int v = 0; v < V; v++)
    if (!mstSet[v] && key[v] < min)
      min = key[v], min_index = v;
  return min_index;
}
int *primMST(int **graph, int V)
{
  int *parent = malloc(sizeof(int)*V);
  int *key = malloc(sizeof(int)*V);
  int *mstSet = malloc(sizeof(int)*V);
  int i,u,v;
  for (i = 0; i < V; i++)
    {
      key[i] = INT_MAX;
      mstSet[i] = 0;   
    }
  key[0] = 0;    
  parent[0] = -1;
  for (i = 0; i < V-1; i++)
    {
      u = minKey(key, mstSet, V);
      mstSet[u] = 1; 
      for (v = 0; v < V; v++)
        if (graph[u][v] && !mstSet[v] && graph[u][v] <  key[v])
          parent[v]  = u, key[v] = graph[u][v];
    }
  free(key);
  free(mstSet);
  return parent;
}
int main()
{
  int i,j,N;
  int **cost,*parent;
  srand(time(NULL));
  scanf("%d",&N);
  cost = malloc(sizeof(int*)*N);
  for(i=0;i<N;i++)
    {
      cost[i] = malloc(sizeof(int)*N);
      for(j=0;j<N;j++)
        scanf("%d",&(cost[i][j]));
      if(cost[i][j] == 0)
        cost[i][j] = INT_MAX;
    }
  parent=primMST(cost,N);
  for (i = 1; i < N; i++)
    if((rand() >> 12)&1)
      printf("%d %d\n", i+1, parent[i]+1);
    else
      printf("%d %d\n", parent[i]+1, i+1);
  return 0;
}

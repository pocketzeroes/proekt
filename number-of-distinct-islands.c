#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
typedef int SetElementType;
typedef struct Set
{
  SetElementType  *Elements;
  int  NumElements;
  int  Capacity;
} Set;
Set *CreateSet(int N);
void DeleteSet(Set *S);
int  isEmptySet(Set *S);
int  AddToSet(Set *S, SetElementType e);
int  isElementInSet(Set *S, SetElementType e);
Set *CreateSet(int N)
{
  Set *S;
  if (N < 1)
  {
    printf("\n**Error in CreateSet invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  S = (Set *)malloc(sizeof(Set));
  if (S == NULL)
  {
    printf("\n**Error in CreateSet: malloc failed to allocate\n\n");
    exit(-1);
  }
  S->Elements = (SetElementType *)malloc(N * sizeof(SetElementType));
  if (S->Elements == NULL)
  {
    printf("\n**Error in CreateSet: malloc failed to allocate\n\n");
    exit(-1);
  }
  S->NumElements = 0;
  S->Capacity = N;
  return S;
}
void DeleteSet(Set *S)
{
  free(S->Elements);
  free(S);
}
int isEmptySet(Set *S)
{
  return S->NumElements == 0;
}
int AddToSet(Set *S, SetElementType e)
{
  if (isElementInSet(S, e))
    return 1;
  if (S->NumElements == S->Capacity)
  {
    int N = 2 * S->Capacity;
    SetElementType *newE = (SetElementType *)malloc(N * sizeof(SetElementType));
    if (newE == NULL)
    {
      printf("\n**Error in AddToSet: malloc failed to allocate\n\n");
      exit(-1);
    }
    int  i;
    for (i = 0; i < S->NumElements; ++i)
    {
      newE[i] = S->Elements[i];
    }
    free(S->Elements);
    S->Elements = newE;
    S->Capacity = N;
  }
  int  i;
  for (i = 0; i < S->NumElements; ++i)
  {
    if (e == S->Elements[i])
      return 1;
    if (e < S->Elements[i])
      break;
  }
  int  j;
  for (j = S->NumElements; j > i; --j)
    S->Elements[j] = S->Elements[j - 1];
  S->Elements[i] = e;
  S->NumElements++;
  return 1;
}
int isElementInSet(Set *S, SetElementType e)
{
  int low = 0;
  int high = S->NumElements - 1;
  while (low <= high)
  {
    int mid = low + ((high - low) / 2);
    if (e == S->Elements[mid])
      return mid + 1;
    else if (e < S->Elements[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }
  return 0;
}
int RemoveFromSet(Set *S, SetElementType e)
{
  if(!isElementInSet(S, e))
    return 1;
  int  i;
  for (i = 0; i < S->NumElements; ++i)
  {
    if (e == S->Elements[i])
      break;
  }
  int j;
  for(j = i; j < S->NumElements; j++)
    S->Elements[j] = S->Elements[j + 1];
  S->NumElements--;
  return 0;
}

//////////////////////
int**grid;
int grid_length;
int grid0length;
int dfs(int i, int j){
    int t = 1;
    grid[i][j] = 0;
    if(i>0             && grid[i-1][j]==1) t +=  19*dfs(i-1, j);
    if(i<grid_length-1 && grid[i+1][j]==1) t +=  31*dfs(i+1, j);
    if(j>0             && grid[i][j-1]==1) t +=  97*dfs(i, j-1);
    if(j<grid0length-1 && grid[i][j+1]==1) t += 193*dfs(i, j+1);
    return t;
}
int numDistinctIslands(int**g, int gridSz, int grid0sz){
    grid = g;
    grid_length = gridSz;
    grid0length = grid0sz;
    Set*visited = CreateSet(1024);
    int t = 0;
    for(int i=0; i<gridSz; ++i) {
        for(int j=0; j< grid0sz; ++j) {
            if(grid[i][j]==1) {
                int c=dfs(i, j);
                if(!isElementInSet(visited, c)) {
                    AddToSet(visited, c);
                    ++t;
                }
            }
        }
    }
    return t;
}











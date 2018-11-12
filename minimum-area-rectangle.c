int min(int a,int b){return a<b?a:b;}
#if 1 // set
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
Set *newSet(int N);
void DeleteSet(Set *S);
int  isEmptySet(Set *S);
int  AddToSet(Set *S, SetElementType e);
int  isElementInSet(Set *S, SetElementType e);



Set *newSet(int N)
{
  Set *S;
  if (N < 1)
  {
    printf("\n**Error in newSet invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  S = (Set *)malloc(sizeof(Set));
  if (S == NULL)
  {
    printf("\n**Error in newSet: malloc failed to allocate\n\n");
    exit(-1);
  }
  S->Elements = (SetElementType *)malloc(N * sizeof(SetElementType));
  if (S->Elements == NULL)
  {
    printf("\n**Error in newSet: malloc failed to allocate\n\n");
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

#define erase     RemoveFromSet
#define contains  isElementInSet
#define add       AddToSet
#define empty     isEmptySet


#endif

int minAreaRect(int**points, int pointsSz, int*points0sz){
    Set*pointSet = newSet(1024);
    for(int i=0; i<pointsSz; i++){int*point = points[i];
        add(pointSet, 40001*point[0]+point[1]);
    }
    int ans = INT_MAX;
    for(int i=0; i<pointsSz; ++i)
        for(int j=i+1; j<pointsSz; ++j){
            if(points[i][0] != points[j][0]&&
               points[i][1] != points[j][1]  ){
                if(contains(pointSet, 40001*points[i][0] + points[j][1])&&
                   contains(pointSet, 40001*points[j][0] + points[i][1])  ){
                    ans = min(ans, abs(points[j][0] - points[i][0]) *
                                   abs(points[j][1] - points[i][1]));
                }
            }
        }
    return ans < INT_MAX ? ans : 0;
}

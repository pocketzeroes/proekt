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

/////
int sum[3000];

bool splitArray(int* nums, int numsSize){
  int i,j,k,n,sum1,sum2,b1;
  n=numsSize;
  sum[0]=0;
  for(i=0;i<n;i++)
    sum[i+1]=sum[i]+nums[i];
  b1=0;
  for(j=3;j<n-3;j++)
  {
    Set*st=CreateSet(1024);
    for (i=1;i+1<j;i++)
    {
      sum1=sum[i];
      sum2=sum[j]-sum[i+1];
      if (sum1==sum2) 
        AddToSet(st,sum1);
    }
    for (k=j+2;k+1<n;k++)
    {
      sum1=sum[k]-sum[j+1];
      sum2=sum[n]-sum[k+1];
      if (sum1==sum2)
        if( isElementInSet(st,sum1) )
        {
          b1=1;break;
        }
    }
    if (b1==1) 
      break;
    DeleteSet(st);
  }
  if (b1==1) 
    return true;
  else 
    return false;
}



















































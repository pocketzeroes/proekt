#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
typedef long long ll;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

/////set/////
#if 1
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








#endif
/////set/////

void fill(int*a,int sz,int val){
  for(int i=0;i<sz;i++)a[i]=val;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct v1{
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct v2{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int max_element(int*arr,int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}

///////
int*BipartiteMatch(vec2d mat){
  int max_item = -1;
  int*fmat = calloc(mat.sz, sizeof(int)); fill(fmat, mat.sz, -1);
  int seen[mat.sz]; fill(seen, mat.sz, -1);
  int prev[mat.sz]; memset(prev, 0, sizeof(prev));
  for (int i = 0; i < mat.sz; i++) 
    if (mat.ptr[i].sz)
      max_item = max(max_item, max_element(mat.ptr[i].ptr, mat.ptr[i].sz));
  int bmat[max_item+1]; fill(bmat, max_item+1, -1);
  for (int i = 0; i < mat.sz; i++){
    vec q = newVec(); q.ptr = pushback(q.ptr, &q.sz, i);
    seen[i] = i; 
    prev[i] = -1;
    int x, y;
    while(q.sz>0){
      x = q.ptr[q.sz-1];
      q.sz--;
      for(int z=0; z < mat.ptr[x].sz; z++){int it = mat.ptr[x].ptr[z];
        int bm = bmat[it];
        if (bm == -1){
          y = it;
          goto found_match;
        }
        if (seen[bm] < i){
          seen[bm] = i; 
          prev[bm] = x;
          q.ptr = pushback(q.ptr, &q.sz, bm);
        }
      }
    }
    continue;
found_match:
    while (x != -1) {
      bmat[y] = x;
      SWAP(y, fmat[x]);
      x = prev[x];
    }
  }
  return fmat;
}
int main() {
  int X, Y;
  while(scanf("%d %d", &Y, &X)==2){
    int g[Y][X];
    int xh[X];memset(xh, 0, sizeof(xh)); 
    int yh[Y];memset(yh, 0, sizeof(yh));
    ll ret = 0;
    for (int y = 0; y < Y; y++)
      for (int x = 0; x < X; x++) {
        scanf("%d", &g[y][x]);
        ret  += max(0, g[y][x] - 1);
        xh[x] = max(xh[x], g[y][x]);
        yh[y] = max(yh[y], g[y][x]);
      }
    Set*seen = CreateSet(1024);
    for(int x = 0; x < X; x++) 
      if (xh[x] > 1) {
        ret -= xh[x]-1;
        if( isElementInSet(seen, xh[x]) ) 
          continue;
        AddToSet(seen, xh[x]);
        vec2d mat = newVec2d();
        for (int x2 = 0; x2 < X; x2++) 
          if (xh[x2] == xh[x]) {
            mat.ptr = pushback2d(mat.ptr, &mat.sz ,newVec());
            for (int y2 = 0, yi = 0; y2 < Y; y2++) 
              if (yh[y2] == xh[x]) {
                if (g[y2][x2])
                  mat.ptr[mat.sz-1].ptr = pushback(mat.ptr[mat.sz-1].ptr, &mat.ptr[mat.sz-1].sz ,yi);
                yi++;
              }
          }
        int*v = BipartiteMatch(mat);
        for (int i = 0; i < mat.sz; i++) 
          if (v[i] != -1)
            ret += xh[x]-1;
      }
    for (int y = 0; y < Y; y++) 
      ret -= max(0, yh[y]-1);
    printf("%lld\n", ret);
  }
}





















































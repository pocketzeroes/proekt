#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TREE_DEBUG 0
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
typedef struct pair_S{
    ll first;
    ll second;
}pair;
pair newPair(ll a, ll b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#if 1// set
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

typedef ll SetElementType;
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
    return 0;
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

#define erase  RemoveFromSet
#define find   isElementInSet
#define insert AddToSet
#define empty  isEmptySet




#endif

#if TREE_DEBUG
struct TreeNode {
    int              val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
typedef struct TreeNode TreeNode;
TreeNode**pushback(TreeNode**array, int*size, TreeNode*value) {
    TreeNode**output = resizeArray(array, TreeNode*, *size + 1);
    output[(*size)++] = value;
    return output;
}
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}
//////////////////
Set*   set;
Set*   done;
TreeNode**ret;
int      retSz;
pair dfs(TreeNode*root){
    if(root == NULL)
        return newPair(0, 0);
    pair hl = dfs(root->left );
    pair hr = dfs(root->right);
    hl.first += 31; hl.second++;
    hr.first += 31; hr.second++;
    ll h0 = root->val * 1000000009L + hl.first * hl.first;
    h0 = h0 * 1000000009L + hr.first * hr.first;
    ll dh = max(hl.second, hr.second);
    ll h = h0*1000000007L + dh;
    if(!insert(set, h) && !find(done, h)){
        ret = pushback(ret, &retSz, root);
        insert(done, h);
    }
    return newPair(h0, dh);
}
TreeNode**findDuplicateSubtrees(TreeNode*root, int*rsz){
    set  = CreateSet(1024);
    done = CreateSet(1024);
    ret  = NULL;
    retSz=0;
    dfs(root);
   *rsz=   retSz;
    DeleteSet(set);
    DeleteSet(done);
    return ret;
}
#if TREE_DEBUG
int main(){
    ;
}
#endif

















































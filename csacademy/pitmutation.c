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

/////////////////

enum{ N   =     310    };
enum{ mod =(int)1e9 + 7};
Set* p1;
Set* p2;
Set* q1;
Set* q2;
int dp1[N] , dp2[N], fact[N];
int comb[N][N];


int main(){
    p1=CreateSet(1024);
    p2=CreateSet(1024);
    q1=CreateSet(1024);
    q2=CreateSet(1024);
    int n, S;
    scanf("%d %d", &n, &S);
    for(int i=1; i<=n; i++)
        AddToSet(p2, i), AddToSet(q2, i);
    for(int i=1; i<=n; i++){
        int t;
        scanf("%d", &t);
        if(t != 0)
            AddToSet(p1, t), RemoveFromSet(p2, t);
    }
    for(int i=1; i<=n; i++){
        int t;
        scanf("%d", &t);
        if(t != 0)
            AddToSet(q1, t) , RemoveFromSet(q2, t);
    }
    comb[0][0] = 1;
    for(int i=1; i<N; i++){
        comb[i][0] = comb[i][i] = 1;
        for(int j=1; j<i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }
    fact[0] = 1;
    for(int i=1; i<N; i++)
        fact[i] = (1LL * fact[i - 1] * i) % mod;
    dp1[0] = 1;
    
    for(int i=0;i<p2->NumElements; i++){int x=p2->Elements[i];//for(auto x : p2){
        int deg = 0;
        for(int i=0;i<q1->NumElements; i++){int y=q1->Elements[i];// for(auto y : q1)
            if(x > y)
                deg++;
        }
        for(int i=deg; i>=0; i--){
            if(i > 0)
                dp1[i] = dp1[i] + (1LL * dp1[i - 1] * (deg - i + 1)) % mod, dp1[i] %= mod;
            else dp1[i] = dp1[i];
        }
    }
    int sz = p2->NumElements;
    for(int j=0; j<=sz; j++)
        dp1[j] = (1LL * dp1[j] * fact[sz - j]) % mod;
    for(int j=sz; j>=0; j--)
        for(int k=j+1; k<=sz; k++)
            dp1[j] = (dp1[j] + mod - (1LL * dp1[k] * comb[k][j]) % mod) % mod;
    dp2[0] = 1;

    for(int i=0;i<p1->NumElements; i++){int x=p1->Elements[i];//for(auto x : p1){
        int deg = 0;
        for(int i=0;i<q2->NumElements; i++){int y=q2->Elements[i];//for(auto y : q2)
            if(x > y)
                deg++;
        }
        for(int i=deg; i>=0; i--){
            if(i > 0)
                dp2[i] = dp2[i] + (1LL * dp2[i - 1] * (deg - i + 1)) % mod , dp2[i] %= mod;
            else
                dp2[i] = dp2[i];
        }
    }
    sz = p1->NumElements;
    for(int j=0; j<=sz; j++)
        dp2[j] = (1LL * dp2[j] * fact[sz - j]) % mod;
    for(int j=sz; j>=0; j--)
        for(int k=j+1; k<=sz; k++)
            dp2[j] = (dp2[j] + mod - (1LL * dp2[k] * comb[k][j]) % mod) % mod;
    int ans = 0;
    for(int i=0; i<=S; i++)
        ans += (1LL * dp1[i] * dp2[S - i]) % mod, ans %= mod;
    printf("%d\n", ans);
}




























































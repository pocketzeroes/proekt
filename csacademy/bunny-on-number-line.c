#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>
#ifdef _WIN32
  #define inline static
#endif



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

#define erase  RemoveFromSet
#define find   isElementInSet
#define insert AddToSet
#define empty  isEmptySet
#define count  isElementInSet




#endif

typedef long long ll;
typedef unsigned long long ull;

enum{ N   = 200        };
enum{ MOD =(int)1e9 + 7};
enum{ WEW =(ull)17.4e18};
int sz;
int mat[N][N] = {},
    res[N][N] = {},
    tmp[N][N] = {},
    tr [N][N];
int vec[N];
int k, m, n;
int x[100];
int p[100];



void matMul(int a[N][N], int b[N][N]){
    for (int i = 0; i < (int)(sz); ++i)
        for (int j = 0; j < (int)(sz); ++j) {
            tr[i][j] = b[j][i];
        }
    for (int i = 0; i < (int)(sz); ++i)
        for (int j = 0; j < (int)(sz); ++j) {
            ull res = 0;
            for (int k = 0; k < (int)(sz); ++k) {
                res += (ull) a[i][k] * tr[j][k];
                if (res > WEW)
                    res %= MOD;
            }
            tmp[i][j] = res % MOD;
        }
    for (int i = 0; i < (int)(sz); ++i)
        for (int j = 0; j < (int)(sz); ++j)
            a[i][j] = tmp[i][j];
}
void matPow(ll p){
    for (int i = 0; i < (int)(sz); ++i)
        for (int j = 0; j < (int)(sz); ++j)
            res[i][j] = i == j;
    while (p){
        if (p & 1)
            matMul(res, mat);
        p >>= 1;
        if (p)
            matMul(mat, mat);
    }
}
void vecMul(){
    int nvec[sz];
    for (int j = 0; j < (int)(sz); ++j) {
        ull res = 0;
        for (int i = 0; i < (int)(sz); ++i) {
            res += (ull) vec[i] * mat[i][j];
            if (res > WEW)
                res %= MOD;
        }
        nvec[j] = res % MOD;
    }
    for (int i = 0; i < (int)(sz); ++i)
        vec[i] = nvec[i];
}
inline void modAdd(int*x, int y){
    (*x) += y;
    if(*x >= MOD)
      (*x)-= MOD;
}
ll get2(int x){
    return (ll)x * (x + 1) / 2;
}
int main(){
    scanf("%d %d %d", &k, &m, &n);
    for (int i = 0; i < (int)(k); ++i)
        scanf("%d", x + i);
    if (x[0] > m){
        puts("0");
        return 0;
    }
    for (int i = k - 1; i > 0; --i)
        x[i] -= x[i - 1];
    for (int i = 1; i < k; ++i)
        if (x[i] > m) {
            k = i;
            break;
        }
    int base = m - x[0] + 1;
    int base2 = ((get2(m) - get2(x[0] - 1)) % MOD + MOD) % MOD;
    for (int i = 1; i < k; ++i) {
        int j = p[i - 1];
        while (j > 0 && x[i] != x[j])
            j = p[j - 1];
        if (x[i] == x[j] || (j == 0 && x[i] >= x[j]))
            ++j;
        p[i] = j;
    }
    sz = 2 * k;
    for (int i = 0; i < (int)(k); ++i) {
        Set*used = CreateSet(1024);
        if (i != k - 1) {
            ++mat[i + 1][i];
            ++mat[k + i + 1][k + i];
            modAdd(&mat[i + 1][k + i], x[i + 1]);
            insert(used, x[i + 1]);
        }
        for (int j = p[i] - 1; j >= 0; j = p[j] - 1) {
            if(!count(used, x[j + 1])){
                ++mat[j + 1][i];
                ++mat[k + j + 1][k + i];
                modAdd(&mat[j + 1][k + i], x[j + 1]);
                insert(used, x[j + 1]);
            }
        }
        int ways = base;
        int ways2 = base2;
        for(int z=0; z<used->NumElements;z++){ int val = used->Elements[z];
            if (val >= x[0]) {
                --ways;
                ways2 -= val;
                if (ways2 < 0)
                    ways2 += MOD;
            }
        }
        modAdd(&mat[0][i]    , ways );
        modAdd(&mat[k][k + i], ways );
        modAdd(&mat[0][k + i], ways2);
        DeleteSet(used);
    }
    matPow(n - 1);
    memcpy(mat, res, sizeof mat);
    for (int i = 0; i < (int)(k); ++i)
        vec[i] = 1;
    vecMul();
    int ans = ((ll)vec[0] * base2 + (ll)vec[k] * base) % MOD;
    printf("%d\n", ans);
    return 0;
}























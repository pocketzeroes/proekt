#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int compP( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}
pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}

//beginSet
typedef __int128_t SetElementType;
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
  int j;
  for (j = S->NumElements; j > i; --j)
    S->Elements[j] = S->Elements[j - 1];
  S->Elements[i] = e;
  S->NumElements++;
  return 1;
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
#define PART_BIT 32
__int128_t pack(int d,int c,int b,int a){
    __int128_t p = a;
    p = (p << PART_BIT) | b;
    p = (p << PART_BIT) | c;
    p = (p << PART_BIT) | d;
    return p;
}
int unpack(__int128_t p, int k){
    int n = k * PART_BIT;
    __int128_t mask = INT_MAX;
    mask <<= n;
    return ((p & mask) >> n);
}
//endSet


enum{ NMax = 100005};
int N, M, O[NMax], K, NRC;

int*G  [NMax];int sz1 [NMax];
int*GT [NMax];int sz2 [NMax];
int*GG [NMax];int sz4 [NMax]; 
int*GGT[NMax];int sz5 [NMax];

bool Use  [NMax];
int C     [NMax];
int Degree[NMax], Root;
int Father[NMax];
int Level [NMax];
pair Up   [NMax];
Set*S;
int Poz     [NMax];
bool ok = 1;
int F       [NMax];
int ans = 0;
bool Dead   [NMax];
bool Check  [NMax];
int Arb [4 * NMax], First[NMax], Last[NMax], cnt;
int Lazy[4 * NMax];


void Read()
{
    scanf("%d %d", &N, &M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        scanf("%d %d", &x, &y);
        G [x]=pushback(G [x], sz1+x , y);
        GT[y]=pushback(GT[y], sz2+y , x);
    }
}
void DFP(int Nod)
{
    Use[Nod]=1;
    for(unsigned int i=0; i<sz1[Nod]; i++)
    {
        int Vecin=G[Nod][i];
        if(!Use[Vecin])
            DFP(Vecin);
    }
    O[++K]=Nod;
}
void DFM(int Nod)
{
    Use[Nod]=1;

    C[Nod] = NRC;
    for(unsigned int i=0;i<sz2[Nod]; i++)
        {
            int Vecin=GT[Nod][i];
            if(!Use[Vecin])
                DFM(Vecin);
        }
}
void Kosaraju()
{
    for(int i=1;i<=N;i++)
        {
            if(!Use[i])
                DFP(i);
        }
    memset(Use,0,sizeof(Use));
    for(int i=K;i>=1;i--)
        {
            if(!Use[O[i]])
            {
                NRC++;
                DFM(O[i]);
            }

        }
}
void buildGG()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < sz1[i]; j++)
        {
            int neighb = G[i][j];
            if(C[i] == C[neighb])
                continue;
            int index=C[i];
            GG[index]=pushback(GG[index], sz4+index, C[neighb]);
            int idx=C[neighb];
            GGT[idx]=pushback(GGT[idx],sz5+idx,C[i]);
            Degree[C[neighb]]++;
        }
    }
    for(int i = 1; i <= NRC; i++)
    {
        if(Degree[i] == 0)
            Root = i, Level[Root] = 1;
    }
}
void DFS(int node)
{
    Use[node] = 1;
    First[node] = ++cnt;
    for(int i = 0; i < sz4[node]; i++)
    {
        int neighb = GG[node][i];
        if(Use[neighb] == 1)
            continue;
        Level[neighb] = Level[node] + 1;
        F[neighb] = node;
        for(int j = 0; j < sz5[neighb]; j++)
        {
            if(GGT[neighb][j] == node)
            {
                Father[neighb] = j;
                break;
            }

        }
        DFS(neighb);
    }
    Last[node] = cnt;
}
int DFS2(int node)
{
    Use[node] = 1;
    Up[node].first = Level[node];
    Up[node].second = node;
    for(int i = 0; i < sz5[node]; i++)
    {
        int neighb = GGT[node][i];
        if(i == Father[node])
            continue;
        if(Up[node].first > Level[neighb])
            Up[node] = newPair(Level[neighb], neighb);
    }
    int Max = 0;
    for(int i = 0; i < sz4[node]; i++)
    {
        int neighb = GG[node][i];
        if(Use[neighb] == 1)
            continue;
        Max = max(Max, DFS2(neighb) - 1);
        Up[node] = minP(Up[node], Up[neighb]);
    }
    if(Up[node].first >= Level[node])
        Dead[node] = 1;
    if(Max == 0 && node != Root)
    {
        if(Dead[node] == 1 && node != Root)
            ok = 0;
        ++ans;
        return Level[node] - Up[node].first;
    }
    return Max;
}
void Solve()
{
    while(!isEmptySet(S))
    {
        __int128_t x = S->Elements[ S->NumElements-1];
        RemoveFromSet(S, x);

        int sec = unpack(x, 1);
        if(sec == Root)
            continue;
        if(Dead[sec] == 1)
        {
            ok = 0;
            puts("-1");
            return;
        }
        int node = sec;
        int newN = Up[sec].second;

        __int128_t el = pack(Up[sec].first, Up[sec].second, 0, 0);
        if(isElementInSet(S, el))
            continue;
        AddToSet(S, el);
        ++ans;
    }
    printf("%d\n", ans);
}
void sortTop(int node)
{
    Use[node] = 1;
    for(int i = 0; i < sz4[node]; i++)
    {
        int neighb = GG[node][i];
        if(Use[neighb] == 1)
            continue;
        sortTop(neighb);
    }
    O[++O[0]] = node;
    Poz[node] = O[0];
}
int compare(const void*pa, const void*pb)
{
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a = *ptra;
    int b = *ptrb;
    return (Poz[a] > Poz[b])?-1:1;
}
int main()
{
    Read();
    Kosaraju();
    if(NRC == 1)
    {
        puts("0");
        return 0;
    }
    buildGG();
    memset(Use, 0, sizeof(Use));
    O[0] = 0;
    sortTop(Root);
    for(int i = 1; i <= NRC; i++)
        qsort(GG[i], sz4[i], sizeof(int) , compare);
    memset(Use, 0, sizeof(Use));
    DFS(Root);
    memset(Use, 0, sizeof(Use));
    DFS2(Root);
    if(ok == 0)
    {
        puts("-1");
        return 0;
    }
    printf("%d\n", ans);
    return 0;
}


































































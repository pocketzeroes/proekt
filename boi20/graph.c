#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int*size, pair value){
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
#if 1 //queueue
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed _to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;
  Q->Back = -1;
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed _to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity)
    Q->Back = 0;
  Q->Elements[Q->Back] = e;
  Q->NumElements++;
  return 1;
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif
//////////////////////////
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
//typedef pair<int,int> pii;
//typedef vector<vector<int> > graph;
//const double pi = acos(-1.0);
#define oned(a, x1, x2) { cout << #a << ":"; for(int _i = (x1); _i < (x2); _i++){ cout << " " << a[_i]; } cout << endl; }
#define twod(a, x1, x2, y1, y2) { cout << #a << ":" << endl; for(int _i = (x1); _i < (x2); _i++){ for(int _j = (y1); _j < (y2); _j++){ cout << (_j > y1 ? " " : "") << a[_i][_j]; } cout << endl; } }
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
enum{MAXN = 200005};
int n, m;
vecp g[MAXN];
int vis[MAXN];
int sgn[MAXN];
int val[MAXN];
Queue*Q;
int ans[MAXN];
int cnt;
int comp[MAXN];
int num[MAXN];

void solve(){
    memset(vis,0,sizeof(vis));
    for(int u = 1; u <= n; u++) {
        if(!vis[u]) {
            vis[u] = true;
            sgn[u] = +1;
            val[u] = 0;
            cnt = 0;
            comp[cnt++] = u;
            bool bip = true;
            double x;
            push(Q, u);
            while(!empty(Q)) {
                int v = front(Q); pop(Q);
                for(size_t i = 0; i < g[v].sz; i++){
                    int w   = g[v].ptr[i].fst;
                    int sum = g[v].ptr[i].snd;
                    if(!vis[w]){
                        vis[w] = true;
                        sgn[w] = -sgn[v];
                        val[w] = sum-val[v];
                        comp[cnt++] = w;
                        push(Q, w);
                    }
                    else if(sgn[w]==sgn[v]) {
                        bip = false;
                        x = sgn[w]*(sum-val[w]-val[v])/2;
                    }
                }
            }
            if(bip) {
                for(int i = 0; i < cnt; i++) {
                    int v = comp[i];
                    num[i] = (-sgn[v])*val[v];
                }
                qsort(num, cnt, sizeof(int), cmp);
                x = num[cnt/2];
            }
            for(int i = 0; i < cnt; i++) {
                int v = comp[i];
                ans[v] = val[v] + sgn[v]*x;
            }
            for(int i = 0; i < cnt; i++) {
                int v = comp[i];
                for(size_t i = 0; i < g[v].sz; i++){
                    int w = g[v].ptr[i].fst;
                    if(ans[v]+ans[w]!=g[v].ptr[i].snd){
                        puts("NO");
                        return;
                    }
                }
            }
        }
    }
    puts("YES");
    for(int v = 1; v <= n; v++){
        printf("%.1lf ", 0.5*ans[v]);
    }
    puts("");
}
int main(){
    Q=newQueue();
    while(scanf("%d %d", &n, &m)==2){
        for(int i = 1; i <= n; i++){
            g[i].sz=0;
        }
        for(int i = 0; i < m; i++){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            c *= 2;
            pbp(g[a], newpair(b,c));
            pbp(g[b], newpair(a,c));
        }
        solve();
    }
    return 0;
}

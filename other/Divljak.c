#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

int cmp(const void*a, const void*b){return(*(int*)a-*(int*)b);}
int unique(int*a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(a[i] != a[j])
      a[++j] = a[i];
  return j + 1;
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

typedef long long ll;
int fail[2000010],ch[2000010][26],mxsonid[2000010],sz[2000010],deep[2000010],top[2000010],in[2000010],out[2000010],ts;
int Head[2000010],Next[2000010],To[2000010],_cnt;
int base[2000010],n,pos[2000010],cnt,tot,p,op,x,q,st[2000010];
char s[2000010];


void addedge(int u,int v){
    _cnt++;
    Next[_cnt]=Head[u];
    Head[u]=_cnt;
    To[_cnt]=v;
}
void build(){
    Queue*Q = newQueue();
    push(Q, 0);
    while(!empty(Q)){
        int u = front(Q); pop(Q);
        if(u!=fail[u])
            addedge(fail[u],u);
        for(int i=0;i<26;i++){
            if(ch[u][i]){
                push(Q, ch[u][i]);
                if(u)
                    fail[ch[u][i]]=ch[fail[u]][i];
            }
            else
                ch[u][i]=ch[fail[u]][i];
        }
    }
}
void dfs(int u, int f){
    sz[u]++;
    int mxson=0;
    mxsonid[u]=0;
    for(int it=Head[u];it;it=Next[it]){
        int v=To[it];
        deep[v]=deep[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>mxson)
            mxson=sz[v],mxsonid[u]=v;
    }
}
void dfsid(int u,int f,int anc){
    in[u]=++ts;
    top[u]=anc;
    if(mxsonid[u])
        dfsid(mxsonid[u],u,anc);
    for(int it=Head[u];it;it=Next[it]){
        int v=To[it];
        if(v!=mxsonid[u])
            dfsid(v,u,v);
    }
    out[u]=ts;
}
int lca(int u,int v){
    while(top[u]!=top[v]){
        if(deep[top[u]]<deep[top[v]])
            swap(u,v);
        u=fail[top[u]];
    }
    return deep[u]<deep[v]?u:v;
}
void add(int x,int v){
    assert(x>0);
    for(;x<=ts;x+=(x&-x))
        base[x]+=v;
}
ll query(int x){
    ll res=0;
    for(;x;x-=(x&-x))
        res+=base[x];
    return res;
}
int mycmp(const void*a, const void*b){
    return(in[*(int*)a]<in[*(int*)b])?-1:1;
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        int len=strlen(s+1),cur=0;
        for(int j=1;j<=len;j++){
            if(!ch[cur][s[j]-'a'])
                ch[cur][s[j]-'a']=++tot;
            cur=ch[cur][s[j]-'a'];
        }
        pos[i]=cur;
    }
    build();
    dfs(0,0);
    dfsid(0,0,0);
    scanf("%d", &q);
    for(int i=1;i<=q;i++){
        scanf("%d", &op);
        if(op==1){
            scanf("%s", s+1);
            int len=strlen(s+1),cur=0,p=0;
            for(int j=1;j<=len;j++){
                cur=ch[cur][s[j]-'a'];
                st[++p]=cur;
            }
            qsort(st+1, p, sizeof(int), cmp);
            p = unique(st+1, p);
            qsort(st+1, p, sizeof(int), mycmp);
            for(int i=1;i<=p;i++){
                add(in[st[i]],1);
                if(i!=1)
                    add(in[lca(st[i],st[i-1])],-1);
            }
        }
        else{
            scanf("%d", &x);
            printf("%lld\n", query(out[pos[x]])-query(in[pos[x]]-1));
        }
    }
    return 0;
}

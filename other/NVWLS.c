#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


char buff[1000000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
char*prepend(char*s, char v){
  char*ptr=NULL;
  asprintf(&ptr, "%c%s", v, s);
  free(s);
  return ptr;
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
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
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
      printf("\n**Error in push: malloc failed to allocate\n\n");
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
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)  
      return 1;  
    ++i;
    if (i == Q->Capacity)  
      i = 0;
  }
  return 0;
}

#endif
/////////////////////////////////////
enum{ N = (int)3e5 + 50};
int v  [N],
    len[N];

//typedef struct Trie{
enum{ B = 26, 
      M = (int)1e5 + 50};
int next  [M][B], 
    fail  [M], 
    end   [M];
int failto[M];
int id    [M];
int root, L;

int newnode(){
    for(int i = 0; i < B; i++)
        next[L][i] = -1;
    id[L]     = -1;
    failto[L] = -1;
    end[L++]  = 0;
    return L - 1;
}
void init(){
    L    = 0;
    root = newnode();
}
void insert(char*buf, int idx){
    int now = root;
    for(int z=0; buf[z]; z++){char c = buf[z];
        if(next[now][c - 'A'] == -1)
           next[now][c - 'A'] = newnode();
        now = next[now][c - 'A'];
    }
    end[now]++;
    if(id[now] == -1 || v[id[now]] < v[idx])
       id[now] = idx;
}
void build(){
    Queue*Q=newQueue();
    fail[root] = root;
    for(int i = 0; i < B; i++){
        if(next[root][i] == -1)
           next[root][i] = root;
        else{
            fail[next[root][i]] = root;
            push(Q, next[root][i]);
        }
    }
    while(!empty(Q)){
        int now = front(Q); pop(Q);
        for(int i = 0; i < B; i++){
            if(next[now][i] == -1)
               next[now][i] = next[fail[now]][i];
            else{
                fail[next[now][i]] = next[fail[now]][i];
                push(Q, next[now][i]);
            }
        }
    }
}
int get_fail_to(int v){
    if(failto[v] != -1)
        return failto[v];
    if(v == 0)
        return failto[v] = 0;
    if(!end[fail[v]])
        return failto[v] = get_fail_to(fail[v]);
    else
        return failto[v] = fail[v];
}
//}Trie;

int  n;
char*fs[N];
char*s [N];
int  dp[N], 
     pv[N];
char*mes;

int main(){
    scanf("%d", &n);
    init();
    for(int i=0; i<n; i++)
        s[i]=strdup("");
    for(int i=0; i<n; i++){
        fs[i]=getstr();
        for(int z=0;fs[i][z];z++){char c = fs[i][z];
            if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
                v[i]++;
                continue;
            }
            s[i] = concatc(s[i], c);
        }
        len[i] = strlen(s[i]);
        insert(s[i], i);
    }
    build();
    int cur_st = 0;
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    mes=getstr();
    int mlen = strlen(mes);
    mes = prepend(mes, ' ');
    for(int i=1; i<=mlen; i++){
        cur_st = next[cur_st][mes[i] - 'A'];
        int cur = cur_st;
        if(!end[cur])
            cur = get_fail_to(cur);
        while(cur != 0){
            int id1 = id[cur];
            if(dp[i - len[id1]] != -1 && dp[i - len[id1]] + v[id1] > dp[i]){
                dp[i] = dp[i - len[id1]] + v[id1];
                pv[i] = id1;
            }
            cur = get_fail_to(cur);
        }
    }
    int cur = mlen;
    vec res=newVec();
    while(cur != 0){
        pb(res, pv[cur]);
        cur -= len[pv[cur]];
    }
    reverse(res.ptr, 0, res.sz-1);
    for(int z=0;z<res.sz;z++){int ii = res.ptr[z];
        printf("%s ", fs[ii]);
    }
    free(res.ptr);
    puts("");
    for(int i=0; i<n; i++) if( s[i]) free( s[i]);
    for(int i=0; i<n; i++) if(fs[i]) free(fs[i]);
    return 0;
}

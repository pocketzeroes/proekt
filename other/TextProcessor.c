#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#if 1 //que
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
#endif

typedef struct Node{
  int l, r, par, link, num_children, next[26];
}Node;
Node newNode(int l, int r, int par){//puts(__FUNCTION__);
  Node rv;
  rv.l  =l;
  rv.r  =r;
  rv.par=par;
  rv.link=-1;
  rv.num_children=0;
  memset(rv.next, -1, sizeof(rv.next));
  return rv;
}



int Length(Node n){//puts(__FUNCTION__);
  return n.r - n.l;
}
int get(Node n, char c){//puts(__FUNCTION__);
  return n.next[c-'a'];
}
void SetEdge(Node*n, char c, int node_index){//puts(__FUNCTION__);
  if(n->next[c-'a'] != -1 && node_index == -1)
    --n->num_children;
  else if(n->next[c-'a'] == -1 && node_index != -1)
    ++n->num_children;
  n->next[c-'a'] = node_index;
}

typedef struct State{
  int v, pos;
}State;
State newState(int v, int p){//puts(__FUNCTION__);
  return(State){v,p};
}
char*text;
Queue*que;
Node*tree;//of Node
int  treesz;
State ptr;
ll num_substrings;
int slen;


void SuffixTree(char*str){//puts(__FUNCTION__);
  que = newQueue();
  text = strdup(str);
  tree = calloc(2*slen+1, sizeof(Node));
  tree[treesz++] = newNode(0,0,-1);
}
State Go(State st, int l, int r){//puts(__FUNCTION__);
  while (l < r) {
    if(st.pos == Length(tree[st.v])){
      st = newState(get(tree[st.v], text[l]), 0);
      if(st.v == -1)
        return st;
    }
    else{
      if(text[ tree[st.v].l + st.pos ] != text[l])
        return newState(-1, -1);
      if(r-l < Length(tree[st.v]) - st.pos)
        return newState(st.v, st.pos + r-l);
      l += Length(tree[st.v]) - st.pos;
      st.pos = Length(tree[st.v]);
    }
  }
  return st;
}
int Split(State st){//puts(__FUNCTION__);
  if(st.pos == Length(tree[st.v]))
    return st.v;
  if(st.pos == 0)
    return tree[st.v].par;
  Node*v = &tree[st.v];
  int id = treesz;
  tree[treesz++] = newNode(v->l, v->l + st.pos, v->par);
  SetEdge(&tree[v->par], text[v->l], id);
  SetEdge(&tree[id], text[v->l + st.pos], st.v);
  tree[st.v].par = id;
  tree[st.v].l += st.pos;
  return id;
}
int GetLink(int v){//puts(__FUNCTION__);
  if (tree[v].link != -1)
    return tree[v].link;
  if (tree[v].par == -1)
    return 0;
  int to = GetLink(tree[v].par);
  return tree[v].link = Split(Go(newState(to, Length(tree[to])), tree[v].l + (tree[v].par==0), tree[v].r));
}
void TreeExtend(int pos){//puts(__FUNCTION__);
  int mid;
  num_substrings += size(que);
  do {
    State nptr = Go(ptr, pos, pos+1);
    if (nptr.v != -1) {
      ptr = nptr;
      return;
    }
    mid = Split(ptr);
    int leaf = treesz;
    num_substrings++;
    push(que, leaf);
    tree[treesz++] = newNode(pos, strlen(text), mid);
    SetEdge(&tree[mid], text[pos], leaf);
    ptr.v = GetLink(mid);
    ptr.pos = Length(tree[ptr.v]);
  }while (mid != 0);
}
void TreeDelete(int pos){//puts(__FUNCTION__);
  int leaf = front(que); pop(que);
  int par = tree[leaf].par;
  while (tree[leaf].num_children == 0) {
    if (ptr.v != leaf) {
      SetEdge(&tree[par], text[tree[leaf].l], -1);
      num_substrings -= fminl(tree[leaf].r, pos) - tree[leaf].l;
      leaf = par;
      par = tree[leaf].par;
    }
    else {
      if (ptr.pos == fminl(tree[leaf].r,pos) - tree[leaf].l)
        break;
      int mid = Split(ptr);
      ptr.v = mid;
      num_substrings -= fminl(tree[leaf].r, pos) - tree[leaf].l;
      SetEdge(&tree[mid], text[tree[leaf].l], -1);
      tree[leaf] = tree[mid];
      SetEdge(&tree[tree[mid].par], text[tree[mid].l], leaf);
      treesz--;
      break;
    }
  }
  if (leaf != 0 && tree[leaf].num_children == 0) {
    push(que, leaf);
    int to = (tree[leaf].par == 0) ? 0 : tree[tree[leaf].par].link;
    ptr = Go(newState(to, Length(tree[to])), tree[leaf].l + (tree[leaf].par==0), tree[leaf].r);
    tree[leaf].l = pos - Length(tree[leaf]);
    tree[leaf].r = strlen(text);
  }
}
enum{ MAXN = 100100};
ll ans_window[MAXN];
char txt[MAXN];
int main(){//puts(__FUNCTION__);
  int w, n, q;
  scanf("%s %d %d", txt, &n, &w);
  slen = strlen(txt);
  SuffixTree(txt);
  for(int i=1; i<=slen; ++i){
    TreeExtend(i-1);
    if(i >= w){
      ans_window[i-w] = num_substrings;
      TreeDelete(i);
    }
  }
  for(int i=0; i<n; ++i){
    scanf("%d", &q);
    printf("%lld\n", ans_window[q-1]);
  }
  return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
#if 1//dq

#define dummy dp->head
typedef struct node{
  int data;
  struct node *next;
  struct node *prev;
}node;
typedef struct deque{
  int count;
  node *head;
}deque;
deque*newDeque(){
  node *sentinel = malloc(sizeof(node));
  deque *dp = malloc(sizeof(deque));
  assert(dp != NULL && sentinel != NULL);
  sentinel -> prev = sentinel;
  sentinel -> next = sentinel;
  dummy = sentinel;
  dp -> count = 0;
  return dp;
}
void clear(deque*dp){
  node *temp, *prev;
  temp = prev = dummy -> next;
  while (temp != dummy){
    temp = temp -> next;
    free(prev);
    prev = temp;
  }
  free(dummy);
  free(dp);
}
int numItems(deque *dp){
  assert(dp != NULL);
  return dp->count;
}
bool empty(deque *dp){
  assert(dp != NULL);
  return dp->count == 0;
}
void push_front(deque *dp, int x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> next = dummy -> next;
  newNode -> prev = dummy;
  dummy -> next -> prev = newNode;
  dummy -> next = newNode;
}
void push_back(deque *dp, int x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> prev = dummy -> prev;
  newNode -> next = dummy;
  dummy -> prev -> next = newNode;
  dummy -> prev = newNode;
}
int pop_front(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> next;
  dummy -> next = temp -> next;
  temp -> next -> prev = temp -> prev;
  int x = temp->data;
  free(temp);
  return x;
}
int pop_back(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> prev;
  dummy -> prev = temp -> prev;
  temp -> prev -> next = temp -> next;
  int x = temp -> data;
  free(temp);
  return x;
}
int front(deque*dp){
  assert(dp != NULL && dummy -> next != NULL);
  return dummy->next->data;
}
int back(deque*dp){
  assert(dp != NULL && dummy -> prev != NULL);
  return dummy -> prev -> data;
}
void printDeque(deque*dp){
  assert(dp != NULL && dp->count != 0);
  int i = 0;
  node *temp = malloc(sizeof(node));
  temp = dummy->next;
  for(i = 0; i < dp -> count; i++){
    printf("\nnode %d: %d\n", i, temp->data);
    temp = temp->next;
  }
  printf("\ncount: %d\n", dp->count);
  return;
}
int size(deque*dp){
  return dp->count;
}
void moveToFirst(deque *dp, int position){
  assert(dp != NULL && dp -> count >= position);
  int i = 0;
  node *temp = malloc(sizeof(node));
  temp = dummy -> next;
  for(i = 0; i < position; i++){
    temp = temp -> next;
  }
  temp -> next -> prev = temp -> prev;
  temp -> prev -> next = temp -> next;
  temp -> next = dummy -> next;
  temp -> prev = dummy;
  dummy -> next -> prev = temp;
  dummy -> next = temp;   
  return;
}
#endif
#define FR(i,a,b) for(int i=(a);i<(b);++i)
#define FOR(i,n) FR(i,0,n)

int n,m;
vec edg  [1000000];
int indeg[1000000];

int main(){
  scanf("%d %d", &n, &m);
  if(n==0)
    exit(0);
  FOR(i, n)
    indeg[i] = 0;
  FOR(i, m){
    int a, b;
    scanf("%d %d", &a, &b);
    --a, --b;
    ++indeg[b];
    pb(edg[a], b);
  }
  deque*q = newDeque();
  FOR(i, n)
    if(indeg[i] == 0)
      push_back(q, i);
  vec ret = newVec();
  bool happy = 1;
  FOR(i, n){
    if(!size(q)){
      happy = 0;
      break;
    }
//  int r = rand()%(int)size(q);
//  swap(q[0], q[r]);
    int v = front(q); pop_front(q);
    pb(ret, v+1);
    for(int z=0;z<edg[v].sz;z++){int w = edg[v].ptr[z];
      if(0 == --indeg[w])
        push_back(q, w);
    }
  }
  FOR(i, n)
    edg[i].sz = 0;
  if(happy){
    FOR(i, n)
      printf("%d\n", ret.ptr[i]);
  }
  else
    puts("IMPOSSIBLE");
  return 0;
}

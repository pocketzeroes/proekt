#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#if 1//dq

#define dummy dp->head
typedef struct node{
  pair data;
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
void push_front(deque *dp, pair x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> next = dummy -> next;
  newNode -> prev = dummy;
  dummy -> next -> prev = newNode;
  dummy -> next = newNode;
}
void push_back(deque *dp, pair x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> prev = dummy -> prev;
  newNode -> next = dummy;
  dummy -> prev -> next = newNode;
  dummy -> prev = newNode;
}
pair pop_front(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> next;
  dummy -> next = temp -> next;
  temp -> next -> prev = temp -> prev;
  pair x = temp->data;
  free(temp);
  return x;
}
pair pop_back(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> prev;
  dummy -> prev = temp -> prev;
  temp -> prev -> next = temp -> next;
  pair x = temp -> data;
  free(temp);
  return x;
}
pair front(deque*dp){
  assert(dp != NULL && dummy -> next != NULL);
  return dummy->next->data;
}
pair back(deque*dp){
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

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char*M[n];
    for(int i=0; i<n; ++i)
        M[i] = getstr();
    bool visited[n][m]; clr(visited);
    int  dist   [n][m]; dfill(dist, n, m, 10000);
    deque*Q = newDeque();//of pair
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(M[i][j] == 'W'){
                push_back(Q, newpair(i, j));
                dist[i][j] = -1;
            }
        }
    }
    while(size(Q)>0){
        pair fq = front(Q);
        int i = fq.first;
        int j = fq.second; pop_front(Q);
        if(visited[i][j])
            continue;
        visited[i][j] = true;
        char from = M[i][j];
        for(int di = -1; di <= 1; ++di){
            for(int dj = -1; dj <= 1; ++dj){
                if(i+di >= 0 && i+di < n && j+dj >= 0 && j+dj < m){
                    char to = M[i+di][j+dj];
                    if(from == to){
                        dist[i+di][j+dj] = fmin(dist[i+di][j+dj], dist[i][j]);
                        push_front(Q, newpair(i+di, j+dj));
                    }
                    else{
                        dist[i+di][j+dj] = fmin(dist[i+di][j+dj], dist[i][j]+1);
                        push_back(Q, newpair(i+di, j+dj));
                    }
                }
            }
        }
    }
    int val[26];
    for(int c=0; c<26; ++c)
        val[c] = 10000;
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            val[M[i][j]-'A'] = fmin(val[M[i][j]-'A'], dist[i][j]);
    for(int c=0; c<26; ++c)
        if(val[c] >= 0 && val[c] < 10000)
            printf("%c %d\n", (char)('A' + c), val[c]);
    return 0;
}

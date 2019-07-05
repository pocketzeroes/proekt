#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
typedef struct{
  pair first;
  pair second;
}quad;
quad newQuad(pair a, pair b){
  quad rez;
  rez.first =a;
  rez.second=b;
  return rez;
}


#define dummy dp->head
typedef struct node{
  quad data;
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
void push_front(deque *dp, quad x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> next = dummy -> next;
  newNode -> prev = dummy;
  dummy -> next -> prev = newNode;
  dummy -> next = newNode;
}
void push_back(deque *dp, quad x){
  assert(dp != NULL);
  dp -> count++;
  node *newNode = malloc(sizeof(node));
  newNode -> data = x;
  newNode -> prev = dummy -> prev;
  newNode -> next = dummy;
  dummy -> prev -> next = newNode;
  dummy -> prev = newNode;
}
quad pop_front(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> next;
  dummy -> next = temp -> next;
  temp -> next -> prev = temp -> prev;
  quad x = temp->data;
  free(temp);
  return x;
}
quad pop_back(deque*dp){
  assert(dp != NULL && dp -> count > 0);
  dp -> count--;
  node *temp = dummy -> prev;
  dummy -> prev = temp -> prev;
  temp -> prev -> next = temp -> next;
  quad x = temp -> data;
  free(temp);
  return x;
}
quad front(deque*dp){
  assert(dp != NULL && dummy -> next != NULL);
  return dummy->next->data;
}
quad back(deque*dp){
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
//////////////////////----------------------------------------------------------

int  R, C;
int  i1, J1, i2, j2;
bool mark[20][20][4][1601];
int  dist[20][20][4][1601];
bool pass[20][20][4];
int  dr[] = { -1, 0, 1, 0 },
     dc[] = {  0, 1, 0,-1 };
deque*q;


void enq(int d, int r, int c, int rot, int rem){
  if(rem < 0)
    return;
  if(mark[r][c][rot][rem])
    return;
  push_back(q, newQuad(newPair(r,c), newPair(rot,rem)));
  mark[r][c][rot][rem] = 1;
  dist[r][c][rot][rem] = d;
}
void doit(){
  scanf("%d %d", &R, &C);
  if(R==0)
    exit(0);
  scanf("%d %d %d %d", &i1, &J1, &i2, &j2);
  --i1, --J1, --i2, --j2;
  memset(pass, 0, sizeof(pass));
  for(int r=0; r<R; ++r){
    for(int c=0; c<C; ++c){
      char buf[256];
      scanf("%s", buf);
      if(buf[0] == 'x')
        continue;
      for(char*p = buf; *p; ++p){
        pass[r][c][*p=='N' ? 0 : *p=='E' ? 1 : *p=='S' ? 2 : 3] = 1;
      }
    }
  }
  memset(mark, 0, sizeof(mark));
  clear(q);
  q = newDeque();
  push_back(q, newQuad(newPair(i1,J1), newPair(0,0)));
  mark[i1][J1][0][0] = 1;
  dist[i1][J1][0][0] = 0;
  int ans = -1;
  while(size(q)){
    int r   = front(q).first.first,
        c   = front(q).first.second,
        rot = front(q).second.first,
        rem = front(q).second.second;
    int d   = dist[r][c][rot][rem];
    pop_front(q);
    if(r == i2 && c == j2){
      ans = d;
      break;
    }
    for(int drot = -1; drot <= 1; ++drot){
      int rotp = (rot+drot+4)%4;
      int remp = rem + (drot==0);
      enq(d+1, r, c, rotp, remp);
      for(int k=0; k<4; ++k){
        int r2 = r + dr[k],
            c2 = c + dc[k];
        if(r2<0 || r2>=R || c2<0 || c2>=C)
          continue;
        int kp = (k+rotp)%4;
        if(!pass[r][c][kp])
          continue;
        for(int drot2 = -1; drot2 <= 2; ++drot2){
          if(abs(drot2) > remp)
            continue;
          int rot2 = (drot2+4)%4,
              rem2 = remp - abs(drot2);
          if(!pass[r2][c2][(k+rot2+2)%4])
            continue;
          enq(d+1, r2, c2, rot2, rem2);
        }
      }
    }
  }
  printf("%d\n",ans);
}
int main(){
  q = newDeque();
  doit();
  return 0;
}

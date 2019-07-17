#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char**newmat(int x, int y){
  char**rv = calloc(x, sizeof(char*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(char));
  return rv;
}

#if 1// de que
#define dummy dp->head

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;
typedef struct Deque{
    int count;
    node *head;
}Deque;
Deque*newDeque(){
    node *sentinel = malloc(sizeof(node));
    Deque *dp = malloc(sizeof(Deque));
    assert(dp != NULL && sentinel != NULL);
    sentinel -> prev = sentinel;
    sentinel -> next = sentinel;
    dummy = sentinel;
    dp -> count = 0;
    return dp;
}
void destroyDeque(Deque *dp){
    node *temp, *prev;
    temp = prev = dummy -> next;
    while (temp != dummy)
    {
        temp = temp -> next;
        free(prev);
        prev = temp;
    }
    free(dummy);
    free(dp);
}
int numItems(Deque *dp){
    assert(dp != NULL);
    return dp->count;
}
bool empty(Deque *dp){
    assert(dp != NULL);
    return dp->count == 0;
}
void push_front(Deque *dp, int x){
    assert(dp != NULL);
    dp -> count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> next = dummy -> next;
    newNode -> prev = dummy;
    dummy -> next -> prev = newNode;
    dummy -> next = newNode;
}
void push_back(Deque *dp, int x){
    assert(dp != NULL);
    dp -> count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> prev = dummy -> prev;
    newNode -> next = dummy;
    dummy -> prev -> next = newNode;
    dummy -> prev = newNode;
}
int pop_front(Deque *dp){
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> next;
    dummy -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int pop_back(Deque *dp){
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> prev;
    dummy -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    int x = temp -> data;
    free(temp);
    return x;
}
int removePosition(Deque *dp, int position){
    assert(dp != NULL);
    dp -> count--;
    int i;
    node *temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int front(Deque *dp){
    assert(dp != NULL && dummy -> next != NULL);
    return dummy->next->data;
}
int back(Deque *dp){
    assert(dp != NULL && dummy -> prev != NULL);
    return dummy -> prev -> data;
}
int getPosition(Deque *dp, int position){
    assert(dp != NULL && position <= dp -> count);
    int i;
    node* temp = malloc(sizeof(node));
    temp = dummy -> next;
    for (i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    return temp -> data;
}
int search(Deque *dp, int x){
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    int found = 0;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next; 
    for (i = 0; i < dp -> count; i++)
    {
        if(temp -> data == x)
        {
            found = 1;
            printf("found %d!\n", x);
            break;
        }
        else
        {
            temp = temp -> next;
            position++;
        }
    }
    if (found == 1)
        return position;
    else
        return -1;
}
void printDeque(Deque*dp){
    assert(dp != NULL && dp->count != 0);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy->next;
    for(i = 0; i < dp -> count; i++)    {
        printf("\nnode %d: %d\n", i, temp->data);
        temp = temp->next;
    }
    printf("\ncount: %d\n", dp->count);
    return;
}
int size(Deque*dp){
    return dp->count;
}
void moveToFirst(Deque *dp, int position){
    assert(dp != NULL && dp -> count >= position);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> next -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    temp -> next = dummy -> next;
    temp -> prev = dummy;
    dummy -> next -> prev = temp;
    dummy -> next = temp;   
    return;
};
void UpdateData(Deque *dp, int position, int data){
    assert(dp != NULL);
    assert(dp -> count >= position);
    int i;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> data = data;
    return;
}
int findMin(Deque *dp){
    assert(dp != NULL);
    int min, i;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    min = temp -> data;
    temp = temp -> next;
    for(i = 1; i < dp -> count; i++)
    {
        if(temp -> data <= min)
        {
            position = i;
            min = temp -> data;
        }
    }
    return position;
}
#endif
int w, h;
char**grid;

int bfs(int targetX, int targetY){
  enum{ SEPARATOR = -1};
  Deque*dequeX = newDeque();
  Deque*dequeY = newDeque();
  bool visited[h][w]; memset(visited, 0, sizeof(visited));
  for(int y=1; y<h-1; y++){
    if(grid[y][0] == 'D'){
      push_front(dequeX, 0);
      push_front(dequeY, y);
      visited[y][0] = true;
    }
    if(grid[y][w-1] == 'D'){
      push_front(dequeX, w-1);
      push_front(dequeY, y);
      visited[y][w-1] = true;
    }
  }
  for(int x = 1; x < w - 1; x++){
    if (grid[0][x] == 'D') {
      push_front(dequeX, x);
      push_front(dequeY, 0);
      visited[0][x] = true;
    }
    if (grid[h-1][x] == 'D'){
      push_front(dequeX, x);
      push_front(dequeY, w-1);
      visited[h-1][x] = true;
    }
  }
  push_back(dequeX, SEPARATOR);
  int dx[4]= {-1, 1, 0, 0};
  int dy[4]= {0, 0, -1, 1};
  int depth = 0;
  while(size(dequeY) > 0){
    if(front(dequeX) == SEPARATOR){
      push_back(dequeX, pop_front(dequeX));
      depth++;
    }
    int x = pop_front(dequeX);
    int y = pop_front(dequeY);
    if(x == targetX && y == targetY)
      return depth;
    for(int i = 0; i < 4; i++){
      int newX = x + dx[i];
      int newY = y + dy[i];
      if(newX >= 0 && newX < w && newY >= 0 && newY < h){
        if(grid[newY][newX] == 'c'){
          if(!visited[newY][newX]){
            visited[newY][newX] = true;
            push_back(dequeX, newX);
            push_back(dequeY, newY);
          }
        }
        else if(grid[newY][newX] == 'D'){
          if(!visited[newY][newX]){
            visited[newY][newX] = true;
            push_front(dequeX, newX);
            push_front(dequeY, newY);
          }
        }
      }
    }
  }
  assert(!"throw new IllegalStateException");
}
int main(){
  h = in_nextInt();
  w = in_nextInt();
  grid = newmat(h, w);// of char
  getchar();
  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++)
      grid[i][j] = getchar();
    getchar();
  }
  int targetY = in_nextInt() - 1;
  int targetX = in_nextInt() - 1;
  printf("%d\n", bfs(targetX, targetY));
  return 0;
}

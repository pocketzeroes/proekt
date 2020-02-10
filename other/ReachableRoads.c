#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
#define int ll
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
#undef int
/////////////////////////

int main(){
    ll i, j, k, cases, nodes, edges, source, dest, check;
    scanf("%lld", &cases);
    for(i=0; i<cases; i++){
        scanf("%lld %lld", &nodes, &edges);
        ll trees=0;
        vecl adj [nodes]; clr(adj );
        bool seen[nodes]; clr(seen);
        Deque*que = newDeque();//ll
        for(j=0; j<edges; j++){
            scanf("%lld %lld", &source, &dest);
            pbl(adj[source], dest  );
            pbl(adj[dest  ], source);
        }
        for(j=0; j<nodes; j++){
            if(!seen[j]){
                push_back(que, j);
                trees++;
            }
            while(!empty(que)){
                check = front(que); pop_front(que);
                for(int z=0;z<adj[check].sz;z++){ll ez = adj[check].ptr[z];
                    if(!seen[ez]){
                        push_back(que, ez);
                        seen[ez] = true;
                    }
                }
            }
        }
        printf("%lld\n", trees-1);
    }
    return 0;
}

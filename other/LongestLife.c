#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double max(double a, double b){return a>b?a:b;}
typedef struct{
  double a, b;
}line;

#if 1// de que
#define dummy dp->head

typedef struct node{
    line data;
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
void push_front(Deque *dp, line x){
    assert(dp != NULL);
    dp -> count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> next = dummy -> next;
    newNode -> prev = dummy;
    dummy -> next -> prev = newNode;
    dummy -> next = newNode;
}
void push_back(Deque *dp, line x){
    assert(dp != NULL);
    dp -> count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> prev = dummy -> prev;
    newNode -> next = dummy;
    dummy -> prev -> next = newNode;
    dummy -> prev = newNode;
}
line pop_front(Deque *dp){
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> next;
    dummy -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    line x = temp -> data;
    free(temp);
    return x;
}
line pop_back(Deque *dp){
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> prev;
    dummy -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    line x = temp -> data;
    free(temp);
    return x;
}
line removePosition(Deque *dp, int position){
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
    line x = temp -> data;
    free(temp);
    return x;
}
line front(Deque *dp){
    assert(dp != NULL && dummy -> next != NULL);
    return dummy->next->data;
}
line back(Deque *dp){
    assert(dp != NULL && dummy -> prev != NULL);
    return dummy -> prev -> data;
}
line getpos(Deque *dp, int position){
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
}
#endif
typedef long long ll;
enum{ ms =(int)2e5+2};


double eval(line t, double x){
  return t.b * x + t.a;
}
double intersectX(line t, line l){
  return 1.0 * (t.a - l.a) / (l.b - t.b);
}
Deque*dq;//of line
int main(){
  dq=newDeque();
  ll n;
  int p, c;
  scanf("%lld %d %d", &n, &p, &c);
  double ans = n;
  push_front(dq, (line){1.0*n, -1.});
  double last = 1.;
  for(int i=0; i<p; i++){
    ll t;
    int x, y;
    scanf("%lld %d %d", &t, &x, &y);
    double prop = 1.0*y/x;
    if(prop >= last)
      continue;
    last = prop;
    while(size(dq) >= 2 && eval(back(dq), t) <= eval( getpos(dq, size(dq)-2), t))
      pop_back(dq);
    double newAns = eval(back(dq), t) - c;
    ans = max(ans, t + newAns/prop);
    line cur =(line){newAns + prop*t, -prop};
    while(size(dq) >= 2 && intersectX(cur, getpos(dq,0)) <= intersectX(getpos(dq,0), getpos(dq,1)))
      pop_front(dq);
    push_front(dq, cur);
  }
  printf("%.10lf\n", ans);
  return 0;
}

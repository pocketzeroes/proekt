#define pushFront  frontMiddleBackQueuePushFront
#define pushMiddle frontMiddleBackQueuePushMiddle
#define pushBack   frontMiddleBackQueuePushBack
#define popFront   frontMiddleBackQueuePopFront
#define popMiddle  frontMiddleBackQueuePopMiddle
#define popBack    frontMiddleBackQueuePopBack

typedef struct{
}FrontMiddleBackQueue;
FrontMiddleBackQueue*gptr;
typedef struct Node{
    int val;
    struct Node*next;
    struct Node*pre;
}Node;
Node*newNode(int val){
    Node*this=calloc(1, sizeof(Node));
    this->val=val;
    this->next=NULL;
    this->pre=NULL;
    return this;
}
int size;
Node*head;
Node*tail;
Node*middle;

FrontMiddleBackQueue*frontMiddleBackQueueCreate(){
    head = newNode(0);
    tail = newNode(0);
    middle=head;
    head->next=tail;
    tail->pre=head;
    size=0;
    return gptr;
}
void frontMiddleBackQueuePushFront(FrontMiddleBackQueue*obj, int val){
    Node*node=newNode(val);
    node->next=head->next;
    head->next->pre=node;
    node->pre=head;
    head->next=node;
    size++;
    if(size==1)
        middle=middle->next;
    if(size%2==0)
        middle=middle->pre;
}
void frontMiddleBackQueuePushMiddle(FrontMiddleBackQueue*obj, int val){
    if(size==0){
        pushFront(obj, val);
        return;
    }
    Node*node=newNode(val);
    if(size%2==1){
        middle->pre->next=node;
        node->pre=middle->pre;
        middle->pre=node;
        node->next=middle;
        middle=middle->pre;
    }
    else{
        middle->next->pre=node;
        node->next=middle->next;
        middle->next=node;
        node->pre=middle;
        middle=middle->next;
    }
    size++;
}
void frontMiddleBackQueuePushBack(FrontMiddleBackQueue*obj, int val){
    Node*node=newNode(val);
    node->next=tail;
    tail->pre->next=node;
    node->pre=tail->pre;
    tail->pre=node;
    size++;
    if(size%2==1)
        middle=middle->next;
}
int frontMiddleBackQueuePopFront(FrontMiddleBackQueue*obj){
    if(size==0)
        return-1;
    int data=head->next->val;
    head->next=head->next->next;
    head->next->pre=head;
    if(size%2==0){
      middle=middle->next;
    }
    size--;
    if(size==0)
        middle=head;
    return data;
}
int frontMiddleBackQueuePopMiddle(FrontMiddleBackQueue*obj){
    if(size==0)
        return-1;
    int data=middle->val;
    middle->pre->next=middle->next;
    middle->next->pre=middle->pre;
    if(size%2==0){
        middle=middle->next;
    }
    else{
        middle=middle->pre;
    }
    size--;
    return data;
}
int frontMiddleBackQueuePopBack(FrontMiddleBackQueue*obj){
    if(size==0)
        return-1;
    int data=tail->pre->val;
    tail->pre=tail->pre->pre;
    tail->pre->next=tail;
    if(size%2==1){
        middle=middle->pre;
    }
    size--;
    return data;
}
void frontMiddleBackQueueFree(FrontMiddleBackQueue*obj){
    ;
}

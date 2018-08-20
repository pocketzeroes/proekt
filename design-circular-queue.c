typedef struct{
}MyCircularQueue;
MyCircularQueue*gptr;

typedef struct Node{
    int  val;
    struct Node*next;
}Node;
Node*front,
    *rear;

MyCircularQueue*myCircularQueueCreate(int k);
bool myCircularQueueEnQueue(MyCircularQueue*obj, int value);
bool myCircularQueueDeQueue(MyCircularQueue*obj);
int myCircularQueueFront(MyCircularQueue*obj);
int myCircularQueueRear(MyCircularQueue*obj);
bool myCircularQueueIsEmpty(MyCircularQueue*obj);
bool myCircularQueueIsFull(MyCircularQueue*obj);
void myCircularQueueFree(MyCircularQueue*obj);



Node*newNode(){
    Node*rez = calloc(1,sizeof(Node));
    return rez;
}
MyCircularQueue*myCircularQueueCreate(int k){
    Node*root = newNode();
    Node*cur  = root;
    front     = root;
    rear      = NULL;
    for(int i=0; i<k-1; i++){
        Node*temp = newNode();
        cur->next = temp;
        cur = temp;
    }
    cur->next = root;
    return gptr;
}
bool myCircularQueueEnQueue(MyCircularQueue*obj, int value){
    if(myCircularQueueIsFull(gptr))
        return false;
    if(myCircularQueueIsEmpty(gptr))
        rear = front;
    else
        rear = rear->next;
    rear->val = value;
    return true;
}
bool myCircularQueueDeQueue(MyCircularQueue*obj){
    if(myCircularQueueIsEmpty(gptr))
        return false;
    if(front == rear)
        rear = NULL;
    else
        front = front->next;
    return true;
}
int myCircularQueueFront(MyCircularQueue*obj){
    return myCircularQueueIsEmpty(gptr) ? -1 : front->val;
}
int myCircularQueueRear(MyCircularQueue*obj){
    return myCircularQueueIsEmpty(gptr)?-1:rear->val;
}
bool myCircularQueueIsEmpty(MyCircularQueue*obj){
    return rear == NULL;
}
bool myCircularQueueIsFull(MyCircularQueue*obj){
    if(myCircularQueueIsEmpty(gptr))
        return false;
    return rear->next == front;
}
void myCircularQueueFree(MyCircularQueue*obj){
    return;
}

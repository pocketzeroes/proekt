typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;
#define dummy dp->head
typedef struct MyCircularDeque{
    int count;
    node*head;
}MyCircularDeque;
MyCircularDeque*gptr;
int gLimit;

MyCircularDeque*myCircularDequeCreate(int k){
    node *sentinel = malloc(sizeof(node));
    MyCircularDeque *dp = malloc(sizeof(MyCircularDeque));
    assert(dp != NULL && sentinel != NULL);
    sentinel -> prev = sentinel;
    sentinel -> next = sentinel;
    dummy = sentinel;
    dp -> count = 0;
    gLimit=k;
    return dp;
}
void myCircularDequeFree(MyCircularDeque *dp){
    node *temp, *prev;
    temp = prev = dummy -> next;
    while (temp != dummy){
        temp = temp -> next;
        free(prev);
        prev = temp;
    }
    free(dummy);
    free(dp);
    gLimit=0;
}
int numItems(MyCircularDeque *dp){
    assert(dp != NULL);
    return dp->count;
}
bool myCircularDequeIsEmpty(MyCircularDeque *dp){
    assert(dp != NULL);
    return dp->count == 0;
}
bool myCircularDequeIsFull(MyCircularDeque*dp){
    if(dp->count == gLimit)
        return true;
    return false;
}
bool myCircularDequeInsertFront(MyCircularDeque *dp, int x){
    assert(dp != NULL);
    if(dp->count == gLimit)
        return false;
    dp->count++;
    node *newNode = malloc(sizeof(node));
    newNode->data = x;
    newNode->next = dummy -> next;
    newNode->prev = dummy;
    dummy->next->prev = newNode;
    dummy->next = newNode;
    return true;
}
bool myCircularDequeInsertLast(MyCircularDeque *dp, int x){
    assert(dp != NULL);
    if(dp->count == gLimit)
        return false;
    dp->count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> prev = dummy -> prev;
    newNode -> next = dummy;
    dummy -> prev -> next = newNode;
    dummy -> prev = newNode;
    return true;
}
bool myCircularDequeDeleteFront(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return false;
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> next;
    dummy -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return true;
}
bool myCircularDequeDeleteLast(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return false;
    assert(dp != NULL && dp -> count > 0);
    dp->count--;
    node *temp = dummy -> prev;
    dummy -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    int x = temp -> data;
    free(temp);
    return true;
}
int removePosition(MyCircularDeque *dp, int position){
    assert(dp != NULL);
    dp -> count--;
    int i;
    node *temp = dummy -> next;
    for(i = 0; i < position; i++){
        temp = temp -> next;
    }
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int myCircularDequeGetFront(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return -1;
    assert(dp != NULL && dummy -> next != NULL);
    return dummy->next->data;
}
int myCircularDequeGetRear(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return -1;
    assert(dp != NULL && dummy -> prev != NULL);
    return dummy -> prev -> data;
}
int getPosition(MyCircularDeque *dp, int position){
    assert(dp != NULL && position <= dp -> count);
    int i;
    node* temp = malloc(sizeof(node));
    temp = dummy -> next;
    for (i = 0; i < position; i++){
        temp = temp -> next;
    }
    return temp -> data;
}
int search(MyCircularDeque *dp, int x){
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    int found = 0;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next; 
    for (i = 0; i < dp -> count; i++){
        if(temp -> data == x){
            found = 1;
            printf("found %d!\n", x);
            break;
        }
        else{
            temp = temp -> next;
            position++;
        }
    }
    if (found == 1)
        return position;
    else
        return -1;
}
void printDeque(MyCircularDeque *dp){
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < dp -> count; i++){
        printf("\nnode %d: %d\n", i, temp -> data);
        temp = temp -> next;
    }
    printf("\ncount: %d\n", dp -> count);
    return;
}
void moveToFirst(MyCircularDeque *dp, int position){
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
};
void UpdateData(MyCircularDeque *dp, int position, int data){
    assert(dp != NULL);
    assert(dp -> count >= position);
    int i;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++){
        temp = temp -> next;
    }
    temp -> data = data;
    return;
}
int findMin(MyCircularDeque *dp){
    assert(dp != NULL);
    int min, i;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    min = temp -> data;
    temp = temp -> next;
    for(i = 1; i < dp -> count; i++){
        if(temp -> data <= min){
            position = i;
            min = temp -> data;
        }
    }
    return position;
}
typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;
#define dummy dp->head
typedef struct MyCircularDeque{
    int count;
    node*head;
}MyCircularDeque;
MyCircularDeque*gptr;
int gLimit;

MyCircularDeque*myCircularDequeCreate(int k){
    node *sentinel = malloc(sizeof(node));
    MyCircularDeque *dp = malloc(sizeof(MyCircularDeque));
    assert(dp != NULL && sentinel != NULL);
    sentinel -> prev = sentinel;
    sentinel -> next = sentinel;
    dummy = sentinel;
    dp -> count = 0;
    gLimit=k;
    return dp;
}
void myCircularDequeFree(MyCircularDeque *dp){
    node *temp, *prev;
    temp = prev = dummy -> next;
    while (temp != dummy){
        temp = temp -> next;
        free(prev);
        prev = temp;
    }
    free(dummy);
    free(dp);
    gLimit=0;
}
int numItems(MyCircularDeque *dp){
    assert(dp != NULL);
    return dp->count;
}
bool myCircularDequeIsEmpty(MyCircularDeque *dp){
    assert(dp != NULL);
    return dp->count == 0;
}
bool myCircularDequeIsFull(MyCircularDeque*dp){
    if(dp->count == gLimit)
        return true;
    return false;
}
bool myCircularDequeInsertFront(MyCircularDeque *dp, int x){
    assert(dp != NULL);
    if(dp->count == gLimit)
        return false;
    dp->count++;
    node *newNode = malloc(sizeof(node));
    newNode->data = x;
    newNode->next = dummy -> next;
    newNode->prev = dummy;
    dummy->next->prev = newNode;
    dummy->next = newNode;
    return true;
}
bool myCircularDequeInsertLast(MyCircularDeque *dp, int x){
    assert(dp != NULL);
    if(dp->count == gLimit)
        return false;
    dp->count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> prev = dummy -> prev;
    newNode -> next = dummy;
    dummy -> prev -> next = newNode;
    dummy -> prev = newNode;
    return true;
}
bool myCircularDequeDeleteFront(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return false;
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> next;
    dummy -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return true;
}
bool myCircularDequeDeleteLast(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return false;
    assert(dp != NULL && dp -> count > 0);
    dp->count--;
    node *temp = dummy -> prev;
    dummy -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    int x = temp -> data;
    free(temp);
    return true;
}
int removePosition(MyCircularDeque *dp, int position){
    assert(dp != NULL);
    dp -> count--;
    int i;
    node *temp = dummy -> next;
    for(i = 0; i < position; i++){
        temp = temp -> next;
    }
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int myCircularDequeGetFront(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return -1;
    assert(dp != NULL && dummy -> next != NULL);
    return dummy->next->data;
}
int myCircularDequeGetRear(MyCircularDeque *dp){
    if(myCircularDequeIsEmpty(dp))
        return -1;
    assert(dp != NULL && dummy -> prev != NULL);
    return dummy -> prev -> data;
}
int getPosition(MyCircularDeque *dp, int position){
    assert(dp != NULL && position <= dp -> count);
    int i;
    node* temp = malloc(sizeof(node));
    temp = dummy -> next;
    for (i = 0; i < position; i++){
        temp = temp -> next;
    }
    return temp -> data;
}
int search(MyCircularDeque *dp, int x){
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    int found = 0;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next; 
    for (i = 0; i < dp -> count; i++){
        if(temp -> data == x){
            found = 1;
            printf("found %d!\n", x);
            break;
        }
        else{
            temp = temp -> next;
            position++;
        }
    }
    if (found == 1)
        return position;
    else
        return -1;
}
void printDeque(MyCircularDeque *dp){
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < dp -> count; i++){
        printf("\nnode %d: %d\n", i, temp -> data);
        temp = temp -> next;
    }
    printf("\ncount: %d\n", dp -> count);
    return;
}
void moveToFirst(MyCircularDeque *dp, int position){
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
};
void UpdateData(MyCircularDeque *dp, int position, int data){
    assert(dp != NULL);
    assert(dp -> count >= position);
    int i;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++){
        temp = temp -> next;
    }
    temp -> data = data;
    return;
}
int findMin(MyCircularDeque *dp){
    assert(dp != NULL);
    int min, i;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    min = temp -> data;
    temp = temp -> next;
    for(i = 1; i < dp -> count; i++){
        if(temp -> data <= min){
            position = i;
            min = temp -> data;
        }
    }
    return position;
}

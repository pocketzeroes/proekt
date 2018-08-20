#pragma GCC optimize "-O3"
typedef struct node{
    int val;
    struct node*next;
}node;
node*make_node(int val, node*next){
    node * rv = malloc(sizeof(*rv));  assert(rv);
    rv->val = val;
    rv->next = next;
    return rv;
}
void free_list(node * head){
    node * prev;
    while (head) {
        prev = head;
        head = head->next;
        free(prev);
    }
}
typedef struct{
    node * head;
    node * tail;
    int size;
}MyLinkedList;

MyLinkedList* myLinkedListCreate(){
    MyLinkedList * rv = calloc(1, sizeof(*rv));
    return rv;
}
int myLinkedListGet(MyLinkedList* obj, int index){
    if (index >= obj->size)
        return -1;
    node * cur = obj->head;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur->val;
}
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    node * newnode = make_node(val, obj->head);
    obj->head = newnode;
    obj->size += 1;
    if (obj->size == 1)
        obj->tail = obj->head;
}
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    node * newnode = make_node(val, NULL);
    if (obj->tail) {
        obj->tail->next = newnode;
        obj->tail = newnode;
        obj->size += 1;
    }
    else
        myLinkedListAddAtHead(obj, val);
}
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val){
    if (index > obj->size)
        return;
    if (index == obj->size)
        return myLinkedListAddAtTail(obj, val);
    if (index == 0)
        return myLinkedListAddAtHead(obj, val);
    node * cur = obj->head;
    for (int i = 1; i < index; ++i)
        cur = cur->next;
    node * newnode = make_node(val, cur->next);
    cur->next = newnode;
    obj->size += 1;
}
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index){
    if (index >= obj->size)
        return;
    node * temp, * rm;
    if (index == 0) {
        temp = obj->head;
        obj->head = temp->next;
        free(temp);
        obj->size -= 1;
        return;
    }
    if (index == obj->size - 1) {
        temp = obj->head;
        while (temp->next != obj->tail)
            temp = temp->next;
        free(temp->next);
        obj->tail = temp;
        obj->size -= 1;
        return;
    }
    temp = obj->head;
    for (int i = 1; i < index; ++i)
        temp = temp->next;
    rm = temp->next;
    temp->next = rm->next;
    free(rm);
    obj->size -= 1;
}
void myLinkedListFree(MyLinkedList* obj) {
    free_list(obj->head);
    free(obj);
}

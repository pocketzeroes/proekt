
typedef struct RandomListNode RandomListNode ;
RandomListNode*newRandomListNode(int l){
    RandomListNode*rez=malloc(sizeof(RandomListNode));
    rez->label=l;
    rez->next=NULL;
    rez->random=NULL;
    return rez;
}
RandomListNode*copyRandomList(RandomListNode *head) {
    for (RandomListNode *curr = head; curr; curr = curr->next->next) {
        RandomListNode  *node = newRandomListNode(curr->label);
        node->next = curr->next;
        curr->next = node;
    }
    for (RandomListNode  *curr = head; curr; curr = curr->next->next) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
    }
    RandomListNode dummy;
    dummy.label=0;
    dummy.next=NULL;
    dummy.random=NULL;
    for (RandomListNode  *curr = head, *copy_curr = &dummy;
         curr;
         copy_curr = copy_curr->next, curr = curr->next) {
        copy_curr->next = curr->next;
        curr->next = curr->next->next;
    }
    return dummy.next;
}
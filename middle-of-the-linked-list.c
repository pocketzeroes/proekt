typedef struct ListNode ListNode;
ListNode*middleNode(ListNode*head){
    int n = 0;
    for(ListNode*x=head; x!=NULL; x=x->next, n++);
    int m = n/2;
    ListNode*y = head;
    for(int i=0; i<m; i++, y = y->next);
    return y;
}

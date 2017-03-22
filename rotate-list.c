typedef struct ListNode ListNode;
ListNode*rotateRight(ListNode*head,int k){
    if (head == NULL || head->next == NULL)
        return head;
    int n = 1;
    ListNode*curr = head;
    for (; curr->next; curr = curr->next)
        ++n;
    curr->next = head;
    ListNode*tail = curr;
    k = n - k % n;
    curr = head;
    for (int i = 0; i < k; curr = curr->next, ++i)
        tail = curr;
    tail->next = NULL;
    return curr; 
}

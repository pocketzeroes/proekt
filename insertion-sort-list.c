typedef struct ListNode ListNode;
ListNode* findInsertPosition(ListNode *head, int x) {
    ListNode *prev = NULL;
    for (ListNode * curr = head; curr && curr->val <= x;  prev = curr, curr = curr->next);
    return prev;
}
ListNode*insertionSortList(ListNode *head) {
    ListNode dummy;
    dummy.val=INT_MIN;
    dummy.next=NULL;
    ListNode*curr = head;
    ListNode*position = NULL;
    while (curr) {
        position = findInsertPosition(&dummy, curr->val);
        ListNode *tmp = curr->next;
        curr->next = position->next;
        position->next = curr;
        curr = tmp;
    }
    return dummy.next;
}


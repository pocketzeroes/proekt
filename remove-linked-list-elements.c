typedef struct ListNode ListNode;
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy;
    dummy.next    = head;
    ListNode*prev = &dummy;
    ListNode*cur  = dummy.next;
    while (cur) {
        if (cur->val == val) {
            prev->next = cur->next;
        } 
        else {
            prev = cur;
        }
        cur = cur->next;
    }
    return dummy.next;
}

typedef struct ListNode ListNode;
ListNode* swapPairs(ListNode* head) {
    ListNode dummy;
    dummy.next = head;
    ListNode*curr = &dummy;
    while (curr->next && curr->next->next) {
        ListNode* next_one   = curr->next;
        ListNode* next_two   = next_one->next;
        ListNode* next_three = next_two->next;
        curr->next           = next_two;
        next_two->next       = next_one;
        next_one->next       = next_three;
        curr                 = next_one;
    }
    return dummy.next; 
}

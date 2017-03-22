typedef struct ListNode ListNode;
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode dummy;
    dummy.next = head;
    ListNode*prev = &dummy;
    for (int i = 0; i < m - 1; ++i) 
        prev = prev->next;
    ListNode*head2 = prev;
    prev = prev->next;
    ListNode*cur = prev->next;
    for (int i = m; i < n; ++i) {
        prev->next = cur->next; 
        cur->next = head2->next;
        head2->next = cur;      
        cur = prev->next;       
    }
    return dummy.next;
}

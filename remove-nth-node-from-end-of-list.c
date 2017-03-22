typedef struct ListNode ListNode;
ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy{0};
    dummy.next = head;
    ListNode*slow = &dummy;
    ListNode*fast = &dummy;
    while (n > 0) {
        fast = fast->next;
        --n;
    }
    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode*node_to_delete = slow->next;
    slow->next = slow->next->next;
    return dummy.next;
}

typedef struct ListNode ListNode;
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy;
    dummy.next = head;
    ListNode* curr = head;
    ListNode* curr_dummy = &dummy;
    int len = 0;
    while (curr) {
        ListNode* next_curr = curr->next;
        len = (len + 1) % k;
        if (len == 0) {
            ListNode* next_dummy = curr_dummy->next;
            reverse(&curr_dummy, curr->next);
            curr_dummy = next_dummy;
        }
        curr = next_curr;
    }
    return dummy.next;
}
void reverse(ListNode **begin, const ListNode *end) {
    ListNode *first = (*begin)->next;
    ListNode *curr = first->next;
    while (curr != end) {
        first->next = curr->next;
        curr->next = (*begin)->next;
        (*begin)->next = curr;
        curr = first->next;
    }
}

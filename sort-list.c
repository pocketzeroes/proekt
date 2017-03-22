#define nullptr NULL
typedef struct ListNode ListNode;
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode dummy;
    ListNode* curr = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* sortList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* slow = head; 
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow;
    slow = slow->next;
    fast->next = nullptr;
    return mergeTwoLists(sortList(head), sortList(slow));
}

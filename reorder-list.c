typedef struct ListNode ListNode;
ListNode*reverse(ListNode *head) {
    ListNode dummy;
    while (head) {
        ListNode* tmp = head->next;
        head->next = dummy.next;
        dummy.next = head;
        head = tmp;
    }
    return dummy.next;
}
ListNode *merge(ListNode *list1, ListNode *list2) {
    ListNode dummy;
    ListNode*ptr = &dummy;
    while (list1 && list2) {
        ListNode* tmp = list1->next;
        ptr->next = list1;
        ptr = ptr->next;
        ptr->next = list2;
        ptr = ptr->next;
        list1 = tmp;
        list2 = list2->next;
    }
    if (list1) {
        ptr->next = list1;
    }
    return dummy.next;
}
void reorderList(ListNode *head) {
    if (!head) 
        return;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* tmp = slow->next;
    slow->next = NULL;
    slow = tmp;

    merge(head, reverse(slow));
}

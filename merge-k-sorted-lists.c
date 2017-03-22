typedef struct ListNode ListNode;
ListNode*mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode dummy;
    ListNode*curr = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        }
        else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    curr->next = l1 ? l1 : l2;
    return dummy.next;
}
ListNode*mergeKLists(ListNode**lists,int listsSize){
    if (listsSize==0)
        return NULL;
    int left = 0, right = listsSize - 1;
    while (right > 0) {
        if (left >= right)
            left = 0;
        else {
            lists[left] = mergeTwoLists(lists[left], lists[right]);
            ++left;
            --right;
        }
    }
    return lists[0];
}

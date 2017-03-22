typedef struct ListNode ListNode;
ListNode* reverseList(ListNode* head) {
    ListNode*dummy = malloc(sizeof(ListNode));
    dummy->val=0;
    dummy->next=NULL;
    while (head) {
        ListNode*tmp = head->next;
        head->next   = dummy->next;
        dummy->next  = head;
        head = tmp;
    }
    return dummy->next;
}

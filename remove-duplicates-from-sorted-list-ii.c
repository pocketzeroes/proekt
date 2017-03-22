typedef struct ListNode ListNode;
ListNode*deleteDuplicates(ListNode*head){
    ListNode*dummy=malloc(sizeof(ListNode));
    ListNode*prev = dummy;
    while (head) {
        if (head->next && head->next->val == head->val) {
            int val = head->val;
            while (head && head->val == val) 
                head = head->next;
            prev->next = head;
        }
        else {
            prev->next = head;
            prev = head;
            head = head->next;
        }
    }
    return dummy->next;
}

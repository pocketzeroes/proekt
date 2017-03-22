typedef struct ListNode ListNode;
ListNode*deleteDuplicates(ListNode*head){
    ListNode*iter = head;
    while (iter) {
        ListNode*runner = iter->next;
        while (runner && runner->val == iter->val) 
            runner = runner->next;
        iter->next = runner;
        iter = runner;
    }
    return head; 
}

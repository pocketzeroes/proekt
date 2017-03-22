typedef struct ListNode ListNode;
ListNode*partition(ListNode*head, int x){
    ListNode dummy_smaller;
    ListNode dummy_larger;
    ListNode*smaller = &dummy_smaller;
    ListNode*larger  = &dummy_larger;
    while (head) {
        if (head->val < x) {
            smaller->next = head;
            smaller = smaller->next;
        } 
        else {
            larger->next = head;
            larger = larger->next;
        }
        head = head->next;
    }
    smaller->next = dummy_larger.next;
    larger->next = NULL;
    return dummy_smaller.next;
}

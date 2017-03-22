typedef struct ListNode ListNode ;
ListNode* oddEvenList(ListNode* head) {
    if (head) {
        ListNode*curr = head->next;
        for(ListNode*odd_tail = head; curr && curr->next; curr = curr->next){
            ListNode *even_head = odd_tail->next;
            odd_tail->next      = curr->next;
            odd_tail            = odd_tail->next;
            curr->next          = odd_tail->next;
            odd_tail->next      = even_head;
        }
    }
    return head; 
}

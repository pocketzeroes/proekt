typedef struct ListNode ListNode;

ListNode*mergeInBetween(ListNode*list1, int a, int b, ListNode*list2){
    ListNode* p = list1;
    for(int i = 0; i < a - 1; i += 1)
      p = p->next;
    ListNode*q = list1;
    for(int i = 0; i <= b; i += 1)
      q = q->next;
    ListNode*x = list2;
    while(x->next != NULL)
      x = x->next;
    p->next = list2;
    x->next = q;
    return list1;
}

typedef struct ListNode ListNode;
#define nullptr NULL
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *curA = headA, *curB = headB;
    ListNode *begin = nullptr, *tailA = nullptr, *tailB = nullptr;
    while (curA && curB) {
        if (curA == curB) {
            begin = curA;
            break;
        }

        if (curA->next) {
            curA = curA->next;
        } else if (!tailA) {
            tailA = curA;
            curA = headB;
        } else {
            break;
        }

        if (curB->next) {
            curB = curB->next;
        } else if (!tailB) {
            tailB = curB;
            curB = headA;
        } else {
            break;
        }
    }
    
    return begin;
}
typedef struct ListNode ListNode;

int getDecimalValue(ListNode*head){
    int ans = 0;
    while(head){
        ans <<= 1;
        ans += head->val;
        head = head->next;
    }
    return ans;
}

typedef struct ListNode ListNode;
bool isPalindrome(ListNode* head) {
    ListNode*reverse = NULL;
    ListNode*fast    = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        ListNode*head_next = head->next;
        head->next = reverse;
        reverse = head;
        head = head_next;
    }
    ListNode *tail = fast ? head->next : head;
    bool is_palindrome = true;
    while (reverse) {
        is_palindrome = is_palindrome && reverse->val == tail->val;
        ListNode*reverse_next = reverse->next;
        reverse->next = head;
        head = reverse;
        reverse = reverse_next;
        tail = tail->next;
    }
    return is_palindrome;   
}

typedef struct ListNode ListNode;
void deleteNode(ListNode* node) {
    if (!node || !node->next) 
            return;
    ListNode* node_to_delete = node->next;
    node->val = node->next->val;
    node->next = node->next->next;
}

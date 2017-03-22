typedef struct ListNode node_t;

node_t* addTwoNumbers(node_t* l1, node_t* l2) {
    node_t*root=malloc(sizeof(node_t));
    root->val  = 0;
    root->next = NULL;
    node_t* cur_node = root;
    node_t* l1_n     = l1;
    node_t* l2_n     = l2;
    int remainder = 0;
    while(l1_n || l2_n || remainder)
    {
        if (l1_n)
            cur_node->val += l1_n->val;
        if (l2_n)
            cur_node->val += l2_n->val;
        remainder = ((10 - cur_node->val) <= 0) ? 1 : 0;
        if (remainder)
            cur_node->val -= 10;
        if (l1_n != NULL) l1_n = l1_n->next;
        if (l2_n != NULL) l2_n = l2_n->next;
        if (remainder || l1_n || l2_n)
        {
            node_t*new=malloc(sizeof(node_t));
            new->val  = remainder;
            new->next = NULL;
            cur_node = cur_node->next = new;
        }
    }
    return root;
}

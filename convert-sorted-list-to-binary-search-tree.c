typedef struct TreeNode TreeNode;
typedef struct ListNode ListNode;

TreeNode*newTreeNode(int v)
{
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode * BuildBSTFromSortedSinglyListHelper(ListNode **head, int s, int e) {
    if (s == e) 
        return NULL;
    int m = s + ((e - s) / 2);
    TreeNode*left = BuildBSTFromSortedSinglyListHelper(head, s, m);
    TreeNode*curr = newTreeNode((*head)->val);
    *head = (*head)->next;
    curr->left = left;
    curr->right = BuildBSTFromSortedSinglyListHelper(head, m + 1, e);
    return curr;
}

TreeNode* sortedListToBST(ListNode* head) {
    ListNode* curr = head;
    int n = 0;
    while (curr) {
        curr = curr->next;
        ++n;
    }
    return BuildBSTFromSortedSinglyListHelper(&head, 0, n);
}


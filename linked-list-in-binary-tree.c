typedef struct ListNode ListNode;
typedef struct TreeNode TreeNode;

bool checkPath(ListNode*head, TreeNode*root){
  if(head->val != root->val) return false;
  if(head->next == NULL) return true;
  if(root->left != NULL && checkPath(head->next, root->left)) return true;
  if(root->right != NULL && checkPath(head->next, root->right)) return true;
  return false;
}
bool isSubPath(ListNode*head, TreeNode*root){
  if(checkPath(head, root)) return true;
  if(root->left != NULL && isSubPath(head, root->left)) return true;
  if(root->right != NULL && isSubPath(head, root->right)) return true;
  return false;
}

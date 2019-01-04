typedef struct TreeNode TreeNode;

bool rec(TreeNode *x, int val){
	if (!x)
        return true;
	return x->val == val && rec(x->left, val) && rec(x->right, val);
}
bool isUnivalTree(TreeNode*root){
	if (!root)
        return true;
	return rec(root, root->val);
}

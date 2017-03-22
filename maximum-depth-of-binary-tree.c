
int maxDepth(struct TreeNode *root) {
	if(NULL==root) return 0;
    
	int l_d=maxDepth(root->left);
	int r_d=maxDepth(root->right);

	return l_d>r_d? l_d+1 : r_d+1;
}


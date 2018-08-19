typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode*dfs(int*pre, int*post, int l1, int r1, int l2, int r2){
    TreeNode*ans = newTreeNode(pre[l1]);
    if(r1 - l1 == 0) 
        return NULL;
    if(r1 - l1 == 1)
        return ans;
    int I = l1, 
        J = l2;
    for(int i = l1 + 1, j = l2; i < r1; i++, j++){
        if(pre[l1 + 1] == post[j]){
            I = i; 
            J = j;
            break;
        }
    }
    ans->left  = dfs(pre, post, l1 + 1, I + 1, l2, J  + 1);
    ans->right = dfs(pre, post, I  + 1, r1, J + 1, r2 - 1);
    return ans;
}
TreeNode*constructFromPrePost(int*pre, int preSz, int*post, int postSz){
    return dfs(pre, post, 0, preSz, 0, postSz);
}

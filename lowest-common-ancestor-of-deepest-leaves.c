typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodep;

typedef struct{
  TreeNodep first;
  int       second;
}pair;

pair dfs(TreeNodep rt, int a){
    if(rt->left && rt->right){
        pair ra = dfs(rt->left, a + 1);
        pair rb = dfs(rt->right, a + 1);
        if(ra.second > rb.second)
            return ra;
        if(rb.second > ra.second)
            return rb;
        ra.first = rt;
        return ra;
    }
    else if (rt->left)
        return dfs(rt->left, a + 1);
    else if (rt->right)
        return dfs(rt->right, a + 1);
    return(pair){rt, a};
} 
TreeNode*lcaDeepestLeaves(TreeNode*root){
    return dfs(root, 0).first;
}

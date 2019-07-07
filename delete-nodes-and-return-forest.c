typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodep;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
TreeNodep*pushbackTN(TreeNodep*array, int *size, TreeNodep value){
  TreeNodep*output = resizeArray(array, TreeNodep, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	TreeNodep*ptr;
	int sz;
}vectn;
vectn newVecTN(){
	vectn rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int find(int*arr, int sz, int val){
    int i;
    for(i=0; i<sz; i++)
        if(arr[i]==val)
            return i;
    return i;
}

vectn roots;

void dfs(TreeNode*root, bool has_parent, int*to_delete, int to_deleteSz){
    if(root == NULL)
        return;
    if(find(to_delete, to_deleteSz, root->val) != to_deleteSz){
        dfs(root->left , false, to_delete, to_deleteSz);
        dfs(root->right, false, to_delete, to_deleteSz);
        return;
    }
    if(!has_parent)
        roots.ptr = pushbackTN(roots.ptr, &roots.sz, root);
    dfs(root->left , true, to_delete, to_deleteSz);
    dfs(root->right, true, to_delete, to_deleteSz);
    if (root->left  != NULL && find(to_delete, to_deleteSz, root->left ->val) != to_deleteSz) root->left  = NULL;
    if (root->right != NULL && find(to_delete, to_deleteSz, root->right->val) != to_deleteSz) root->right = NULL;
}
TreeNode**delNodes(TreeNode*root, int*to_delete, int to_deleteSz, int*rsz){
    roots = newVecTN();
    dfs(root, false, to_delete, to_deleteSz);
   *rsz=   roots.sz;
    return roots.ptr;
}

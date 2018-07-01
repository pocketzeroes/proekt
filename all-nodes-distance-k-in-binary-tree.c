typedef struct TreeNode TreeNode;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int solve(TreeNode*root, TreeNode*target, int K, int prev, vec*res){
    if(root == NULL)
        return -1;
    if(root == target){
        if(K == 0)
            res->ptr = pushback(res->ptr, &res->sz, root->val);
        solve(root->left , target, K, 0, res);
        solve(root->right, target, K, 0, res);
        return 0;
    }
    if(prev + 1 == K)
        res->ptr = pushback(res->ptr, &res->sz, root->val);
    int left  = solve(root->left , target, K, prev + 1, res);
    int right = solve(root->right, target, K, prev + 1, res);
    if(left == -1 && right == -1)
        return -1;
    if(left != -1){
        if(left + 1 == K)
            res->ptr = pushback(res->ptr, &res->sz, root->val);
        else
            solve(root->right, target, K, left + 1, res);
        return left + 1;
    }
    else{
        if(right + 1 == K)
            res->ptr = pushback(res->ptr, &res->sz, root->val);
        else
            solve(root->left, target, K, right + 1, res);
        return right + 1;
    }
}
int*distanceK(TreeNode*root, TreeNode*target, int K, int*rsz){
    vec res = newVec();
    solve(root, target, K, -1e6, &res);
   *rsz =  res.sz;
    return res.ptr;
}

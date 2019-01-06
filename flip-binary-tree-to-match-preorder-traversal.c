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
typedef struct TreeNode TreeNode;


int p = 0;
vec fed;

bool dfs(TreeNode*cur, int*voyage){
    if(cur == NULL)
        return true;
    if(voyage[p] != cur->val)
        return false;
    p++;
    if(cur->left == NULL){
        return dfs(cur->right, voyage);
    }
    if(cur->right == NULL){
        return dfs(cur->left, voyage);
    }
    if(voyage[p] == cur->left->val){
        bool res = dfs(cur->left, voyage);
        if(!res)
            return false;
        return dfs(cur->right, voyage);
    }
    else{
        fed.ptr=pushback(fed.ptr, &fed.sz, cur->val);
        bool res = dfs(cur->right, voyage);
        if(!res)
            return false;
        return dfs(cur->left, voyage);
    }
}
int*flipMatchVoyage(TreeNode*root, int*voyage, int voyageSz, int*rsz){
    p = 0;
    fed = newVec();
    if(dfs(root, voyage)){
       *rsz=fed.sz;
        return fed.ptr;
    }
    else{
        fed.sz=0;
        fed.ptr=pushback(fed.ptr, &fed.sz, -1);
       *rsz=fed.sz;
        return fed.ptr;
    }
}

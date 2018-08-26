typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodep;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
TreeNodep*pushback(TreeNodep *array, int *size, TreeNodep value) {
  TreeNodep *output = resizeArray(array, TreeNodep, *size + 1);
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

TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}
TreeNode**allPossibleFBT(int N, int*rsz){
    vectn res = newVecTN();
    if(N%2==0) 
        goto ret;
    if(N == 1){
        res.ptr = pushback(res.ptr, &res.sz, newTreeNode(0));
        goto ret;
    }
    for(int i=1; i<N; i+=2) {
        if(N-i-1 < 1) 
            continue;
        int lsz, rsz;
        TreeNode**left  = allPossibleFBT(i,     &lsz);
        TreeNode**right = allPossibleFBT(N-i-1, &rsz);
        for(int q=0; q<lsz; q++){TreeNode*l = left[q];
            for(int w=0; w<rsz; w++){TreeNode*r = right[w];
                TreeNode*temp = newTreeNode(0);
                temp->left  = l;
                temp->right = r;
                res.ptr = pushback(res.ptr, &res.sz, temp);
            }
        }
    }
  ret:
    *rsz=   res.sz;
    return res.ptr;
}

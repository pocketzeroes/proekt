typedef struct TreeNode TreeNode;

int Z[100000];
int zsz;

bool rec(TreeNode*x, int depth){
    if(!x)
        return true;
    if(x->val % 2 == depth % 2)
        return false;
    if(zsz <= depth)
        Z[zsz++]=x->val;
    else{
        if(depth % 2 == 0){
            if(Z[depth] >= x->val)
                return false;
        }
        else{
            if(Z[depth] <= x->val)
                return false;
        }
        Z[depth] = x->val;
    }
    if(!rec(x->left , depth+1))
        return false;
    if(!rec(x->right, depth+1))
        return false;
    return true;
}
bool isEvenOddTree(TreeNode*root){
    zsz=0;
	return rec(root, 0);
}

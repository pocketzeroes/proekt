int max(int a,int b){return a>b?a:b;}
typedef struct TreeNode TreeNode;
typedef struct pairS{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

int an;
pair f(TreeNode*ptr){
    if(ptr==NULL)
        return newPair(0, 0);
    pair v_left  = f(ptr->left );
    pair v_right = f(ptr->right);
    int me  = 0;
    int far = 1;
    if(v_left.first == ptr->val){
        me += v_left.second;
        far = max(far, v_left.second+1);
    }
    if(v_right.first == ptr->val){
        me += v_right.second;
        far = max(far,v_right.second+1);
    }
    an = max(an, me);
    return newPair(ptr->val, far);
}
int longestUnivaluePath(TreeNode*root){
    an = 0;
    f(root);
    return an;
}

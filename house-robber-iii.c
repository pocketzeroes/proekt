inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
typedef struct TreeNode TreeNode;
typedef struct pairS{
    int first;
    int second;
}pair;
pair empty;
pair robHelper(TreeNode*root){
    if (!root)
        return empty;
    pair left  = robHelper(root->left );
    pair right = robHelper(root->right);
    pair rez;
    rez.first =root->val + left.second + right.second;
    rez.second= max(left.first,  left.second ) + max(right.first, right.second);
    return rez;
}
int rob(TreeNode* root) {
    pair res = robHelper(root);
    return max(res.first, res.second);
}

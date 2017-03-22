#if DEBUG_ON
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
typedef struct TreeNode TreeNode;

int maxdiadepth = 0;

int dfs(TreeNode* root){        
    if(root == NULL) return 0;
    int leftdepth = dfs(root->left);
    int rightdepth = dfs(root->right);
    if(leftdepth + rightdepth > maxdiadepth) maxdiadepth = leftdepth + rightdepth;
    return max(leftdepth +1, rightdepth + 1);     
}

int diameterOfBinaryTree(TreeNode* root) {
    maxdiadepth = 0;
    dfs(root);
    return maxdiadepth;
}

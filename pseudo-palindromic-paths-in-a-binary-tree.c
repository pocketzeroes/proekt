typedef struct TreeNode TreeNode;
int count[128];
int ans;

void dfs(TreeNode *p){
    count[p->val] += 1;
    if (p->left) dfs(p->left);
    if (p->right) dfs(p->right);
    if (!p->left && !p->right) {
        int odd_cnt = 0;
        for (int i = 0; i < 10; ++i)
            if (count[i] & 1) ++odd_cnt;
        if (odd_cnt <= 1) ++ans;
    }
    count[p->val] -= 1;
}
int pseudoPalindromicPaths (TreeNode* root){
    memset(count, 0, sizeof count);
    ans = 0;
    dfs(root);
    return ans;
}

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct TreeNode TreeNode;
int distance = INT_MAX;
int value = -1;

int find(TreeNode*root, int knownDistance, int target) {
    if (root == NULL) {
        return -1;
    }
    if (root->val == target) {
        if (root->left == NULL && root->right == NULL) {
            distance = 0;
            value = target;
        }
        else {
            find(root->left , 1, target);
            find(root->right, 1, target);
        }
        return 1;
    }
    else if (knownDistance != -1) {
        if (root->left == NULL && root->right == NULL) {
            if (distance > knownDistance) {
                distance = knownDistance;
                value = root->val;
            }
        }
        else {
            find(root->left , knownDistance + 1, target);
            find(root->right, knownDistance + 1, target);
        }
        return -1;
    }
    else {
        int left  = find(root->left , -1, target);
        int right = find(root->right, -1, target);
        if (left != -1 || right != -1) {
            int dis = max(left, right);
            if (left == -1) {
                find(root->left, dis + 1, target);
            }
            if (right == -1) {
                find(root->right, dis + 1, target);
            }
            return dis + 1;
        }
        else {
            return -1;
        }
    }
}
int findClosestLeaf(TreeNode*root, int k){
    distance = INT_MAX;
    value = -1;
    find(root, -1, k);
    return value;
}


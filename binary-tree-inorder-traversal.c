#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct TreeNode TreeNode;
int*inorderTraversal(TreeNode*root, int*returnSize){
    int*res=NULL;
    TreeNode *curr = root;
    while (curr) {
        if (!curr->left) {
            res = pushback(res, returnSize, curr->val);
            curr = curr->right;
        }
        else {
            TreeNode *node = curr->left;
            while (node->right && node->right != curr) 
                node = node->right;
            if (!node->right) {
                node->right = curr;
                curr = curr->left;
            }
            else {
                res = pushback(res, returnSize, curr->val);
                node->right = NULL;
                curr = curr->right;
            }
        }
    }
    return res;
}

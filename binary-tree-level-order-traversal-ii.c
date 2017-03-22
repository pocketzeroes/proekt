void traverse(struct TreeNode *root, int depth, int ***arr, int **columnSizes, int *returnSize)
{
    int     idx;
    if (!root) return;
    traverse(root->left, depth + 1, arr, columnSizes, returnSize);
    traverse(root->right, depth + 1, arr, columnSizes, returnSize);
    idx = *returnSize - depth - 1;
    (*arr)[idx] = realloc((*arr)[idx], ((*columnSizes)[idx] + 1) * sizeof(int));
    (*arr)[idx][(*columnSizes)[idx]] = root->val;
    ++(*columnSizes)[idx];
}

void maxdepth(struct TreeNode *root, int depth, int ***arr, int **columnSizes, int *returnSize)
{
    if (!root) return;
    if (*returnSize < depth + 1) {
        *returnSize = depth + 1;
        *arr = realloc(*arr, (depth + 1) * sizeof(int *));
        (*arr)[depth] = NULL;
        *columnSizes = realloc(*columnSizes, (depth + 1) * sizeof(int));
        (*columnSizes)[depth] = 0;
    }
    maxdepth(root->left, depth + 1, arr, columnSizes, returnSize);
    maxdepth(root->right, depth + 1, arr, columnSizes, returnSize);
}

int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    int **arr;
    arr = NULL;
    *returnSize = 0;
    maxdepth(root, 0, &arr, columnSizes, returnSize);
    traverse(root, 0, &arr, columnSizes, returnSize);
    return arr;
}


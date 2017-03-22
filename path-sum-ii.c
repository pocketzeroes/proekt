void traverse(struct TreeNode *root, int accu, int sum, int *tmp, int count, int ***arr, int **columnSize, int *returnSize)
{
    if (!root) return;
    if (!root->left && !root->right) {
        if (accu + root->val == sum) {
            ++*returnSize;
            (*columnSize) = realloc(*columnSize, *returnSize * sizeof **columnSize);
            (*arr) = realloc(*arr, *returnSize * sizeof **arr);
            (*columnSize)[*returnSize - 1] = count + 1;
            (*arr)[*returnSize - 1] = malloc((*columnSize)[*returnSize - 1] * sizeof ***arr);
            memcpy((*arr)[*returnSize - 1], tmp, count * sizeof tmp[0]);
            (*arr)[*returnSize - 1][count] = root->val;
        }
    }
    else {
        int t[count + 1];
        memcpy(t, tmp, count * sizeof tmp[0]);
        t[count] = root->val;
        traverse(root->left,  accu + root->val, sum, t, count + 1, arr, columnSize, returnSize);
        traverse(root->right, accu + root->val, sum, t, count + 1, arr, columnSize, returnSize);
    }
}

int** pathSum(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {
    int **arr;
    int tmp[0];
    *returnSize = 0;
    *columnSizes = NULL;
    arr = NULL;
    traverse(root, 0, sum, tmp, 0, &arr, columnSizes, returnSize);
    return arr;
}

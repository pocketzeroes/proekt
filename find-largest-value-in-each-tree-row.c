#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int*solution;
typedef struct TreeNode TreeNode;
void helper(TreeNode* node, int cl,int*rsz){
    if (node == NULL)
        return;
    if (*rsz < cl + 1)
        solution=pushback(solution,rsz,node->val);
    else {
        if (solution[cl] < node->val)
            solution[cl] = node->val;
    }
    helper(node->left,  cl+1,rsz);
    helper(node->right, cl+1,rsz);
}
int*largestValues(TreeNode* root,int*rsz){
    solution=NULL;
    if(root == NULL)
        return solution;
    helper(root, 0,rsz);
    return solution;
}

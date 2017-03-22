#define LEN 1000
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int retSize=0;
    if(!root) return NULL;
    int*arr=(int*)malloc(sizeof(int)*LEN);
    struct TreeNode**stack=(struct TreeNode*)malloc(sizeof(struct TreeNode*)*LEN);
    int top=-1;
    stack[++top]=root;
    struct TreeNode *pre=NULL;
    while(top>-1)
    {
        struct TreeNode *cur=stack[top];
        if(!pre||pre->left==cur||pre->right==cur)
        {
            if(cur->left) stack[++top] = cur->left;
            else if(cur->right) stack[++top] = cur->right;
            else arr[retSize++] = cur->val,top--;
        }
        else if(cur->left == pre)
        {
            if(cur->right) stack[++top] = cur->right;
            else arr[retSize++] = cur->val,top--;
        }
        else if(cur->right==pre)
            arr[retSize++] = cur->val,top--;
        pre = cur;
    }
   *returnSize=retSize;
    return arr;
}

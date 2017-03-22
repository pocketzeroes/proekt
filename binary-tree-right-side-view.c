#define BUFFSZ 1000
int *result;
int  count;
int  view [BUFFSZ];
bool found[BUFFSZ];
  
void helper(struct TreeNode* root, int level)
{
    if(!root)
        return;
    if(!found[level])
    {
        view [count++] = root->val;
        found[level  ] = true;
    }
    helper(root->right, level+1);
    helper(root->left,  level+1);
}
void store()
{
    int i;
    if(count == 0)
       return;
    result = (int*)malloc(sizeof(int)*count);
    if(!result)
        exit(1);
    for(i=0; i<count; i++)
       result[i] = view[i];
    for(i=0; i<BUFFSZ; i++)
       found[i] = false;
}
int* rightSideView(struct TreeNode* root, int* returnSize) {
    count  = 0;
    result = NULL;
    helper(root, 0);
    store();
    *returnSize = count;
    return result;
}

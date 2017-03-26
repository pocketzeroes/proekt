#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


typedef struct TreeNode TreeNode;
int*Res;
int ResSz;

void PrintInner(TreeNode *r, int*V)
{
    if(r == NULL)
        return;
    if(r->left == NULL && r->right == NULL)
    {
        Res=pushback(Res,&ResSz,r->val);
        return;
    }
    PrintInner(r->left, V);
    PrintInner(r->right,V);
}
void PrintRightBoundry(TreeNode *root, int*V)
{
    if(root == NULL)
        return;
    if(root->right)
    {
        PrintInner(root->left,V);
        PrintRightBoundry(root->right,V);
    }
    else
        PrintRightBoundry(root->left,V);
    Res=pushback(Res, &ResSz,root->val);
}
void PrintLeftBoundry(TreeNode *root, int*V)
{
    if(root == NULL)
        return;
    Res=pushback(Res, &ResSz, root->val);
    if(root->left)
    {
        PrintLeftBoundry(root->left ,V);
        PrintInner      (root->right,V);
    }
    else
        PrintLeftBoundry(root->right,V);
}
int*boundaryOfBinaryTree(TreeNode*root, int*rsz)
{   
    Res=NULL;
    ResSz = 0;
    if(!root) return NULL;
    Res = pushback(Res, &ResSz, root->val);
    PrintLeftBoundry (root->left, Res);
    PrintRightBoundry(root->right,Res);
   *rsz = ResSz;
    return Res;
}













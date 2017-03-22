#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TREE_DEBUG 0

#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

#if TREE_DEBUG
struct TreeNode {
    int              val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
typedef struct TreeNode TreeNode;

TreeNode**pushback(TreeNode**array, int*size, TreeNode*value) {
    TreeNode**output = resizeArray(array, TreeNode*, *size + 1);
    output[(*size)++] = value;
    return output;
}

TreeNode*newTreeNode(int v)
{
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode *clone(TreeNode *root) {
    TreeNode *newRoot = NULL;
    if (root) {
        newRoot = newTreeNode (root->val  );
        newRoot->left  = clone(root->left );
        newRoot->right = clone(root->right);
    }
    return newRoot;
}

TreeNode**generateTreesHelper(int start, int end, int*rsz){
    TreeNode ** result=NULL;
    if (start > end) {
        result = pushback(result, rsz, NULL);
        return result;
    }
    for (int i = start; i <= end; ++i) {
        int leftSz =0;
        int rightSz=0;
        TreeNode**leftSubTrees  = generateTreesHelper(start, i - 1,&leftSz );
        TreeNode**rightSubTrees = generateTreesHelper(i + 1, end  ,&rightSz);
        for (int z=0;z<leftSz;z++) {
            TreeNode*left = leftSubTrees[z];
            for (int j=0;j<rightSz;j++){
                TreeNode*right=rightSubTrees[j];
                TreeNode *root = newTreeNode(i);
                root->left  = clone(left);
                root->right = clone(right);
                result = pushback(result, rsz, root);
            }
        }
    }
    return result;
}

TreeNode** generateTrees(int n,int*rsz) {
    if (n == 0) 
        return NULL;
    return generateTreesHelper(1, n, rsz);
}
#if TREE_DEBUG
int main(){
// Output:  [[0,null,0,null,0],[0,null,0,0],[0,0,0],[0,0,null,null,0],[1,0,null,0]]
// Expected:[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]    
    int ss;
    generateTrees(3,&ss);
}
#endif


















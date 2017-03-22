#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG_ON 0

#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

#if DEBUG_ON
struct Interval {
    int start;
    int end;
};
#endif
typedef struct Interval Interval;


Interval*pushback(Interval*array, int*size, Interval value) {
    Interval*output = resizeArray(array, Interval, *size + 1);
    output[(*size)++] = value;
    return output;
}

#define null NULL

typedef struct TreeNodeS {
    Interval*interval;
    struct TreeNodeS*left;
    struct TreeNodeS*right;
}TreeNode;
TreeNode*root;
Interval*list;
int*listSz;
typedef struct {
    int a;
} SummaryRanges;
SummaryRanges*ptr;


Interval*newInterval(int a, int b){
    Interval*rez=malloc(sizeof(Interval));
    rez->start=a;
    rez->end  =b;
    return rez;
}
TreeNode*newTreeNode(Interval*in){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->interval = in;
    res->left     = NULL;
    res->right    = NULL;
    return res;
}
SummaryRanges*summaryRangesCreate(){                                            /*public*/
    root=NULL;
    list=NULL;
    listSz=malloc(sizeof(int));
    return ptr;
}
TreeNode*findMin(TreeNode*root) {
    if (root       == null) return null;
    if (root->left == null) return root;
    else return findMin(root->left);
}
TreeNode*removeEl(Interval*x, TreeNode*root){
    if    (root == null) return null;
    else if ( x == null) return root;
    else if (x->start > root->interval->end ) 
        root->right = removeEl(x, root->right);
    else if (x->end < root->interval->start )
        root->left = removeEl(x, root->left);
    else if ( root->left != null && root->right != null){
        TreeNode*el=findMin(root->right);
        root->interval = el->interval;
        root->right = removeEl( root->interval, root->right);
    }
    else 
        root = ( root->left != null ) ? root->left : root->right;
    return root;
}
TreeNode*findKey(int val, TreeNode*root){
    if (root == null) return null;
    if (root->interval->start > val){
        return findKey(val, root->left);
    }
    else if (root->interval->end < val){
        return findKey(val, root->right);
    }
    else
        return root;
}
TreeNode*addKey(int val, TreeNode*root){
    if (root == null) {
        root = newTreeNode( newInterval(val, val) );
    }
    else if (root->interval->start > val){
        root->left = addKey(val, root->left);
    }
    else if (root->interval->end < val){
        root->right = addKey(val, root->right);
    }
    return root;
}
void inOrder(TreeNode*root){
    if (root != null) {
        inOrder(root->left);
        list = pushback(list, listSz, *(root->interval));
        inOrder(root->right);
    }
}
void summaryRangesAddNum(SummaryRanges* obj, int val){                          /*public*/
    if (root == null) {
        root = addKey(val, root);
    }
    else {
        if ( findKey(val, root) != null)
            return;
        TreeNode*left  = findKey(val-1, root);
        TreeNode*right = findKey(val+1, root);
        if (left == null && right == null)
            root = addKey(val, root);
        else if (left != null && right == null)
            left->interval->end++;
        else if (left == null && right != null)
            right->interval->start--;
        else {
            Interval*l = left->interval;
            int e = right->interval->end;
            root = removeEl(right->interval, root);
            l->end = e;
        }
    }
}
Interval*summaryRangesGetIntervals(SummaryRanges* obj, int*returnSize){         /*public*/
    list=NULL;
   *listSz=0;
    inOrder(root);
   *returnSize= *listSz;
    return list;
}
void summaryRangesFree(SummaryRanges* obj) {                                    /*public*/
    free(list);
    list=NULL;
    ptr=NULL;
}



#if DEBUG_ON
int main(){
    
}
#endif


































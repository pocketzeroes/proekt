#define nullptr NULL
typedef struct BSTreeNodeS{
    int val, count;
    struct BSTreeNodeS *left;
    struct BSTreeNodeS *right;
}BSTreeNode;

BSTreeNode*newBSTreeNode(int val, int count) {
    BSTreeNode*rez=malloc(sizeof(BSTreeNode));
    rez->val = val;
    rez->count = count;
    rez->left = rez->right = nullptr;
    return rez;
}
BSTreeNode* insertNode(BSTreeNode* root, BSTreeNode* node) {
    if (root == nullptr)
        return node;
    BSTreeNode* curr = root;
    while (curr) {
        if (node->val < curr->val) {
            ++curr->count;
            if (curr->left != nullptr) 
                curr = curr->left;
            else {
                curr->left = node;
                break;
            }
        } 
        else { 
            if (curr->right != nullptr)
                curr = curr->right;
            else {
                curr->right = node;
                break;
            }
        }
    }
    return root;
}
int query(BSTreeNode* root, int val) {
    if (root == nullptr)
        return 0;
    int count = 0;
    BSTreeNode* curr = root;
    while (curr) {
        if (val < curr->val)
            curr = curr->left;
        else if (val > curr->val) {
            count += 1 + curr->count;
            curr = curr->right;
        }
        else
            return count + curr->count;
    }
    return 0;
}
int*countSmaller(int*nums , int numsSize,int* returnSize){
    int*res=malloc(numsSize*sizeof(int));
    BSTreeNode *root = nullptr;
    for (int i = numsSize - 1; i >= 0; --i) {
        BSTreeNode *node = newBSTreeNode(nums[i], 0);
        root = insertNode(root, node);
        res[i] = query(root, nums[i]);
    }
   *returnSize=numsSize;
    return res;
}






















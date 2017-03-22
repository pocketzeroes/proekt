typedef struct TreeLinkNode TreeLinkNode;
void connect(TreeLinkNode *root){
    for(TreeLinkNode *list, *first; root; root = first) {
        list = first = NULL;
        for(; root; root = root->next) {
            if(!first) first = (root->left)? root->left:root->right;
            if(root->left) {
                if(list) list->next = root->left;
                list = root->left;
            }
            if(root->right) {
                if(list) list->next = root->right;
                list = root->right;
            }
        }
    }
}

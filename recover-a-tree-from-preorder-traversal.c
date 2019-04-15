typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

int pos = 0;
char*s;
int len = 0;

bool hasEdge(int d){
    if(pos+d > len-1)
        return false;
    for(int i = pos; i < pos+d; i++)
        if(s[i] != '-')
            return false;
    return s[pos+d] != '-';
}
TreeNode*go(int dep){
    int v = 0;
    while(pos < len && s[pos] >= '0' && s[pos] <= '9'){
        v = v * 10 + (s[pos]-'0');
        pos++;
    }
    TreeNode*cur = newTreeNode(v);
    if(hasEdge(dep+1)){
        pos += dep+1;
        cur->left = go(dep+1);
    }
    if(hasEdge(dep+1)){
        pos += dep+1;
        cur->right = go(dep+1);
    }
    return cur;
}
TreeNode*recoverFromPreorder(char*S){
    len = strlen(S);
    s = strdup(S);
    pos = 0;
    return go(0);
}

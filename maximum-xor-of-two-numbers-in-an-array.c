typedef struct TreeNodeS {
    struct TreeNodeS* next[2];
}TrieNode;
TrieNode*newTreeNode () {
    TrieNode*rez=malloc(sizeof(TrieNode));
    rez->next[0] = NULL; 
    rez->next[1] = NULL;
    return rez;
};
TrieNode* buildTree(int*nums,int numsSz) {
    TrieNode* root = newTreeNode();
    TrieNode*cur;
    int n = numsSz;
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        cur = root;
        for (int j = 31; j >= 0; j--) {
            int index = ((num >> j) & 1);
            if (cur->next[index] ==  NULL)
                cur->next[index] = newTreeNode();
            cur = cur->next[index];
        }
    }
    return root;
}

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int helper(TrieNode* cur, int num) {
    int res = 0;
    for (int i = 31; i >= 0; i--) {
        int index = ((num >> i) & 1) ? 0 : 1;
        if (cur->next[index]) {
            res <<= 1;
            res |= 1;
            cur = cur->next[index];
        } else {
            res <<= 1;
            res |= 0;
            cur = cur->next[index ? 0 : 1];
        }
    }
    return res;
}
int findMaximumXOR(int*nums,int numsSz) {
    int res = 0;
    TrieNode* root = buildTree(nums,numsSz);
    for (int z=0;z<numsSz;z++){
        int i = nums[z];
        res = max(res, helper(root, i));
    }
    return res;
}













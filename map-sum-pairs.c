typedef struct TrieNode{
    struct TrieNode**next;
    int value;
}TrieNode;
TrieNode*newTrieNode(){
    TrieNode*rez = malloc(sizeof(TrieNode));
    rez->next  = calloc(256, sizeof(TrieNode*));
    rez->value = 0;
    return rez;
}
TrieNode*root;

typedef struct {
} MapSum;
MapSum*ptr;

MapSum*mapSumCreate(){
    root = newTrieNode();
    return ptr;
}
void update(char*key, int val){
    TrieNode*cur = root;
    for (int i = 0; key[i]; i++) {
        int c = key[i];
        if (cur->next[c] == NULL)
            cur->next[c] = newTrieNode();
        cur = cur->next[c];
    }
    cur->value = val;
}
void mapSumInsert(MapSum* obj, char* key, int val){
    update(key, val);
}

int dfs(TrieNode*cur){
    if (cur == NULL)
        return 0;
    int sum = 0;
    sum += cur->value;
    for(int i = 0; i < 256; i++)
        sum += dfs(cur->next[i]);
    return sum;
}
int mapSumSum(MapSum* obj, char*prefix){
    TrieNode*cur = root;
    for (int i = 0; prefix[i]; i++){
        int c = prefix[i];
        if(cur->next[c] == NULL)
            return 0;
        cur = cur->next[c];
    }
    return dfs(cur);
}
void mapSumFree(MapSum* obj) {
    if(root)free(root);
    ptr=NULL;
}






























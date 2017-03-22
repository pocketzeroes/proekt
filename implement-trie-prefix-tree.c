typedef struct TrieS
{
    struct TrieS *next[26];
    bool is_word;
}Trie;
Trie*newTrieNode()
{
    Trie*rez=malloc(sizeof(Trie));
    memset(rez->next, 0, sizeof(rez->next));
    rez->is_word = false;
    return rez;
}
Trie*root;
    
Trie* trieCreate() {
    root = newTrieNode();
    return root;
}
void trieInsert(Trie* obj, char* s) {
    Trie *p = root;
    for(int i = 0; s[i]; ++ i)
    {
        if(p -> next[s[i] - 'a'] == NULL)
            p -> next[s[i] - 'a'] = newTrieNode();
        p = p -> next[s[i] - 'a'];
    }
    p -> is_word = true;
}
Trie* find(char* key)
{
    Trie *p = root;
    for(int i = 0; key[i] && p != NULL; ++ i)
        p = p -> next[key[i] - 'a'];
    return p;
}

bool trieSearch(Trie* obj, char* key) {
    Trie *p = find(key);
    return p != NULL && p -> is_word;
}

bool trieStartsWith(Trie* obj, char* prefix) {
    return find(prefix) != NULL;
}
void trieFree(Trie*t){
    root=NULL;
}

typedef struct TrieS
{
    struct TrieS *next[26];
    bool is_word;
}WordDictionary;
WordDictionary*newTrieNode()
{
    WordDictionary*rez=malloc(sizeof(WordDictionary));
    memset(rez->next, 0, sizeof(rez->next));
    rez->is_word = false;
    return rez;
}
WordDictionary*root;
    
WordDictionary* wordDictionaryCreate() {
    root = newTrieNode();
    return root;
}
void wordDictionaryAddWord(WordDictionary* obj, char* s) {
    WordDictionary *p = root;
    for(int i = 0; s[i]; ++ i)
    {
        if(p -> next[s[i] - 'a'] == NULL)
            p -> next[s[i] - 'a'] = newTrieNode();
        p = p -> next[s[i] - 'a'];
    }
    p -> is_word = true;
}

bool query(char* word, WordDictionary* node) {
    WordDictionary* run = node;
    for (int i = 0; word[i]; i++) {
        if (run && word[i] != '.')
            run = run->next[word[i] - 'a'];
        else if (run && word[i] == '.') { 
            WordDictionary*tmp = run;
            for (int j = 0; j < 26; j++) {
                run = tmp->next[j];
                if (query(word + i + 1, run))
                    return true;
            }
        }
        else
            break;
    }
    return run && run->is_word; 
}

bool wordDictionarySearch(WordDictionary* obj, char* key) {
    return query(key,root);
}

void wordDictionaryFree(WordDictionary*t){
    root=NULL;
}



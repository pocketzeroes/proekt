typedef struct{
    char key[2001];
    UT_hash_handle hh;
}HashNode;
bool isSame(char *s1, char *s2, int len){
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}
int distinctEchoSubstrings(char * text){
    HashNode *head = NULL;
    int len = strlen(text);
    for (int i = 0; i < len - 1; i++) {
        int max = (len - i) / 2;
        char k[2001];
        memcpy(k, text+i, max);
        memcpy(k+max, text+i, max);
        k[2*max] = 0;
        HashNode *n;
        HASH_FIND_STR(head, k, n);
        if (n)
            continue;
        for (int j = 1; j <= max; j++) {
            if(!isSame(text+i, text+i+j, j))
                continue;
            char key[2001];
            memcpy(key, text+i, j);
            memcpy(key+j, text+i, j);
            key[2*j] = 0;
            HashNode *node;
            HASH_FIND_STR(head, key, node);
            if (node)
                continue;
            node = malloc(sizeof(HashNode));
            strcpy(node->key, key);
            HASH_ADD_STR(head, key, node);
        }
    }
    return HASH_COUNT(head);
}

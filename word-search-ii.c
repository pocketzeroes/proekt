#define PLACEHOLDER '#'
#define SIZE 26
struct TrieNode
{
    bool isWord;
    struct TrieNode **children;
};

struct TrieNode* nodeMaker()
{
    struct TrieNode *t = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    t->isWord = false;
    int space = sizeof(struct TrieNode*)*SIZE;
    t->children = (struct TrieNode**)malloc(space);
    memset(t->children, 0, space);
    return t;
}

struct TrieNode* addWords(char** words, int size)
{
    struct TrieNode *root = nodeMaker();
    struct TrieNode *cur;
    for(int i = 0; i < size; i++)
    {
        cur = root; 
        for(int j = 0; words[i][j]; j++)
        {
            int index = words[i][j]-'a';
            if(!(cur->children[index]))
                cur->children[index] = nodeMaker();
            cur = cur->children[index];
        }
        cur->isWord = true;
    }
    return root;
}

void traverse(char** board, int rSize, int cSize, int r, int c, struct TrieNode* root, char* stack, int top, char*** arr, int* returnSize)
{
    if(r<0 || c<0 || r==rSize || c==cSize || board[r][c]==PLACEHOLDER) return ; 
    char a = board[r][c];
    root = root->children[a-'a'];
    if(!root) return ;
    stack[++top] = a;
    if(root->isWord) 
    {
        *returnSize += 1;
        *arr = (char**)realloc(*arr, sizeof(char*)*(*returnSize));
        int len = top+1;
        (*arr)[*returnSize-1] = (char*)malloc(sizeof(char)*(len+1));
        for(int i = 0; i < len; i++)
            (*arr)[*returnSize-1][i] = stack[i];
        (*arr)[*returnSize-1][len] = '\0';
        root->isWord = false; 
    }
    board[r][c] = PLACEHOLDER; 
    traverse(board, rSize, cSize, r+1, c, root, stack, top, arr, returnSize);
    traverse(board, rSize, cSize, r-1, c, root, stack, top, arr, returnSize);
    traverse(board, rSize, cSize, r, c+1, root, stack, top, arr, returnSize);
    traverse(board, rSize, cSize, r, c-1, root, stack, top, arr, returnSize);
    board[r][c] = a; 
}
char** findWords(char** board, int rSize, int cSize, char** words, int wSize, int* returnSize)
{
    struct TrieNode *root = addWords(words, wSize);
    char** arr = (char**)malloc(sizeof(char*));
    char* stack = (char*)malloc(sizeof(char)*SIZE*2);
    int top = -1;
    for(int r = 0; r < rSize; r++) 
        for(int c = 0; c < cSize; c++)
            traverse(board, rSize, cSize, r, c, root, stack, top, &arr, returnSize);
    return arr;
}






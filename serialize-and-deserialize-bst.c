#define LEN 20
char* serializeHelper(struct TreeNode* root, int* len)
{
    *len = 2;
    if(!root) return "X,";
    char *t = (char*)malloc(sizeof(char)*LEN);
    int size = 0;
    int val = root->val;
    while(val) 
    {
        t[size++] = val%10 + '0';
        val /= 10;
    }
    for(int i = 0; i < size/2; i++) 
    {
        char c = t[size-i-1]; t[size-i-1]=t[i]; t[i]=c;
    }
    t[size++] = ','; 
    t[size] = '\0';
    int leftLen=0, rightLen=0;
    char *left  = serializeHelper(root->left,  &leftLen );
    char *right = serializeHelper(root->right, &rightLen);
    *len = size+leftLen+rightLen+2;
    t = (char*)realloc(t, sizeof(char)*(*len));
    strcat(t, left );
    strcat(t, right);
    return  t;
}
char* serialize(struct TreeNode* root)
{
    int len = 0;
    return serializeHelper(root, &len);
}
struct TreeNode* helper(char** s)
{
    if(**s == 'X') return NULL;
    int num = 0;
    while(**s != ',') 
        num = 10*num + *((*s)++) - '0';
    *s += 1; 
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val  = num;
    root->left = helper(s);
    while(*((*s)++) != ',');
    root->right = helper(s);
    return root;
}
struct TreeNode* deserialize(char* s)
{
    return helper(&s);
}



















































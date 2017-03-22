typedef struct TreeNode TreeNode;

#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef TreeNode* T;
typedef struct
{
    T *bottom;
    T *top;
    T *allocated_top;
} 
stack;
stack * new(void)
{
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
void destroy(stack *s)
{
  free(s->bottom);
  free(s);
}
bool empty(stack *s)
{
    return s->top < s->bottom ? true : false;
}
void push(stack *s, T x)
{
    if (s->top == s->allocated_top)
    {
        ptrdiff_t qtty = s->top - s->bottom + 1;
        ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
        s->bottom = realloc(s->bottom, new_qtty * sizeof(T));
        check_pointer(s->bottom);
        s->top = s->bottom + qtty - 1;
        s->allocated_top = s->bottom + new_qtty - 1;
    }
    *(++s->top) = x;
}
T pop(stack *s)
{
    return *(s->top--);
}
T top(stack *s)
{
    return *(s->top);
}

stack*s;
TreeNode*cur;

typedef struct BSTIterator {
  int a;  
}BSTIterator;

BSTIterator *bstIteratorCreate(TreeNode *root) {
  cur=root;  
  s=new();
  return cur;
}

bool bstIteratorHasNext(BSTIterator *iter) {
    return !empty(s) || cur != NULL;    
}

int bstIteratorNext(BSTIterator *iter) {
    while (cur != NULL) {
        push(s,cur);
        cur = cur->left;
    }
    cur = top(s); 
    pop(s);
    TreeNode *node = cur;
    cur = cur->right; 
    return node->val;    
}

void bstIteratorFree(BSTIterator *iter) {
  s=NULL;  
  cur=NULL;  
}










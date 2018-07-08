typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
}node;
#define dummy dp->head
typedef struct deque
{
    int count;
    node*head;
}deque;
deque *newDeque(void)
{
    node *sentinel = malloc(sizeof(node));
    deque *dp = malloc(sizeof(deque));
    assert(dp != NULL && sentinel != NULL);
    sentinel -> prev = sentinel;
    sentinel -> next = sentinel;
    dummy = sentinel;
    dp -> count = 0;
    return dp;
}
void destroyDeque(deque *dp)
{
    node *temp, *prev;
    temp = prev = dummy -> next;
    while (temp != dummy)
    {
        temp = temp -> next;
        free(prev);
        prev = temp;
    }
    free(dummy);
    free(dp);
}
int numItems(deque *dp)
{
    assert(dp != NULL);
    return dp->count;
}
bool empty(deque *dp)
{
    assert(dp != NULL);
    return dp->count == 0;
}
void push_front(deque *dp, int x)
{
    assert(dp != NULL);
    dp->count++;
    node *newNode = malloc(sizeof(node));
    newNode->data = x;
    newNode->next = dummy -> next;
    newNode->prev = dummy;
    dummy->next->prev = newNode;
    dummy->next = newNode;
}
void push_back(deque *dp, int x)
{
    assert(dp != NULL);
    dp -> count++;
    node *newNode = malloc(sizeof(node));
    newNode -> data = x;
    newNode -> prev = dummy -> prev;
    newNode -> next = dummy;
    dummy -> prev -> next = newNode;
    dummy -> prev = newNode;
}
int pop_front(deque *dp)
{
    assert(dp != NULL && dp -> count > 0);
    dp -> count--;
    node *temp = dummy -> next;
    dummy -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int pop_back(deque *dp)
{
    assert(dp != NULL && dp -> count > 0);
    dp->count--;
    node *temp = dummy -> prev;
    dummy -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    int x = temp -> data;
    free(temp);
    return x;
}
int removePosition(deque *dp, int position)
{
    assert(dp != NULL);
    dp -> count--;
    int i;
    node *temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
    int x = temp -> data;
    free(temp);
    return x;
}
int front(deque *dp)
{
    assert(dp != NULL && dummy -> next != NULL);
    return dummy->next->data;
}
int back(deque *dp)
{
    assert(dp != NULL && dummy -> prev != NULL);
    return dummy -> prev -> data;
}
int getPosition(deque *dp, int position)
{
    assert(dp != NULL && position <= dp -> count);
    int i;
    node* temp = malloc(sizeof(node));
    temp = dummy -> next;
    for (i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    return temp -> data;
}
int search(deque *dp, int x)
{
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    int found = 0;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next; 
    for (i = 0; i < dp -> count; i++)
    {
        if(temp -> data == x)
        {
            found = 1;
            printf("found %d!\n", x);
            break;
        }
        else
        {
            temp = temp -> next;
            position++;
        }
    }
    if (found == 1)
        return position;
    else
        return -1;
}
void printDeque(deque *dp)
{
    assert(dp != NULL && dp -> count != 0);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < dp -> count; i++)
    {
        printf("\nnode %d: %d\n", i, temp -> data);
        temp = temp -> next;
    }
    printf("\ncount: %d\n", dp -> count);
    return;
}
void moveToFirst(deque *dp, int position)
{
    assert(dp != NULL && dp -> count >= position);
    int i = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> next -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    temp -> next = dummy -> next;
    temp -> prev = dummy;
    dummy -> next -> prev = temp;
    dummy -> next = temp;   
    return;
};
void UpdateData(deque *dp, int position, int data)
{
    assert(dp != NULL);
    assert(dp -> count >= position);
    int i;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    for(i = 0; i < position; i++)
    {
        temp = temp -> next;
    }
    temp -> data = data;
    return;
}
int findMin(deque *dp)
{
    assert(dp != NULL);
    int min, i;
    int position = 0;
    node *temp = malloc(sizeof(node));
    temp = dummy -> next;
    min = temp -> data;
    temp = temp -> next;
    for(i = 1; i < dp -> count; i++)
    {
        if(temp -> data <= min)
        {
            position = i;
            min = temp -> data;
        }
    }
    return position;
}

////////////////
int t[32][32][1 << 6];
int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
int n, m;
char**g;

int go(int r, int c){
    int all = 0;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j) {
            if ('a' <= g[i][j] && g[i][j] <= 'z') {
                all |= 1 << (g[i][j] - 'a');
            }
        }
    memset(t, 0xff, sizeof(t));
    t[r][c][0] = 0;
    deque*que = newDeque();
    push_back(que, (r << 12) + (c << 6) + 0);
    while (!empty(que)) {
        int key = front(que); pop_front(que);
        r = key >> 12;
        c = (key >> 6) & 0x3f;
        int k = key & 0x3f;
        for (int d = 0; d < 4; ++d) {
            int r1 = r + dr[d], c1 = c + dc[d];
            if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= m) 
                continue;
            char ch = g[r1][c1];
            if ('#' == ch) 
                continue;
            if ('A' <= ch && ch <= 'Z') {
                int x = 1 << (ch - 'A');
                if (!(k & x)) 
                    continue;
            }
            int k1 = k;
            if ('a' <= ch && ch <= 'z')
                k1 |= (1 << (ch - 'a'));
            if (t[r1][c1][k1] < 0) {
                t[r1][c1][k1] = t[r][c][k] + 1;
                if (k1 == all)
                    return t[r1][c1][k1];
                push_back(que, (r1 << 12) + (c1 << 6) + k1);
            }
        }
    }
    return -1;
}
int shortestPathAllKeys(char**grid, int gridSz){
    g = grid;
    n = gridSz;
    if (n < 1)
        return -1;
    m = strlen(g[0]);
    if (m < 1)
        return -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if ('@' == g[i][j])
                return go(i, j);
        }
    return -1;
}



#define LEN 10000
struct MyListNode
{
    long long key;
    int val;
    struct MyListNode *next;
};
void push(struct MyListNode* head, long long key, int val)
{
    struct MyListNode *p = head;
    while(p->next)
        p = p->next;
    struct MyListNode *t = (struct MyListNode*)malloc(sizeof(struct MyListNode));
    t->key = key;
    t->val = val;
    p->next = t;
}
int pop(struct MyListNode* head, long long key)
{
    struct MyListNode *p = head->next;
    while(p)
    {
        if(p->key == key)
            return p->val;
        p = p->next;
    }
    return 0;
}
char* fractionToDecimal(int n, int d)
{
    if(n == 0) return "0";
    char *s = (char*)malloc(sizeof(char)*LEN);
    int index = 0;
    if((n<0 && d>0) || (n>0 && d<0)) s[index++] = '-'; 
    long long numerator = (n==INT_MIN)? -1*(long long)n : abs(n); 
    long long denominator = (d==INT_MIN)? -1*(long long)d : abs(d); 
    long long integer = numerator/denominator; 
    if(integer == 0)
        s[index++] = '0';
    else
    {
        char *t = (char*)malloc(sizeof(char)*LEN); 
        int index0 = 0;
        while(integer)
        {
            t[index0++] = integer%10+'0';
            integer /= 10;
        }
        for(int i = index0-1; i > -1; i--) 
            s[index++] = t[i];
    }
    long long remainder = numerator%denominator; 
    if(remainder == 0) 
    {
        s[index] = '\0';
        return s;
    }
    s[index++] = '.'; 
    struct MyListNode *head = (struct MyListNode*)malloc(sizeof(struct MyListNode)); 
    while(remainder)
    {
        int pre = pop(head, remainder);
        if(pre) 
        {
            for(int i = index; i > pre; i--)
                s[i] = s[i-1];
            index++;
            s[pre] = '(';
            s[index++] = ')';
            break;
        }
        push(head, remainder, index);
        remainder *= 10; 
        s[index++] = remainder/denominator+'0';
        remainder %= denominator;
    }
    s[index] = '\0';
    return s;
}




#if 1//pq
struct PQNode
{
    int value;
    struct PQNode* left;
    struct PQNode* right;
    int leftCount;
    int rightCount;
};
typedef struct PriorityQueue
{
    struct PQNode* headNode;
    int count;
    int head;
    short sign;
}PriorityQueue;
int PQNodeSize=sizeof(struct PQNode);
int PQSize=sizeof(struct PriorityQueue);
short comparePQNode(struct PQNode* pqn1,struct PQNode* pqn2,short sign)
{
    short returnV=0;
    if(pqn1->value>pqn2->value)
        returnV=1;
    if(sign==0)
        returnV=1-returnV;
    return returnV;
}
void swapValue(struct PQNode* pqn1,struct PQNode* pqn2)
{
    int temp=pqn1->value;
    pqn1->value=pqn2->value;
    pqn2->value=temp;
}
void pushDown(struct PQNode* cur,struct PQNode* insert,short sign)
{
    if(comparePQNode(insert,cur,sign))
    {
        int temp=cur->value;
        cur->value=insert->value;
        insert->value=temp;
    }
    if(cur->left==NULL)
    {
        cur->leftCount++;
        cur->left=insert;
    }
    else if(cur->right==NULL)
    {
        cur->rightCount++;
        cur->right=insert;
    }
    else if(cur->leftCount>cur->rightCount)
    {
        cur->rightCount++;
        pushDown(cur->right,insert,sign);
    }
    else
    {
        cur->leftCount++;
        pushDown(cur->left,insert,sign);
    }
}
void push(struct PriorityQueue* pq,int value)
{
    struct PQNode* pqn=(struct PQNode*)malloc(PQNodeSize);
    pqn->value=value;
    pqn->left=NULL;
    pqn->right=NULL;
    pqn->leftCount=0;
    pqn->rightCount=0;
    if(pq->headNode==NULL)
        pq->headNode=pqn;
    else
        pushDown(pq->headNode,pqn,pq->sign);
    pq->head=pq->headNode->value;
    pq->count++;
}
void swapDown(struct PQNode* pqn,short sign)
{
    if(pqn->left==NULL&&pqn->right==NULL)
        return;
    if(pqn->right!=NULL)
    {
        struct PQNode* bigTemp;
        if(comparePQNode(pqn->left,pqn->right,sign))
            bigTemp=pqn->left;
        else
            bigTemp=pqn->right;
        if(comparePQNode(pqn,bigTemp,sign))
            return;
        if(comparePQNode(pqn->left,pqn->right,sign))
        {
            swapValue(pqn,pqn->left);
            swapDown(pqn->left,sign);
        }
        else
        {
            swapValue(pqn,pqn->right);
            swapDown(pqn->right,sign);
        }
    }
    else
    {
        if(comparePQNode(pqn,pqn->left,sign))
            return;
        swapValue(pqn,pqn->left);
        swapDown(pqn->left,sign);
    }
}
void PopDown(struct PQNode* pq,short sign)
{
    if(pq->rightCount>0)
        if(comparePQNode(pq->left,pq->right,sign))
            pq->value=pq->left->value;
        else
            pq->value=pq->right->value;
    else
        pq->value=pq->left->value;
    if(pq->rightCount==1&&pq->leftCount==1)
    {
        if(comparePQNode(pq->left,pq->right,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->left,sign);
        }
        free(pq->right);
        pq->right=NULL;
        pq->rightCount--;
        
    }
    else if(pq->leftCount==1)
    {
        free(pq->left);
        pq->left=NULL;
        pq->leftCount--;
    }
    else if(pq->leftCount>pq->rightCount)
    {
        if(comparePQNode(pq->right,pq->left,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->right,sign);
        }
        pq->leftCount--;
        PopDown(pq->left,sign);
    }
    else
    {
        if(comparePQNode(pq->left,pq->right,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->left,sign);
        }
        pq->rightCount--;
        PopDown(pq->right,sign);
    }
}
void pop(struct PriorityQueue* pq)
{
    if(pq->count==0)
        return;
    pq->count--;
    if(pq->count==0)
    {
        free(pq->headNode);
        pq->headNode=NULL;
        pq->head=-1;
        return;
    }
    struct PQNode* p=pq->headNode;
    PopDown(p,pq->sign);
    pq->head=pq->headNode->value;
}
int top(struct PriorityQueue* pq)
{
    return pq->head;
}
int size(struct PriorityQueue* pq)
{
    return pq->count;
}
int empty(struct PriorityQueue* pq)
{
    return pq->count == 0;
}
struct PriorityQueue* newPriorityQueue(short sign)
{   
    struct PQNode* h=NULL;
    struct PriorityQueue* pq=(struct PriorityQueue*)malloc(PQSize);
    pq->headNode=h;
    pq->count=0;
    pq->head=-1;
    pq->sign=sign;
    return pq;
}
#endif

int connectSticks(int*sticks, int sticksSz){
    PriorityQueue*pq = newPriorityQueue(0);
    for(int z=0;z<sticksSz;z++){int v = sticks[z];
        push(pq, v);
    }
    int ans = 0;
    while(size(pq) > 1){
        int x = top(pq); pop(pq);
        int y = top(pq); pop(pq);
        ans += x + y;
        push(pq, x+y);
    }
    return ans;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#if 1 //pq
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
struct PriorityQueue* newPriorityQueue()
{   
    short sign=1;
    struct PQNode* h=NULL;
    struct PriorityQueue* pq=(struct PriorityQueue*)malloc(PQSize);
    pq->headNode=h;
    pq->count=0;
    pq->head=-1;
    pq->sign=sign;
    return pq;
}
#endif

typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}


int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int evSz = 2*n;
    pair ev[evSz]; memset(ev, 0, sizeof(ev));
    for(int i = 0; i < n; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        ev[2*i  ] = newPair(a  ,  1);
        ev[2*i+1] = newPair(a+b, -1);
    }
    qsort(ev, evSz, sizeof(pair), cmpP);
    PriorityQueue*q = newPriorityQueue();
    int walks = 0;
    for(int z=0; z<evSz; z++){ pair e = ev[z];
        if(e.second < 0)
            push(q, -e.first-m);
        else{
            while(!empty(q) && -top(q) < e.first)
                pop(q);
            if(!empty(q))
                pop(q), ++walks;
        }
    }
    printf("%d\n", walks);
    return 0;
}



















































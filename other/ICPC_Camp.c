#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

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
    short sign=0;//rev
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
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
//////////////////////////////
enum{MAXN = 200005};

int n, p, q, s;
int a[MAXN],
    b[MAXN];

bool trial(int D){
    vecp ev = newVecP();
    for(int i=0; i<p; i++){
        int st, ed;
        st = fmax(0, a[i] - D);
        ed = fmin(s - a[i], a[i] + D);
        if(st <= ed)
           pbp(ev, newpair(st, ed));
    }
    qsort(ev.ptr, ev.sz, sizeof(pair), cmpP);
    int p = 0;
    PriorityQueue*pq = newPriorityQueue();//rev
    int mtch=0;
    for(int i=0; i<q; i++){
        while(p < ev.sz && ev.ptr[p].first <= b[i]){
            push(pq, ev.ptr[p].second);
            p++;
        }
        while(size(pq) && top(pq) < b[i])
            pop(pq);
        if(size(pq)){
            mtch++;
            pop(pq);
        }
    }
    return mtch >= n;
}
int main(){
    scanf("%d %d %d %d", &n, &p, &q, &s);
    for(int i=0; i<p; i++)
        scanf("%d", &a[i]);
    for(int i=0; i<q; i++)
        scanf("%d", &b[i]);
    qsort(a, p, sizeof(int), cmp);
    qsort(b, q, sizeof(int), cmp);
    int s = 0,
        e =(int)1e9;
    if(!trial(e)){
        puts("-1");
        return 0;
    }
    while(s != e){
        int m = (s+e)/2;
        if(trial(m))
            e = m;
        else
            s = m + 1;
    }
    printf("%d\n", s);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>


#define MAX_CHILDREN_POWER    5
#define MAX_CHILDREN_NUMBER  64
typedef struct NumberTrieNodeS{
    bool   bEndPoint;
    int    numberCount;
    struct NumberTrieNodeS*next[MAX_CHILDREN_NUMBER];
}NumberTrieNode;
NumberTrieNode*newNumberTrieNode()
{
    NumberTrieNode*rez=malloc(sizeof(NumberTrieNode));
    rez->bEndPoint   = false;
    rez->numberCount = 0;
    memset(rez->next, 0, sizeof(rez->next));
    return rez;
}
NumberTrieNode*m_objNumberTrieRoot;
typedef struct RandomizedSet RandomizedSet;
RandomizedSet*ptr;

bool insert(NumberTrieNode * pstCurrent, int iValue)
{
    if (pstCurrent == NULL)
        return false;
    if (iValue == 0)
    {
        if (pstCurrent -> bEndPoint)
            return false;
        pstCurrent->bEndPoint = true;
        pstCurrent->numberCount ++;
        return true;
    }
    int iNextIndex = (int)((unsigned)(iValue) & (MAX_CHILDREN_NUMBER - 1));
    int iNextValue = (int)((unsigned)(iValue) >> MAX_CHILDREN_POWER);
    if (pstCurrent->next[iNextIndex] == NULL)
        pstCurrent->next[iNextIndex] = newNumberTrieNode();
    bool bResult = insert(pstCurrent->next[iNextIndex], iNextValue);
    if (bResult)
        pstCurrent->numberCount++;
    return bResult;
}
bool removeEl(NumberTrieNode * pstCurrent, int iValue)
{
    if (pstCurrent == NULL)
        return false;
    if (iValue == 0)
    {
        if (!pstCurrent -> bEndPoint)
            return false;
        pstCurrent -> bEndPoint = false;
        pstCurrent -> numberCount --;
        return true;
    }
    int iNextIndex = (int)((unsigned)(iValue) & (MAX_CHILDREN_NUMBER - 1));
    int iNextValue = (int)((unsigned)(iValue) >> MAX_CHILDREN_POWER);
    bool bResult = removeEl(pstCurrent -> next[iNextIndex], iNextValue);
    if (bResult)
        pstCurrent -> numberCount --;
    return bResult;
}
void errexit(int a){
    printf("err %d\n",a);
    exit(a);
}
int getRandom(NumberTrieNode * pstCurrent)
{
    if (pstCurrent == NULL)
        errexit(5);
    if (pstCurrent -> numberCount <= 0)
        errexit(6);
    int iChooseIndex = 0 - 1;
    int iChooseRound = rand() % pstCurrent -> numberCount;
    for (int iIndex = 0, iChooseRange = 0; iIndex < MAX_CHILDREN_NUMBER; iIndex ++)
    {
        if (pstCurrent -> next[iIndex] == NULL)
            continue;
        if (iChooseRound < iChooseRange + pstCurrent -> next[iIndex] -> numberCount)
        {
            iChooseIndex = iIndex;
            break;
        }
        iChooseRange += pstCurrent -> next[iIndex] -> numberCount;
    }
    if (iChooseIndex < 0)
    {
        if (pstCurrent -> bEndPoint)
            return 0;
        errexit(7);
    }
    return (getRandom(pstCurrent -> next[iChooseIndex]) << MAX_CHILDREN_POWER) | iChooseIndex;
}

RandomizedSet*randomizedSetCreate(){
    m_objNumberTrieRoot=newNumberTrieNode();
    srand(time(NULL));
    return ptr;
}
bool randomizedSetInsert(RandomizedSet* obj, int val) {
    return insert(m_objNumberTrieRoot, val);
}
bool randomizedSetRemove(RandomizedSet* obj, int val) {
    return removeEl(m_objNumberTrieRoot, val);
}
int  randomizedSetGetRandom(RandomizedSet* obj){
    return getRandom(m_objNumberTrieRoot);
}

void randomizedSetFree(RandomizedSet* obj){
    m_objNumberTrieRoot=NULL;
}


#define DEBUG_ON 0


#if DEBUG_ON
int main(){
  RandomizedSet*rs = randomizedSetCreate();
  randomizedSetInsert   (rs,1);
  randomizedSetRemove   (rs,2);
  randomizedSetInsert   (rs,2);
  randomizedSetGetRandom(rs);
  randomizedSetRemove   (rs,1);
  randomizedSetInsert   (rs,2);
int rv=
  randomizedSetGetRandom(rs);  printf("%d\n",rv);
  randomizedSetFree     (rs);
}
#endif
























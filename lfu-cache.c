#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node {
    int key; 
    int val; 
    int fre; 
    int timeStamp; 
}Node;
typedef struct {
    int a;
} LFUCache;
LFUCache*ptr;

Node*pq[4096];
int nodeIndex;
int mp[4096]; 
int Cap; 
int ts; 

Node*newNode(){
    Node*rez=malloc(sizeof(Node));
    pq[nodeIndex++]=rez;
    rez->key=-1;
    rez->val=-1;
    rez->timeStamp=-1;
    rez->fre=0;
    return rez;
}
Node*newNodeMake(int k, int v, int ts){
    Node*rez=malloc(sizeof(Node));
//    pq[nodeIndex++]=rez;
    rez->key=k;
    rez->val=v;
    rez->timeStamp=ts;
    rez->fre=1;
    return rez;
}

void sink(int index);
void swim(int index);
void myswap(int id1, int id2);

//public
LFUCache* lFUCacheCreate(int capacity){
    nodeIndex=0;
    memset(pq,0,sizeof(pq));
    memset(mp,0,sizeof(mp));
    Cap = capacity;
    Node*dummy = newNode();
    ts = 0;
    return ptr;
}
int lFUCacheGet(LFUCache* obj, int key){
    if(mp[key]==0) return -1;
    int index = mp[key];
    Node*cur=pq[index];
    int val = cur->val;
    cur->fre++;
    cur->timeStamp= ++ts;
    sink(index);
    return val;
}
void lFUCachePut(LFUCache* obj, int key, int value){
    if(Cap <= 0) return;
    if(mp[key]!=0) {
        int index = mp[key];
        Node*cur=pq[index];
        cur->val = value;
        lFUCacheGet(ptr, key);
    }
    else {
        if(nodeIndex - 1 == Cap) {
            int oldKey = pq[1]->key;
            mp[oldKey]=0;
            Node* newnode = newNodeMake(key, value, ++ts);
            pq[1] = newnode;
            mp[key] = 1;
            sink(1);
        }
        else {
            Node* newnode = newNodeMake(key, value, ++ts);
            pq[nodeIndex++]=(newnode);
            mp[key] = nodeIndex - 1;
            swim(nodeIndex - 1);
        }
    }
}
void lFUCacheFree(LFUCache* obj) {
    
}
//private
void sink(int index) {
    int left = 2 * index, right = 2 * index + 1, target = index;
    if(left < nodeIndex && pq[left]->fre <= pq[target]->fre) 
           target = left;
        if(right < nodeIndex) { 
            if(pq[right]->fre < pq[target]->fre || (pq[right]->fre == pq[target]->fre && pq[right]->timeStamp < pq[target]->timeStamp)) 
                 target = right;
    }
    if(target != index) {
        myswap(target, index);
            sink(target);
    }
}
void swim(int index) {
    int par = index / 2;
    while(par > 0 && pq[par]->fre > pq[index]->fre) {
        myswap(par, index);
        index = par;
        par /= 2;
    }
}
void swap(Node**nums, int i, int j) {
   Node*t  = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void myswap(int id1, int id2) {
    swap(pq, id1, id2);
    mp[pq[id1]->key] = id1;
    mp[pq[id2]->key] = id2;
}
#if 0
int main(){
  LFUCache*cache = lFUCacheCreate( 2 );
  lFUCachePut(cache,1, 1);
  lFUCachePut(cache,2, 2);
  printf("%d\n",
  lFUCacheGet(cache,1)  );     // returns 1
  lFUCachePut(cache,3, 3);    // evicts key 2
  printf("%d\n",
  lFUCacheGet(cache,2) );     // returns -1 (not found)
  printf("%d\n",
  lFUCacheGet(cache,3) );     // returns 3.
  lFUCachePut(cache,4, 4);    // evicts key 1.
  printf("%d\n",
  lFUCacheGet(cache,1) );     // returns -1 (not found)
  printf("%d\n",
  lFUCacheGet(cache,3) );     // returns 3
  printf("%d\n",
  lFUCacheGet(cache,4));       // returns 4
}
#endif





















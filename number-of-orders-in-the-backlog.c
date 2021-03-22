#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)
typedef long long ll;
enum{MOD =(int)1e9+7};
typedef struct Node{
    ll price;
    ll amount;
    struct Node*left;
    struct Node*right;
}Node;

Node*newNode(ll p, ll a){
    Node*n=calloc(1, sizeof(Node));
    n->price =p;
    n->amount=a;
    return n;
}

Node*meld(Node*a, Node*b, bool maxheap){
    if(!a)
        return b;
    if(!b)
        return a;
    bool cmp = maxheap ? a->price < b->price : a->price > b->price;
    if(cmp)
        swap(a, b);
    a->right = meld(a->right, b, maxheap);
    swap(a->left, a->right);
    return a;
}
int getNumberOfBacklogOrders(int**orders, int ordersSz, int*orders0sz){
    Node*buyBacklog  = NULL;
    Node*sellBacklog = NULL;
    for(int z=0;z<ordersSz;z++){int*oo=orders[z];
        ll price     = oo[0];
        ll amount    = oo[1];
        ll orderType = oo[2];
        if(orderType == 0){
            while(amount > 0){
                if(!sellBacklog || sellBacklog->price > price){
                    buyBacklog = meld(buyBacklog, newNode(price, amount), true);
                    break;
                }
                else{
                    ll am = fminl(amount, sellBacklog->amount);
                    amount -= am;
                    Node*cur = newNode(sellBacklog->price, sellBacklog->amount - am);
                    sellBacklog = meld(sellBacklog->left,  sellBacklog->right, false);
                    if(cur->amount > 0){
                        sellBacklog = meld(sellBacklog, cur, false);
                    }
                }
            }
        }
        else if(orderType == 1){
            while(amount > 0){
                if(!buyBacklog || buyBacklog->price < price){
                    sellBacklog = meld(sellBacklog, newNode(price, amount), false);
                    break;
                }
                else{
                    ll am = fminl(amount, buyBacklog->amount);
                    amount -= am;
                    Node*cur = newNode(buyBacklog->price, buyBacklog->amount - am);
                    buyBacklog = meld(buyBacklog->left, buyBacklog->right, true);
                    if(cur->amount > 0){
                        buyBacklog = meld(buyBacklog, cur, true);
                    }
                }
            }
        }
    }
    ll countHeap(Node*n){
        if(!n)
            return 0;
        ll amount = n->amount;
        amount += countHeap(n->left) + countHeap(n->right);
        amount %= MOD;
        return amount;
    }
    return(countHeap(buyBacklog) + countHeap(sellBacklog)) % MOD;
}

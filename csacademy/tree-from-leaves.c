#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>





int total;
int cur;

typedef struct NodeS
{
    int num;
    int dist;
    int to;
    struct NodeS* next;
    struct NodeS* child;
    int  childSz;
}Node;
Node nodes[12345];
Node* root;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Node*pushback(Node*array, int *size, Node value){
    Node*output = resizeArray(array, Node, *size + 1);
    output[(*size)++] = value;
    return output;
}


int ask(int a, int b)
{
    printf("Q %d %d\n", a, b);fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}
Node* build(int now, int to, int dist)
{
    Node* ret  = nodes + cur++;
    Node* node = ret;
    node->to   = to;
    node->num  = now;
    node->dist = dist;
    for(int i = 0; i < dist; i++)
    {
        node->next = nodes + cur++;
        node->next->dist = dist - 1 - i;
        if(i < dist - 1)
            node->next->num = ++total;
        else
            node->next->num = to;
        node->next->to = to;
        node = node->next;
    }
    return ret;
}
void go(Node* node, int num, int dist)
{
    int dist2 = ask(num, node->to);
    int extra = (dist + dist2 - node->dist) / 2;
    for(int i = 0; i < dist - extra; i++)
        node = node->next;
    bool ok = false;
    for(int i=0;i<node->childSz;i++){ Node*c = &node->child[i];
        if(ask(num, c->to) < c->dist + extra)
        {
            go(c, num, extra);
            ok = true;
            break;
        }
    }
    if(!ok){
        Node*nn=build(node->num, num, extra);
        node->child=pushback(node->child, &node->childSz, *nn);
    }
}
void pp(Node* node)
{
    while(node)
    {
        if(node->next){
            printf("%d %d\n", node->num, node->next->num);fflush(stdout);
        }
        for(int i=0;i<node->childSz;i++){ Node*c = &node->child[i];
            pp(c);
        }
        node = node->next;
    }
}
int main()
{
    int K;
    scanf("%d", &K);
    total = K;
    root = build(1, 2, ask(1, 2));
    for(int i = 3; i <= K; i++)
        go(root, i, ask(1, i));
    printf("A\n%d\n",total); fflush(stdout);
    pp(root);
    return 0;
}





























































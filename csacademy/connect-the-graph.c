#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair *pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
  

enum{ kMaxN =(int) 1e5+1};
int* vertex [kMaxN];
int  sizes  [kMaxN];
bool visited[kMaxN];
int  parent [kMaxN];
pair*free_edges=NULL;int free_edgesSz=0;

void Df(int node) {
    visited[node] = true;
    for(int i=0;i<sizes[node];i++){
        int itr = vertex[node][i];
        if (itr == parent[node]) {
            continue;
        }
        if (!visited[itr]) {
            parent[itr] = node;
            Df(itr);
        } 
        else {
            if (itr < node) {
                free_edges=pushbackP(free_edges,&free_edgesSz,newPair(node, itr));
            }
        }
    }
    return;
}
int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i += 1) {
        int a, b; 
        scanf("%d %d", &a, &b);
        vertex[a]=pushback(vertex[a], sizes+a, b);
        vertex[b]=pushback(vertex[b], sizes+b, a);
    }
    int*root_nodes=NULL;int root_nodesSz=0;
    for (int i = 1; i <= n; i += 1) {
        if (!visited[i]) {
            root_nodes=pushback(root_nodes,&root_nodesSz,i);
            Df(i);
        }       
    }
    if (root_nodesSz - 1 > free_edgesSz) {
        puts("-1");
        return 0;
    }
    else {
        printf("%d\n", root_nodesSz - 1);
        while ( root_nodesSz > 1) {
            int a = root_nodes[0];
            int b = root_nodes[root_nodesSz-1];
            root_nodesSz--;
            pair deleted_edge = free_edges[free_edgesSz-1];
            free_edgesSz--;
            printf("%d %d %d %d\n", deleted_edge.first, deleted_edge.second, a, b);
        }
    }
    return 0;
}


















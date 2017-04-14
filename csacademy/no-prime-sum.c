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
 

typedef long long int64;
enum{ kMaxN   =(int) 1e4  }; 
enum{ kMaxVal =(int) 2e5+5};
int*left_nodes =NULL;int left_nodesSz =0;
int*right_nodes=NULL;int right_nodesSz=0;
int*vertex[kMaxN];
int sizes [kMaxN];
bool is_prime[kMaxVal];
bool visited[kMaxN], matched[kMaxN];
int match_pair[kMaxN];

void Init() {
    for (int i = 2; i < kMaxVal; i += 1) {
        is_prime[i] = true;
    }
    for (int i = 2; i < kMaxVal; i += 1) {
        if (! is_prime[i]) {
            continue;
        }
        for (int64 j = 1LL * i * i; j < kMaxVal; j += i) {
            is_prime[j] = false;
        }
    }
}
bool Match(int node) {
    visited[node] = true;
    for(int i=0;i<sizes[node];i++){ int itr = vertex[node][i];
        if (! matched[itr]) {
            matched[node] = true;
            matched[itr] = true;
            match_pair[node] = itr;
            match_pair[itr] = node;
            return true;
        }
    }
    for(int i=0;i<sizes[node];i++){ int itr = vertex[node][i];
        if (! visited[match_pair[itr]] && Match(match_pair[itr])) {
            matched[node] = true;
            match_pair[node] = itr;
            match_pair[itr] = node;
            return true;
        }
    }
    return false;
}
int main() {
    Init();
    int n;
    scanf("%d", &n);
    int elements[n];
    for(int i=0;i<n;i++){
        int itr;
        scanf("%d", &itr);
        elements[i]=itr;
        if (itr & 1){
            left_nodes=pushback(left_nodes, &left_nodesSz, itr);
        } 
        else {
            right_nodes=pushback(right_nodes, &right_nodesSz, itr);
        }
    }
    for (int i = 0; i < left_nodesSz; i += 1) {
        for (int j = 0; j < right_nodesSz; j += 1) {
            if (! is_prime[left_nodes[i] + right_nodes[j]]) {
                continue;
            }
            int a = i;
            int b = j + left_nodesSz;
            vertex[a]=pushback(vertex[a], sizes+a, b);
        }
    }
    bool ok = true;
    while (ok) {
        ok = false;
        for (int i = 0; i < left_nodesSz; i += 1) {
            visited[i] = false;
        }
        for (int i = 0; i < left_nodesSz; i += 1) {
            if (visited[i] || matched[i]) {
                continue;
            }
            if (Match(i)) {
                ok = true;
            }
        }
    }
    int*unselected_q=NULL;int unselected_qSz=0;
    int selected[n];
    memset(selected,0,sizeof(selected));
    for(int i = 0; i < left_nodesSz; i++){
        if (matched[i]){
            selected[i] = true;
        } 
        else{
            unselected_q=pushback(unselected_q, &unselected_qSz, i);
        }
    }
    while(unselected_qSz){
        int node = unselected_q[unselected_qSz-1];
        unselected_qSz--;
        for(int i=0;i<sizes[node];i++){
            int itr = vertex[node][i];
            if (!selected[itr]){
                int oth = match_pair[itr];
                if (selected[oth]) {
                    unselected_q=pushback(unselected_q, &unselected_qSz, oth);
                    selected[oth] = false;
                }
                selected[itr] = true;
            }
        }
    }
    int r = 0;
    for(int i=0;i<n;i++){
        int itr = selected[i];
        r += itr;
    }
    printf("%d\n", r);
    for(int i = 0; i < n; i++){
        if(!selected[i]){
            continue;
        }
        if (i < left_nodesSz){
            printf("%d ", left_nodes[i]);
        } 
        else {
            printf("%d ", right_nodes[i - left_nodesSz]);
        }
    }
    puts("");
    return 0;
}





























































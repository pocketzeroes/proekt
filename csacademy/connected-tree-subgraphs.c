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
enum{ kMaxN=(int)1e5  }; 
enum{ kMod =(int)1e9+7};
int inv_number  [kMaxN+1];
int fact        [kMaxN+1];
int*neighbour   [kMaxN];
int sizes       [kMaxN];
bool visited    [kMaxN];
int subtree_size[kMaxN];
int64 answer = 0;
int n;

int Pow(int a, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (1LL * res * a) % kMod;
        }
        a = (1LL * a * a) % kMod;
        p /= 2;
    }
    return res;
}
void Initialise() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= kMaxN; i += 1) {
        fact[i] = (1LL * i * fact[i - 1]) % kMod;
    }
    int inv_fact = Pow(fact[kMaxN], kMod - 2);
    for (int i = kMaxN; i; i -= 1) {
        inv_number[i] = 1LL * inv_fact * fact[i - 1] % kMod;
        inv_fact = 1LL * inv_fact * (i) % kMod;
    }
    inv_number[0] = 1;
}
void ComputeSubtree(int node) {
    visited[node] = true;
    for(int i=0;i<sizes[node];i++){int itr=neighbour[node][i];
        if (visited[itr]) {
            continue;
        }
        ComputeSubtree(itr);
        subtree_size[node] += subtree_size[itr];
    }    
    subtree_size[node] += 1;
    visited[node] = false;
}
void Solve(int node, int sum) {
    answer += sum;
    visited[node] = true;
    for(int i=0;i<sizes[node];i++){int itr=neighbour[node][i];
        if (visited[itr]) {
            continue;
        }
        Solve(itr, 1LL * sum * subtree_size[itr] % kMod * inv_number[(n - subtree_size[itr])] % kMod);
    }
    visited[node] = false;
}
int main() {
    Initialise();
    scanf("%d", &n);
    for (int i = 1; i < n; i += 1) {
        int a, b; 
        scanf("%d %d", &a, &b);
        a -= 1;
        b -= 1;
        neighbour[a]=pushback(neighbour[a], sizes+a, b);
        neighbour[b]=pushback(neighbour[b], sizes+b, a);
    }
    const int root = 0;
    ComputeSubtree(root);
    int root_answer = fact[n];
    for (int i = 0; i < n; i += 1) {
        root_answer = 1LL * root_answer * inv_number[subtree_size[i]] % kMod;
    }
    Solve(root, root_answer);
    printf("%lld\n", answer % kMod);
    return 0;
}



















































#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef long long int64;
enum{ kMaxN =(int) 1e5 + 1};
int elements[kMaxN];
bool visited[kMaxN];
int64 result[kMaxN];

int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i += 1) {
        int x; 
        scanf("%d", &x);
        elements[i] = x;
    }
    for (int i = 1; i <= n; i += 1) {
        if (visited[i]) {
            continue;
        }
        int*current_permutation=NULL;int current_permutationSz=0;
        int*index              =NULL;int indexSz=0;
        int current = i;
        while(!visited[current]){
            current_permutation=pushback(current_permutation,&current_permutationSz,elements[current]);
            index=pushback(index,&indexSz,current);
            visited[current] = true;
            current = elements[current];
        }
        int64 permutation_sum = 0;
        for(int i=0;i<current_permutationSz;i++){
            int itr=current_permutation[i];
            permutation_sum += itr;
        }
        int offset = m % current_permutationSz;
        int64 base_sum = 1LL * permutation_sum * (int)(m / current_permutationSz);
        int64 current_sum = 0;
        for (int i = 0; i < offset; i += 1) {
            current_sum += current_permutation[i];
        }
        for (int i = 0; i < current_permutationSz; i += 1) {
            result[index[i]] = current_sum + base_sum;
            current_sum -= current_permutation[i];
            current_sum += current_permutation[(i + offset) % current_permutationSz];
        }
    }
    for (int i = 1; i <= n; i += 1){
      printf("%lld ", result[i]);
    }
    printf("\n");
    return 0;
}



























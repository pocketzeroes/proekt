#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

enum{ kMaxN   = 13        }; 
enum{ inf     = 0x3f3f3f3f}; 
enum{ kMaxVal = 10000     };

int main() {
    int n;
    scanf("%d", &n);
    assert(n <= kMaxN);
    int sz=1 << n;
    int config_cost[n][sz];
    for( int i=0;i<n;i++)
        for( int j=0;j<sz;j++)
            config_cost[i][j]=inf;
    int cost       [n][n ];
    memset(cost,0,sizeof(cost));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            scanf("%d", &cost[i][j]);
            assert(0 <= cost[i][j]);
            assert(cost[i][j] <= kMaxVal);
        }
    }
    for (int i = 0; i < n; i += 1) 
        config_cost[i][1 << i] = 0;
    for (int config = 0; config < (1 << n); config += 1) {
        int*current_elements=NULL;int current_elementsSz=0;
        for (int el = 0; el < n; el += 1) 
            if (config & (1 << el)) 
                current_elements=pushback(current_elements,&current_elementsSz,el);
        for (int current_elements_config = 1; current_elements_config < (1 << current_elementsSz); current_elements_config += 1) {
            int child_config = 0;
            for (int i = 0; i < current_elementsSz; i += 1) 
                if ((1 << i) & current_elements_config) 
                    child_config |= (1 << current_elements[i]);
            for(int z=0;z<current_elementsSz;z++){ 
                int father=current_elements[z];
                if ((1 << father) & child_config) 
                    continue;
                for(int q=0;q<current_elementsSz;q++){ 
                    int child=current_elements[q];
                    if (((1 << child) & child_config) == 0) 
                        continue;
                    config_cost[father][config] = min(config_cost[father][config],
                            max(config_cost[father][config ^ child_config],
                                config_cost[child][child_config]) + cost[father][child]);
                }
            }
        }
        free(current_elements);
    }
    printf("%d\n", config_cost[0][(1 << n) - 1] );
    return 0;
}





























































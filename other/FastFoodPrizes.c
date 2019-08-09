#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ max_stickers = 100};

int main(){
    int tn;
    for(scanf("%d", &tn); tn--;){
        int n, m;
        scanf("%d %d", &n, &m);
        int*stickers[n];
        int sizes   [n];
        int value   [n];
        for(int i=0; i<n; i++){
            int k;
            scanf("%d", &k);
            stickers[i] = calloc(k, sizeof(int)); 
            sizes[i] = k;
            for(int j = 0; j < k; j++)
                scanf("%d", &stickers[i][j]);
            scanf("%d", &value[i]);
        }
        int stickersNum[m];
        for(int i=0; i<m; i++)
            scanf("%d", &stickersNum[i]);
        int total = 0;
        for(int i = 0; i < n; i++){
            int minnum = max_stickers;
            for(size_t j=0; j < sizes[i]; j++)
                if(minnum > stickersNum[stickers[i][j] - 1])
                   minnum = stickersNum[stickers[i][j] - 1];
            total += minnum * value[i];
        }
        printf("%d\n", total);
    }
    return 0;
}

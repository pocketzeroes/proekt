#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

int main(){
    int v[31][31]; dfill(v, 31, 31, 1);
    for(int i = 2; i <= 30; i++)
        for(int j = 2; j <= i; j++)
            v[i][j] = v[i-1][j] + v[i-1][j-1];
    int cases;
    scanf("%d", &cases);
    for(int i=0; i<cases; i++){
        int pirates, groups;
        scanf("%d %d", &pirates, &groups);
        printf("%d\n", v[pirates][groups]);
    }
    return 0;
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

enum{ MAX_ROUNDS = 10};
enum{ MAX_N = 1200   };

int main(){
    int numCases = in_nextInt();
    int prev[MAX_N+1]; clr(prev);
    int curr[MAX_N+1]; clr(curr);
    for(int c=0; c<numCases; c++){
        int n = in_nextInt();
        for(int i=1; i<=n; i++)
            prev[i] = in_nextInt();
        for(int round=1; round<=MAX_ROUNDS; round++){
            for(int i=1; i<=n; i++)
                curr[i] = prev[prev[i]];
            int temp[MAX_N+1];
            memcpy(temp, prev, sizeof(prev));
            memcpy(prev, curr, sizeof(prev));
            memcpy(curr, temp, sizeof(prev));
        }
        bool isIdentity = true;
        for(int i=1; i<=n; i++){
            if(prev[i]!=i){
                isIdentity=false;
                break;
            }
        }
        if(isIdentity)
            puts("All can eat.");
        else
            puts("Some starve.");
    }
    return 0;
}

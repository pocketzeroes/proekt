#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    int sweep[101005] = {0};
    for(int i=0; i<N; ++i){
        int cur;
        scanf("%d", &cur);
        sweep[cur]++;
        sweep[cur+1000]--;
    }
    int top    = 0;
    int active = 0;
    for(int i=0; i<101005; ++i){
        active += sweep[i];
        top = max(top, active);
    }
    printf("%d\n", ((top + K - 1) / K) );
    return 0;
}

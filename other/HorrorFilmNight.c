#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int main(){
    int state[1000010]; fill(state, 1000010, 3);
    for(int i = 0; i < 2; ++i){
        int k;
        scanf("%d", &k);
        while(k--){
            int v;
            scanf("%d", &v);
            state[v] &= ~(1<<i);
        }
    }
    int answer = 0, disl = 0;
    for(int i=0;i<1000010;i++){int s = state[i];
        if(s < 3 && !(s&disl))
            ++answer, disl = s;
    }
    printf("%d\n", answer);
    return 0;
}

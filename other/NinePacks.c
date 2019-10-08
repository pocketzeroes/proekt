#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{GSZ=100002};

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
    int inf = 1<<29;
    int size;
    int*h=calloc(GSZ, sizeof(int)); fill(h, GSZ, inf);
    int*b=calloc(GSZ, sizeof(int)); fill(b, GSZ, inf);
    h[0] = 0;
    b[0] = 0;
    scanf("%d", &size);
    for(int i=0; i<size; i++){
        int num;
        scanf("%d", &num);
        for(int j = GSZ-num-1; j >= 0; j--)
            if(h[j] < h[j+num])
                h[j+num] = h[j]+1;
    }
    scanf("%d", &size);
    for(int i = 0; i < size; i++){
        int num;
        scanf("%d", &num);
        for(int j = GSZ-num-1; j >= 0; j--)
            if(b[j] < b[j+num])
                b[j+num] = b[j]+1;
    }
    int best = inf;
    for(int i = 1; i < GSZ; i++)
        if(h[i] + b[i] < best)
            best = h[i] + b[i];
    if(best >= inf/2) {
        puts("impossible");
        return 0;
    }
    printf("%d\n", best);
    return 0;
}

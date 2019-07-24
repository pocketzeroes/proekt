#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
    int t = in_nextInt();
    for(int i = 0; i < t; i++) {
        int n        = in_nextInt();
        int total    = 0;
        int max      = 0;
        int maxCount = 0;
        int maxIdx   = -1;
        for(int j = 1; j <= n; j++) {
            int x = in_nextInt();
            total += x;
            if (x > max){
                max = x;
                maxIdx = j;
                maxCount = 1;
            }
            else if (x == max)
                maxCount++;
        }
        if(maxCount > 1)
            puts("no winner");
        else if(max > total / 2)
            printf("majority winner %d\n", maxIdx);
        else
            printf("minority winner %d\n", maxIdx);
    }
    return 0;
}

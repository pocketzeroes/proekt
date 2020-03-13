#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

int main(){
    int t = in_nextInt();
    for(int i=0; i<t; i++){
        int cals = in_nextInt();
        double num = (cals * 1.0) / 400;
        int out = (int)num;
        if(num > out)
            out++;
        printf("%d\n", out);
    }
    return 0;
}

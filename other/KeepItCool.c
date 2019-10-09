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
///////////////////////////

int main(){
    int n = in_nextInt();
    int m = in_nextInt();
    int s = in_nextInt();
    int d = in_nextInt();
    int c[s];
    for(int i=0; i<s; i++)
        c[i] = in_nextInt();
    int r[s]; clr(r);
    while(n > 0){
        int ui = -1, 
            uc = d;
        for(int i = 0; i < s; i++){
            if(c[i] < uc){
                ui = i;
                uc = c[i];
            }
        }
        int z = fmin(d-c[ui], n);
        c[ui] += z;
        r[ui] = z;
        n -= z;
    }
    int t = 0;
    for(int i=0; i<s; i++)
        if(r[i] == 0)
            t += c[i];
    if(t >= m){
        for(int i=0; i<s; i++)
            printf("%d ", r[i]);
        puts("");
    }
    else
        puts("impossible");
    return 0;
}

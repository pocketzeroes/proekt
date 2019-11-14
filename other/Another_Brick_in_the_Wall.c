#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int h, w, n;
    scanf("%d %d %d", &h, &w, &n);
    bool good = true;
    int heightCount = 0;
    int wCount = 0;
    while(n--){
        int brick;
        scanf("%d", &brick);
        wCount += brick;
        if(wCount == w){
            heightCount++;
            wCount = 0;
            if(heightCount == h)
                goto end;
        }
        else if(wCount > w){
            good = false;
            goto end;
        }
    }
  end:
    if(good && heightCount == h)
        puts("YES");
    else
        puts("NO");
    return 0;   
}

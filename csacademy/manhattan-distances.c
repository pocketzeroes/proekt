#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

int main(){
    int test;
    int a, b, c;
    scanf("%d", &test);
    for(int i=0;i<test;i++){
        scanf("%d %d %d", &a, &b, &c);
        if (a < b) swap(a, b);
        if (a < c) swap(a, c);
        if (a > b + c || (b + c - a) % 2)
            puts("-1");
        else{
            int y = (b + c - a) / 2;
            printf("0 0 %d 0 %d %d\n", a, b - y, y);
        }
    }
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
int main(){
    while(scanf("%d", &n)==1 && n!=0){
        n-=3;
        if (n==0)
            puts("4");
        else if (n<4)
            puts("No such base");
        else{
            bool f=false;
            for (int i=4; i<=sqrt(n)+1; i++)
                if (n%i==0){
                    printf("%d\n", i);
                    f=true;
                    break;
                }
            if (f)
                continue;
            if (n%3==0 && n/3>=4)
                printf("%d\n", n/3);
            else
            if (n%2==0 && n/2>=4)
                printf("%d\n", n/2);
            else
                printf("%d\n", n);
        }
    }
    return 0;
}

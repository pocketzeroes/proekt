#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int pr[] = {2, 3, 5, 7};
    int ans = 1;
    for(int i = 0; i < 4; i++){
        printf("Q %d\n", pr[i]); fflush(stdout);
        int a;
        scanf("%d", &a);
        while(a--)
            ans *= pr[i];
    }
    printf("A %d\n", ans); fflush(stdout);
}

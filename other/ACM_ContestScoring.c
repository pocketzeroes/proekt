#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    int attempts[256]; clr(attempts);
    int correct=0;
    int score  =0;
    int submit;
    while(scanf("%d", &submit)==1 && submit != -1){
        getchar();
        char p     =getchar();
        char*result=getstr ();
        attempts[p]++;
        if(strcmp(result, "right")==0){
            correct++;
            score += submit + 20 * (attempts[p] - 1);
        }
    }
    printf("%d %d\n", correct, score);
    return 0;
}

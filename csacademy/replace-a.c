#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define MAX_STRING 200
char str[MAX_STRING];

int main(){
    scanf("%s", &str);
    int len = strlen(str);
    int Aflag = 0;
    for (int i = 0; i < len; i++){
        if (str[i] == 'B'){
            printf("B");
            Aflag = 0;
        }
        else{
            if(!Aflag)
                printf("A");
            Aflag = 1;
        }
    }
}

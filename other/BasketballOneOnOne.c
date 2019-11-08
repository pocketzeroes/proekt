#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    char*input = getstr();
    int  input_len = strlen(input);
    int a = 0;
    int b = 0;
    bool isDeuce = false;
    for(int i=0; i<input_len; i+=2){
        if(input[i] == 'A')
            a += input[i + 1] - '0';
        else
            b += input[i + 1] - '0';
        if(a == 10 && b == 10)
            isDeuce = true;
        if(isDeuce){
            if(a >= b + 2)
                puts("A");
            else if(b >= a + 2)
                puts("B");
        }
        else{
            if(a >= 11)
                puts("A");
            else if(b >= 11)
                puts("B");
        }
    }
    return 0;
}

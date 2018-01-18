#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

char buff_s[100000];
char buff_p[100000];
int main() {
    scanf("%s %s", &buff_s, &buff_p);
    for(int i=0;buff_s[i];i++){char c = buff_s[i];
        putchar(buff_p[c-'a']);
    }
    puts("");
}

#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char line[100000];
char*getln(){
  gets(line);
  return strdup(line);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for(int i=0; i<n; ++i){
        char*s = getln();
        int mask = 0;
        for(int z=0;s[z];z++){char c = s[z];
            if(c >= 'A' && c <= 'Z')
                mask |= 1 << (c - 'A');
            else if(c >= 'a' && c <= 'z')
                mask |= 1 << (c - 'a');
        }
        if(mask == (1 << 26) - 1)
            puts("pangram");
        else{
            printf("missing ");
            for(char c = 'a'; c <= 'z'; ++c){
                if((mask & (1 << (c - 'a'))) == 0)
                    putchar(c);
            }
            puts("");
        }
    }
    return 0;
}

#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
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
char*prepend(char*s, char v){
  char*ptr=NULL;
  asprintf(&ptr, "%c%s", v, s);
  free(s);
  return ptr;
}

#define HEX "0123456789ABCDEF"

int main(){
    char*s = getstr();
    int s_size = strlen(s);
    if(strcmp(s, "0")==0){
        puts("0");
        return 0;
    }
    int head_len = s_size - (s_size - 1) / 4 * 4;
    int head_val = 0;
    char*head_str=strdup("");
    for(int i=0; i<head_len; ++i){
        head_val *= 8;
        head_val += s[i] - '0';
    }
    while(head_val){
        head_str = prepend(head_str, HEX[head_val%16]);
        head_val /= 16;
    }
    printf("%s", head_str);
    for(int i=head_len; i<s_size; i+=4){
        int val = ((s[i    ] - '0') << 9)+
                  ((s[i + 1] - '0') << 6)+
                  ((s[i + 2] - '0') << 3)+
                  ((s[i + 3] - '0'));
        printf("%c%c%c", HEX[val>>8], HEX[(val>>4)&15], HEX[val&15]);
    }
    puts("");
    return 0;
}

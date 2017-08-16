#include <stdio.h>
int freq[10];
char buff[100000];
int main() {
    scanf("%s", &buff);
    for(int i=0;buff[i];i++){
        int num = buff[i]-'0';
        freq[num]++;
    }

    for(int i=1;i<10;i++){
        if(freq[i]!=freq[i-1])
          return puts("0")*0;
    }
    return puts("1")*0;
}    

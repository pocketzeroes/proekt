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

int main() {
    char c = getchar();
    char*s = getstr ();
    if(c == 'E'){
        char last = 0;
        int count = 0;
        for(int z=0;s[z];z++){char i = s[z];
            if(i != last){
                if(count)
                    printf("%c%d", last, count);
                count = 0;
            }
            last = i;
            count++;
        }
        if (count)
            printf("%c%d", last, count);
    }
    else{
        char rep  = 0;
        int count = 0;
        for(int z=0;s[z];z++){char i = s[z];
            if(i >= '0' && i <= '9'){
                count *= 10;
                count += i - '0';
            } 
            else{
                while(count){
                    putchar(rep);
                    count -= 1;
                }
                rep = i;
            }
            while(count){
                putchar(rep);
                count -= 1;
            }
        }
    }
    puts("");
    return 0;
}

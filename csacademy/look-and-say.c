#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SZ 5000000

char res[MAX_STR_SZ];
int resLen=0;

char*next(char* s){
    resLen=0;
    char ch   = s[0];
    int count = 1;
    for (int i = 1; s[i]; ++i) {
        if (s[i] == ch) {
            ++count;
        } 
        else {
            res[resLen++]= (count + '0');
            res[resLen++]= (ch);
            ch = s[i];
            count = 1;
        }
    }
    res[resLen++]=(count + '0');
    res[resLen++]=(ch);
    res[resLen]=0;
    return strdup(res);
}

int main() {
    int n;
    scanf("%d", &n);
    char*s = strdup("1");
    char*s2;
    for (int i = 2; i <= n; ++i) {
        s2=next(s);
        free(s);
        s=s2;
    }
    puts(res);
    return 0;
}

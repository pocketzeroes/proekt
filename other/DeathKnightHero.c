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
    int n;
    scanf("%d", &n);
    int wins = 0;
    for(int i=0; i<n; i++){
        char*s=getstr();
        wins++;
        for(int i = 0; i < strlen(s)-1; i++){
            if(s[i] == 'C' && s[i+1] == 'D'){
                wins--;
                break;
            }
        }
    }
    printf("%d\n", wins);
    return 0;
}

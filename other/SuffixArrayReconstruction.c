#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


int main(){
    int numCases;
    scanf("%d", &numCases);
    while (numCases-- > 0){
        int len, numSuff, pos;
        char buf[10005], 
            suff[10005];
        scanf("%d%d", &len, &numSuff);
        for (int i = (0); i < (len); i++)
            buf[i] = '*';
        buf[len] = '\0';
        bool possible = true;
        for (int i = (0); i < (numSuff); i++){
            scanf("%d%s", &pos, suff);
            pos--;
            int suffLen = strlen(suff);
            for (int j = (0); j < (suffLen); j++){
                if (suff[j] == '*') {
                    break;
                }
                else if (buf[j + pos] == '*' || buf[j + pos] == suff[j]) {
                    buf[j + pos] = suff[j];
                }
                else {
                    possible = false;
                    break;
                }
            }
            for (int j = (0); j < (suffLen); j++) {
                if (suff[suffLen - j - 1] == '*') {
                    break;
                }
                else if (buf[len - j - 1] == '*' || buf[len - j - 1] == suff[suffLen - j - 1]) {
                    buf[len - j - 1] = suff[suffLen - j - 1];
                }
                else {
                    possible = false;
                    break;
                }
            }
        }
        for (int i = (0); i < (len); i++) {
            if (buf[i] == '*') {
                possible = false;
            }
        }
        if (possible) {
            printf("%s\n", buf);
        }
        else {
            puts("IMPOSSIBLE");
        }
    }
    return 0;
}

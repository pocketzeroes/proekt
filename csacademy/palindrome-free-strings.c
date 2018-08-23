#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

char s[1000];
bool k[1000];

int main(){
    scanf("%s", &s);
    int ans = 0;
    for(int i=1; s[i]; i++){
        if(s[i] == s[i-1] && !k[i-1]){
            ans++;
            k[i] = true;
            continue;
        }
        if(i > 1 && s[i] == s[i-2] && !k[i-2]){
            ans++;
            k[i] = true;
        }
    }
    printf("%d\n", ans);
    return 0;
}

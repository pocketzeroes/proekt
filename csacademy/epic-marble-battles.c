#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 300100};
char s   [maxn];
char way [maxn];
char way2[maxn];
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%s", s);
        int qa = 0, qb = 0;
        int top = 0;
        for(int i = 0; s[i]; i++){
            if(s[i] == 'a'){
                if(top > 1 && way[top-1] == 'a' && way[top-2] == 'a') {
                    top -= 2;
                    qa++;
                }
                else{
                    way[top++] = 'a';
                }
            }
            else if(s[i] == 'b'){
                if(top > 1 && way[top-1] == 'a' && way[top-2] == 'b') {
                    top -= 2;
                }
                way[top++] = 'b';
            }
        }
        for(int i = 0; i < top; ){
            if(way[i] == 'a')
                i++;
            else{
                int j = i;
                while(j < top && way[j] == 'b')
                    j++;
                int len = j - i;
                if(i == 0)
                    len++;
                if(j == top)
                    len++;
                len--;
                qb += len / 2;
                i = j;
            }
        }
        if(qb > qa)
            puts("First");
        else
            puts("Second");
    }
    return 0;
}

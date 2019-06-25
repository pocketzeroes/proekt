#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    int offset = in_nextInt();
    char shift[26];
    for(int i=0; i<26; i++)
        shift[i] = (char)(((i+offset)%26)+'a');
    char*msg = getstr();
    int  msg_len = strlen(msg);
    int N    = in_nextInt();
    int bad  = 0;
    int good = 0;
    for(int i=0; i<N; i++){
        char nMsg[msg_len];
        for(int j = 0; j < msg_len; j++)
            nMsg[j] = shift[msg[j]-'a'];
        int vCnt = 0;
        int cCnt = 0;
        for(int j = 0; j < msg_len; j++){
            if(nMsg[j] == 'a' || nMsg[j] == 'e' || nMsg[j] == 'i' || nMsg[j] == 'o' || nMsg[j] == 'u' || nMsg[j] == 'y')
                vCnt++;
            else
                cCnt++;
        }
        if(vCnt >= (cCnt+1)/2)
            bad++;
        else
            good++;
        msg = nMsg;
    }
    if(good > bad)
        puts("Boris");
    else
        puts("Colleague");
    return 0;
}

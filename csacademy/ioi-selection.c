#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int S[17];
int main(){
    for(int i=0; i<=15; i++)
      scanf("%d", &S[i]);
    int ans = 0;
    for(int i=0; i<=15; i++){
        if(S[3] < S[i]+300)
            ans++;
        else
            break;
    }
    printf("%d\n", ans);
    return 0;
}

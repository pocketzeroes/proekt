#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int d, m;
        scanf("%d %d", &d, &m);
        int ans = 0;
        int tot = 0;
        for(int i=0; i<m; i++){
            scanf("%d", &d);
            if((tot + 12) % 7 == 5 && d >= 13)
                ans++;
            tot += d;
        }
        printf("%d\n", ans);
    }
    return 0;
}

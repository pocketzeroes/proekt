#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int tc,n,m;
    scanf("%d", &tc);
    for(int test=1; test<=tc; test++){
        scanf("%d %d", &n, &m);
        for(int i=0; i<m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
        }
        printf("%d\n", n%2);
    }
}

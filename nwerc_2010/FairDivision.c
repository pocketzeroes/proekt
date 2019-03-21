#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int c, n;
int a   [101];
bool vis[101];
int b   [101];

int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        scanf("%d %d", &c, &n);
        for(int i=0; i<n; i++)
            scanf("%d", a+i);
        int sum = 0;
        for(int i=0; i<n; i++)
            sum += a[i];
        if(sum<c){
            puts("IMPOSSIBLE");
            continue;
        }
        sum = c;
        int rest = n;
        for(int i=0; i<n; i++)
            vis[i] = 0;
        for(int i=0; i<n; i++)
            b[i] = 0;
        for(int i=0; i<n; i++){
            int m = 10000000;
            int p = -1;
            for(int j=0; j<n; j++){
                if (a[j]<m && !vis[j]){
                    m = a[j];
                    p = j;
                }
            }
            if(sum/rest > m) {
                sum -= m;
                rest--;
                b[p] = a[p];
                vis[p] = 1;
            }
            else
                break;
        }
        int m = sum/rest;
        sum -= m*rest;
        for(int j=0; j<n; j++) 
            if (!vis[j])
                b[j] = m;
        while(sum!=0) {
            m = 0;
            int p = -1;
            for (int j=0; j<n; j++) {
                if (a[j]>m && !vis[j]) {
                    m = a[j];
                    p = j;
                }
            }
            b[p]++;
            sum--;
            vis[p] = 1;
        }
        for(int i=0; i<n; i++)
            printf("%d ", b[i]);
        puts("");
    }
    return 0;
}

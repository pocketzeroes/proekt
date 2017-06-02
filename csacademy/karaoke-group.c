#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


int song[105][105];

int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i += 1) {
        int l; 
        scanf("%d", &l);
        for (int j = 1; j <= l; j += 1) {
            int x; 
            scanf("%d", &x);
            song[i][x] = true;
        }
    }
    int mx = 0;
    for (int a = 1; a <= n; a += 1) {
        for (int b = a + 1; b <= n; b += 1) {
            int now = 0;
            for (int s = 1; s <= m; s += 1) {
                now += song[a][s] & song[b][s];
            }
            mx = max(mx, now);
        }
    }
    printf("%d\n", mx);
    return 0;
}

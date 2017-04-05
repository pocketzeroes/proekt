#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

enum { N =(int) 1e5 + 10};
int inv[N];
int P[N];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0 ; i < n ; ++i) {
        scanf("%d", &P[i]);
        inv[P[i]] = i;
    }
    int ans = 0, idx = 0;
    for (int i = 1, cnt = 0 ; i <= n ; ++i) {
        if (i > 1 && inv[i-1] < inv[i])
            ++cnt;
        else 
            cnt = 1;
        if (cnt > ans) {
            ans = cnt;
            idx = i - cnt + 1;
        }
    }
    printf("%d\n", n - ans);
    for (int i = idx-1 ; i > 0 ; --i)      printf("%d 0\n", i ); 
    for (int i = idx + ans ; i <= n ; ++i) printf("%d 1\n", i );
    return 0;
}

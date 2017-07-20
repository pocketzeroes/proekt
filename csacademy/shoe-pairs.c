#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef long long ll;
#define mp make_pair

enum{ N = 111};
int a[N][2];

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        int x;
        char c;
        scanf("%d %c", &x, &c);
        if (c == 'L')
            a[x][0]++;
        else
            a[x][1]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
        ans += min(a[i][0], a[i][1]);
    printf("%d\n", ans);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ kMaxN =(int) 1e5};

int where[kMaxN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%d", &x); 
        x -= 1;
        where[x] = i;
    }
    int left = n, right = 0;
    int mx = 0;
    for (int i = n - 1, num = 1; i >= 0; i -= 1, num += 1) {
        left = min(left, where[i]);
        right = max(right, where[i]);
        mx = max(mx, right - left - num + 3);
    }
    if (n == 1) {
        mx = 1;
    }
    printf("%d\n", mx);
    return 0;
}

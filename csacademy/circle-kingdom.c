#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int sum[10005], tot, a[10005], n;
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
        tot += a[i];
    }
    for(int i = n + 1; i <= n * 2; ++i){
        a[i] = a[i - n];
        sum[i] = sum[i - 1] + a[i];
    }
    int anslen = 0x3f3f3f3f, cur, tmp;
    int pos = 2, ans;
    for(int i = 2; i <= n + 1; ++i){
        cur = tot - a[i - 1];
        while(max(sum[pos] - sum[i - 1], cur - sum[pos] + sum[i - 1]) > max(sum[pos + 1] - sum[i-1], cur - sum[pos + 1] + sum[i-1])){
            ++pos;
            if(pos >= 2 * n) while(1);
        }
        tmp = max(sum[pos] - sum[i - 1], cur - sum[pos] + sum[i - 1]);
        if(tmp < anslen){
            anslen = tmp;
            ans = (pos - 1) % n + 1;
        }
        else if(tmp == anslen){
            if((pos - 1) % n + 1 < ans)
                ans = (pos - 1) % n + 1;
        }
    }
    printf("%d\n", ans + 1);
    return 0;
}

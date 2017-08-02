#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int a  [1111];
int cnt[1111];
int main(){
    int n, x=0, Max = 0;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }
    for(int i=0; i<n; i++){
        int temp = a[i]*cnt[a[i]];
        if(Max<temp)
            Max = temp;
    }
    int ans = 0;
    for(int i=0; i<n; i++)
        ans += a[i];
    printf("%d\n", ans-Max);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, now = 0;
    long long dist = 0;
    scanf("%d", &n);
    int c[n],t[n],m[n];
    for (int i=1;i<n;i++)
        scanf("%d", &c[i]);
    m[1] = c[1];
    for (int i=2;i<n;i++)
        m[i] = fmin(m[i-1], c[i]);
    for (int i=0;i<n;i++)
        scanf("%d", &t[i]);
    for(int i=1;i<n;i++){
        dist += c[i];
        now++;
        if (now < t[i]){
            long long d = t[i] - now;
            if (d & 1)
                d++;
            now += d;
            dist += d*m[i];
        }
    }
    printf("%lld\n", dist);
    return 0;
}

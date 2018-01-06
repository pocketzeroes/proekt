#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    int b[m];
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    for (int j = 0; j < m; ++j) {
        scanf("%d", &b[j]);
    }
    int count = 0;
    for (int i = 0; i <= m - n; ++i) {
        bool flag = false;
        for (int j = 0; j < n; ++j) {
            if(b[i + j] + a[j] == 2) 
                flag = true;
            if(b[i + j] + a[j] == 0)
                flag = true;
        }
        if(!flag)
            count++;
    }
    printf("%d\n", count);
    return 0;
}

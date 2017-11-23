#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int mas[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &mas[i]);
    int ans = 0;
    for(int i = 0; i < n; i++){
        bool ok = true;
        for(int j = 0; j < n; j++){
            if (i == j)
                continue;
            ok &= abs(mas[i] - mas[j]) > k;
        }
        ans += ok;
    }
    printf("%d\n", ans);
}

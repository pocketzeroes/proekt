#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MXN =(int) 1e6 + 3};

int n, k, ans;
bool fox[MXN], shelter[MXN];
bool ok, ok2;

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; ++i){
        int x;
        scanf("%d", &x);
        fox[x] = 1;
    }
    for (int i = 1; i <= k; ++i){
        int x;
        scanf("%d", &x);
        shelter[x] = 1;
    }
    shelter[0] = shelter[n];
    shelter[n + 1] = shelter[1];
    fox[0] = fox[n];
    fox[n + 1] = fox[1];
    if (k * 2 == n){
        for (int i = 1; i <= n; ++i){
            if (fox[i]){
                if (i % 2) ok = 1;
                else ok2 = 1;
            }
            if (shelter[i]){
                if (i % 2) ok2 = 1;
                else ok = 1;
            }
        }
    }
    if ((!ok2 && ok) || (ok2 && !ok)){
        printf("%d", k);
    }
    else {
        for (int i = 1; i <= n; ++i){
            if (fox[i]){
                if (!shelter[i + 1] && shelter[i - 1]){
                    ans++;
                    shelter[i - 1] = 0;
                    if (i - 1 == 0) shelter[n] = 0;
                    fox[i] = 0;
                    continue;
                }
                if (!shelter[i - 1] && shelter[i + 1]){
                    ans++;
                    shelter[i + 1] = 0;
                    if (i + 1 > n) shelter[1] = 0;
                    fox[i] = 0;
                }
                continue;
            }
            if (shelter[i]){
                if (!fox[i + 1] && fox[i - 1]){
                    ans++;
                    fox[i - 1] = 0;
                    if (i - 1 == 0) fox[n] = 0;
                    shelter[i] = 0;
                    continue;
                }
                if (!fox[i - 1] && fox[i + 1]){
                    ans++;
                    fox[i + 1] = 0;
                    if (i + 1 > n) fox[1] = 0;
                    shelter[i] = 0;
                }
            }
        }
        for (int i = 1; i <= n; ++i){
            if (fox[i]){
                if (!shelter[i + 1] && shelter[i - 1]){
                    ans++;
                    shelter[i - 1] = 0;
                    if (i - 1 == 0) shelter[n] = 0;
                    fox[i] = 0;
                    continue;
                }
                if (!shelter[i - 1] && shelter[i + 1]){
                    ans++;
                    shelter[i + 1] = 0;
                    if (i + 1 > n) shelter[1] = 0;
                    fox[i] = 0;
                }
                continue;
            }
            if (shelter[i]){
                if (!fox[i + 1] && fox[i - 1]){
                    ans++;
                    fox[i - 1] = 0;
                    if (i - 1 == 0) fox[n] = 0;
                    shelter[i] = 0;
                    continue;
                }
                if (!fox[i - 1] && fox[i + 1]){
                    ans++;
                    fox[i + 1] = 0;
                    if (i + 1 > n) fox[1] = 0;
                    shelter[i] = 0;
                }
            }
        }
        printf("%d", ans + (k - ans) * 2);
    }
    return 0;
}


























#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define kMaxN  100005
int sol[kMaxN];
int main() {
    memset(sol,0,sizeof(sol));
    char*txt=NULL;  
    size_t len;
    getline(&txt, &len, stdin);
    int n = strlen(txt)-1;
    for (int d = 1; d <= n; d ++) {
        if (n % d) 
            continue;
        bool ok = true;
        for (int i = 0; i < d; i ++) {
            signed char c = -1;
            for (int j = i; j < n; j += d) {
                if (txt[j] == '?') 
                    continue;
                else {
                    int t = txt[j] - '0';
                    if (c == -1) 
                        c = t;
                    else {
                        if (t != c) {
                            ok = false;
                            goto finish;
                        }
                    }
                }
            }
            sol[i] = c;
        }
    finish:
        if (ok) {
            for (int j = 0; j < n / d; j ++) {
                for (int i = 0; i < d; i ++) {
                    if (sol[i] == -1) 
                        sol[i] = 0;
                    printf("%d", sol[i]);
                }
            }
            printf("\n");
            exit(0);
        }
    }
    return 0;
}




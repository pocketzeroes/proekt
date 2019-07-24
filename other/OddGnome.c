#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
int data[2000];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int tot;
        scanf("%d", &tot);
        for (int j = 0; j < tot; ++j) {
            scanf("%d", &data[j]);
        }
        for (int j = 1; j < tot - 1; ++j) {
            int last = -1;
            bool ok = true;
            for (int k = 0; k < tot; ++k) {
                if (k != j) {
                    if (data[k] <= last) {
                        ok = false;
                        break;
                    }
                    last = data[k];
                }
            }
            if (ok) {
                printf("%d\n", j + 1);
            }
        }
    }
    return 0;
}

#include<stdio.h>


int main() {
    int n; 
    scanf("%d", &n);
    int elements[n];int elementsLen=0;
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%d", &x);
        int ans = 0;
        for(int q=0;q<elementsLen;q++){
            int itr = elements[q];
            if (itr == 0) {
                continue;
            }
            if (x % itr == 0) {
                ans += 1;
            }
        }
        if (x == 0) { ans = i; }
        elements[elementsLen++] = x;
        printf("%d\n", ans);fflush(stdout);
    }
    return 0;
}

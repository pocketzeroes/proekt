#include <stdio.h>


int lsb(int x) {
    return x^(x&(x-1));
}
   
int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        int x;
        scanf("%d", &x);
        printf("%d\n", lsb(x) );
    }
    return 0;
}

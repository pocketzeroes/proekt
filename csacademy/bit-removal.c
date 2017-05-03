
#include <stdio.h>

int bitRemoval(int x, int y) {
    return x^(x&y);
}

int main() {
    int num;
    scanf("%d", &num);
    for(int i=0;i<num;i++){
      int a, b;
      scanf("%d %d", &a, &b);
      printf("%d", bitRemoval(a , b));
    }
    return 0;
}

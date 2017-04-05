#include <stdio.h>

int main() {
    int height, width;
    scanf("%d %d", &height, &width);
    long long area = 1LL * height * width;
    long long best = area - 1;
    for (int length = 2; 1LL * length * length <= area; length += 1) {
        if (area % length == 0) {
            best = area / length - length;
        }
    }
    printf("%d", best);
    return 0;
}

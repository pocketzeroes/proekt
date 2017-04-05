#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>

enum{ kMaxN   =(int) 1e3}; 
enum{ kMaxVal =(int) 1e3};

int main() {
    int n; 
    scanf("%d", &n);
    printf("%d\n", n);
    assert(3 <= n && n <= kMaxN);
    int elements[n + 2];
    for (int i = 1; i <= n; i += 1) {
        scanf("%d", &elements[i]);
        assert(1 <= elements[i] && elements[i] <= kMaxVal);
    }
    elements[0] = elements[n];
    elements[n + 1] = elements[1];
    for (int i = 1; i <= n; i += 1) {
        printf("%d ", elements[i - 1] + elements[i + 1]);
    }
    return 0;
}

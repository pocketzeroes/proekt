#include <stdio.h>

int Solve(int x) {
    int answer = 0;
    for (int i = 0; i <= x; i += 1) {
        if (i % 2 != 1 && i % 3 != 1) {
            answer += 1;
        }
    }
    return answer;
}

int main() {
    int a, b; 
    scanf("%d %d", &a, &b);
    printf("%d", Solve(b) - Solve(a - 1) );
}

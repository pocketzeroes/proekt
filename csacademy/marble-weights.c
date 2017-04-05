#include <assert.h>
#include <stdio.h>


enum{ MAX_N = 1000};
int n;
int ans[MAX_N + 1];

int main(){
    scanf("%d", &n);
    assert(3 <= n && n <= MAX_N);
    int sum12, sum13, sum23;
    puts("Q 2 1 2"); fflush(stdout);
    scanf("%d", &sum12);
    puts("Q 2 1 3"); fflush(stdout);
    scanf("%d", &sum13);
    puts("Q 2 2 3"); fflush(stdout);
    scanf("%d", &sum23);
    ans[1] = (sum12 + sum13 + sum23) / 2 - sum23;
    ans[2] = sum12 - ans[1];
    ans[3] = sum13 - ans[1];
    for (int i = 4; i <= n; ++i) {
        printf("Q 2 1 %d\n", i);
        fflush(stdout);
        fprintf(stderr, "Wait sum\n");
        int sum; 
        scanf("%d", &sum);
        fprintf(stderr, "Got sum\n");
        ans[i] = sum - ans[1];
    }
    puts( "A ");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}

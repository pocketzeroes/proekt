#define MAX(a,b) (((a)>(b))?(a):(b))
bool canJump(int*A, int n) {
    int reach = 0;
    for(int i = 0; i <= reach && i < n; ++i) {
        reach = MAX(reach, i + A[i]);
    }
    return reach >= n - 1;
}

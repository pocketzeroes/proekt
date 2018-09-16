int s[30005];
int p[30005];

int sumSubarrayMins(int*A, int Asz){
    int n = Asz;
    int top = 1;
    s[1] = A[0];
    p[1] = 0;
    p[0] = -1;
    s[0] = -1;
    long long ans = A[0];
    long long cur = A[0];
    for (int i = 1; i < n; i++) {
        int x = A[i];
        while (x < s[top]) {
            cur -= (p[top] - p[top - 1]) * s[top];
            --top;
        }
        s[++top] = x;
        p[top] = i;
        cur += (p[top] - p[top - 1]) * s[top];
        ans += cur;
    }
    return ans % 1000000007;
}

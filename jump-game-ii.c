#define MAX(a,b) (((a)>(b))?(a):(b))
int jump(int*A, int n) {
    int ans = 0;
    int last = 0;
    int cur = 0;     
    for(int i = 0, next; i < n; ++i) {
        if(i > last) { 
            ++ans;     
            last = cur;
        }
        cur = MAX(cur, i + A[i]);
    }
    return ans;
}

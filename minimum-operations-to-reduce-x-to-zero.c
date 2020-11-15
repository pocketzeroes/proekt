#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int minOperations(int*nums, int numsSz, int x){
    int n = numsSz, ans = n + 1;
    int pre[n]; clr(pre);
    int suf[n]; clr(suf);
    for(int i = 0; i < n; i += 1){
        if(i) pre[i] = pre[i - 1];
        pre[i] += nums[i];
        if(pre[i] == x) ans = fmin(ans, i + 1);
    }
    for(int i = n - 1; i >= 0; i -= 1){
        if(i + 1 < n) suf[i] = suf[i + 1];
        suf[i] += nums[i];
        if(suf[i] == x) ans = fmin(ans, n - i);
    }
    if(suf[0] < x) return -1;
    for(int i = 0, j = 1; i + 1 < n; i += 1){
        j = fmax(j, i + 1);
        while(j < n && pre[i] + suf[j] > x) j += 1;
        if(j < n && pre[i] + suf[j] == x) ans = fmin(ans, i + 1 + n - j);
    }
    if(ans > n) return -1;
    return ans;
}

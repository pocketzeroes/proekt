
void amin(int*x, int y){
    if(y<*x)
       *x=y;
}
int sums[100011];
int mem [100011];

int minSumOfLengths(int*arr, int arrSz, int target){
    int N= arrSz;
    for(int i=0, i_len=(N); i<i_len; ++i) sums[i+1] = sums[i] + arr[i];
    int left = 0;
    memset(mem, 0x3f, sizeof mem);
    int ans = mem[0];
    for (int right=1; right<=N; right++) {
        while (sums[right] - sums[left] > target) left++;
        if (sums[right] - sums[left] == target) {
            amin(&ans, right - left + mem[left]);
            amin(&mem[right], right - left);
        }
        amin(&mem[right], mem[right-1]);
    }
    if (ans == mem[0]) {
        return -1;
    }
    else {
        return ans;
    }
}

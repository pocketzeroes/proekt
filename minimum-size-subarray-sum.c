#define MIN(a,b) (((a)<(b))?(a):(b))
int minSubArrayLen(int s, int* nums,int numsSz) {
    int start = -1, sum = 0, min_size = INT_MAX;
    for (int i = 0; i < numsSz; ++i) {
        sum += nums[i];
        while (sum >= s) {
            min_size = MIN(min_size, i - start);
            sum -= nums[++start];
        }
    }
    if (min_size == INT_MAX) {
        return 0;
    }
    return min_size;
}

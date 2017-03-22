#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int robRange(int* nums, int start, int end) {
    int num_i = nums[start], num_i_1 = 0, num_i_2 = 0;
    for (int i = start + 1; i < end; ++i) {
        num_i_2 = num_i_1;
        num_i_1 = num_i;
        num_i = MAX(nums[i] + num_i_2, num_i_1);
    }
    return num_i;
}

int rob(int*nums,int numsSz) {
    if (numsSz == 0) {
        return 0;
    }
    if (numsSz == 1) {
        return nums[0];
    }
    int aa=robRange(nums, 0, numsSz - 1);
    int bb=robRange(nums, 1, numsSz);
    return MAX(aa,bb );   
}

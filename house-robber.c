#define MAX(a, b) ((a) > (b) ? (a) : (b))

int rob(int* nums, int numsSize) {
    int curt = 0, prev = 0, res = 0;
    for(int i=0 ; i < numsSize; i++){
        res = MAX(res, prev + nums[i]);
        prev=curt;
        curt=res;
    }
    return res;
}

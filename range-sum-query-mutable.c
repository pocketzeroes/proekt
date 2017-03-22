typedef struct {
    int a;
} NumArray;

int*gNums;
int gNumsSz;
int*bit;

int sum(int i) {
    ++i;
    int sum = 0;
    for (; i > 0; i -= lower_bit(i)) 
        sum += bit[i];
    return sum;
}
void add(int i, int val) {
    ++i;
    for (; i <= gNumsSz; i += lower_bit(i)) 
        bit[i] += val;
}
inline int lower_bit(int i){
    return i & -i;
}

NumArray*numArrayCreate(int*nums, int numsSize){
    gNums=malloc(numsSize*sizeof(int));
    gNumsSz=numsSize;
    for (int i=0;i<numsSize;i++)
        gNums[i]=nums[i];
    bit = malloc((numsSize+1)*sizeof(int));
    bit[0]=0;
    for (int i = 1; i < numsSize+1; ++i) 
        bit[i] = nums[i - 1] + bit[i - 1];
    for (int i = numsSize; i >= 1; --i){
        int last_i = i - lower_bit(i);
        bit[i] -= bit[last_i];
    }
    return gNums;
}
void numArrayUpdate(NumArray* obj, int i, int val) {
    if (val - gNums[i]) {
        add(i, val - gNums[i]);
        gNums[i] = val;
    }
}
int numArraySumRange(NumArray* obj, int i, int j) {
    return sum(j) - sum(i - 1);
}
void numArrayFree(NumArray* obj) {
    gNums=NULL;
}



























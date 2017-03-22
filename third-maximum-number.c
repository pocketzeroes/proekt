#define MY_VAL 0xdeadbeef
int thirdMax(int*nums,int numsSz){
    int max1 = MY_VAL;
    int max2 = MY_VAL;
    int max3 = MY_VAL;
    for(int i=0;i<numsSz;i++){
        int n=nums[i];
        if (n==max1 || n==max2 || n==max3)
            continue;
        if (max1 == MY_VAL || n > max1){
            max3 = max2;
            max2 = max1;
            max1 = n;
        }
        else if (max2 == MY_VAL || n > max2) {
            max3 = max2;
            max2 = n;
        } 
        else if (max3 == MY_VAL || n > max3){
            max3 = n;
        }
    }
    return max3 == MY_VAL ? max1 : max3;
}

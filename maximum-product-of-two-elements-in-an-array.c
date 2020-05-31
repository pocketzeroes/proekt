int maxProduct(int*nums, int numsSz){
    int ma=0;
    int i,j;
    for(j=0;j<numsSz;j++)
        for(i=0;i<j;i++)
            ma=fmax(ma,(nums[i]-1)*(nums[j]-1));
    return ma;
}

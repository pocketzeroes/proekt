int*productExceptSelf(int*nums,int numsSz,int*rsz) {
    *rsz=0;
    int * left_product;
    if(numsSz==0) 
        goto end;
    left_product=malloc(numsSz*sizeof (int));
    left_product[0] = 1;
    for (int i = 1; i < numsSz; ++i) 
        left_product[i] = left_product[i - 1] * nums[i - 1];
    int right_product = 1;
    for (int i = numsSz - 2; i >= 0; --i) {
        right_product *= nums[i + 1];
        left_product[i] = left_product[i] * right_product;
    }
   *rsz=numsSz;
end:return left_product;
}

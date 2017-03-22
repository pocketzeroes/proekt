int* majorityElement(int* nums, int numsSize, int* returnSize) {
    int t1,t2,n1=0,n2=0; 
    for(int i=0;i<numsSize;++i)
    {
        if(n1!=0&&t1==nums[i]){++n1;continue;} 
        if(n2!=0&&t2==nums[i]){++n2;continue;}
        if(n1==0){ t1=nums[i]; ++n1;continue;}
        if(n2==0){ t2=nums[i]; ++n2;continue;}
        --n1;--n2;
    }
    int z1=0,z2=0;
    for(int i=0;i<numsSize;++i)
    {
        if(n1>0){ if(nums[i]==t1) ++z1;}
        if(n2>0) {if(nums[i]==t2) ++z2;}
    }
    int*ret=malloc(2*sizeof(int));
    int rsz=0;
    if(z1>numsSize/3) 
        ret[rsz++]=t1;
    if(z2>numsSize/3) 
        ret[rsz++]=t2;
   *returnSize=rsz;
    return ret;
}

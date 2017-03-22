int mergeSort(long long*sum, int left, int right, int lower, int upper)
{
    int mid, i, res, j, k;
    if(left >right) return 0;
    if(left==right) return ( (sum[left]>=lower) && (sum[left]<=upper) )?1:0;
    else
    {
        long long temp[right-left+1];
        memset(temp,0,sizeof(temp));
        mid = (left+right)/2;
        res = mergeSort(sum, left, mid,   lower, upper) +
              mergeSort(sum, mid+1,right, lower, upper);
        for(i=left, j=k=mid+1; i<=mid; ++i)
        {
            while(j<=right && sum[j]-sum[i]<lower)  ++j;
            while(k<=right && sum[k]-sum[i]<=upper) ++k;
            res +=k-j;
        }
        for(i=k=left, j=mid+1; k<=right; ++k) 
            temp[k-left] = (i<=mid) && (j>right || sum[i]<sum[j])?sum[i++]:sum[j++]; 
        for(k=left; k<=right; ++k) 
            sum[k] = temp[k-left]; 
        return res;
    }
}
int countRangeSum(int* nums, int numsSize, int lower, int upper){
     int len = numsSize, i;
     long long sum[len+1];
     memset(sum,0,sizeof(sum));
     for(i=1; i<=len; ++i) 
        sum[i] = sum[i-1]+nums[i-1];
     return mergeSort(sum, 1, len, lower, upper);
}

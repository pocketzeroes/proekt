void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rotate(int*nums, int n, int k) 
{
    for (; k = k%n; n -= k, nums += k)
    {
        for (int i = 0; i < k; i++)
        {
            swap(nums,i, n - k + i);
        }
    }
}

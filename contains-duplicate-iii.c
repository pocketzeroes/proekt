void swap(int *p, int *q)
{
    int t = *p; 
    *p = *q;
    *q = t;
}
void sort(int* nums, int* indexes, int low, int high)
{
    int l = low, h = high;
    int v = nums[l+(h-l)/2];
    while(l <= h)
    {
        while(nums[l] < v) l++;
        while(nums[h] > v) h--;
        if(l <= h)
        {
            swap(nums+l, nums+h);
            swap(indexes+l, indexes+h);
            l++, h--;
        }
    }
    if(h > low)
        sort(nums, indexes, low, h);
    if(l < high)
        sort(nums, indexes, l, high);
}
bool containsNearbyAlmostDuplicate(int* nums, int size, int k, int t)
{
    int *indexes = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
        indexes[i] = i;
    sort(nums, indexes, 0, size-1);
    for(int i = 0; i < size; i++)
    {
        int top = nums[i]+t;
        for(int j = i+1; j < size && nums[j] <= top; j++)
            if(abs(indexes[i] - indexes[j]) <= k)
                return true;
    }
    return false;
}

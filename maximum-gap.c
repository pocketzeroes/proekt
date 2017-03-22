#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int maximumGap(int* nums,int nsz) {
    if (nsz < 2) return 0;
    int n = nsz;
    for(int i = 0; i < 32; ++i)
    {
        int mask = 1LL << i;
        int cnt1 = 0;
        for (int j = 0; j < n; ++j) if (mask & nums[j]) ++cnt1;
        int*newn=malloc(n*sizeof(int));
        memset(newn,0, n*sizeof(int));
        int k0 = 0;
        int k1 = 0;
        for (int j = 0; j < n; ++j)
        {
            if (nums[j] & mask) newn[(n-cnt1) + k1++] = nums[j];
            else newn[k0++] = nums[j];
        }
        int *t =nums;
        nums=newn;
        newn=t;
    }
    int mx = 0;
    for (int i = 1; i < n; ++i)
    {
        mx = MAX(mx, nums[i] - nums[i-1]);
    }
    return mx;
}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int minSwapsCouples(int*row, int rowSz){
    int n = rowSz;
    int pos[n]; memset(pos, 0, sizeof(pos));
    for (int i=0; i<n; ++i)
        pos[row[i]] = i;
    int ans = 0;
    for (int i=0; i<n; i+=2) 
        if (pos[row[i]^1]==i+1) 
            continue;
        else{
#define p  pos[row[i]^1]
#define s  pos[row[i+1]]
            s = p;
            p = i+1;
            swap(row, p, s);
            ++ans;
        }
    return ans;
}

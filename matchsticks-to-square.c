bool makesquare(int* nums,int numsSz) {
    int sum =0;for (int i=0;i<numsSz;i++)sum+=nums[i];
    if (sum % 4) 
        return false;
    int side_len = sum / 4;
    int all = (1 << numsSz) - 1;
    int used_subsets[1024]={0};
    int usLen=0;
    bool valid_half_subsets[1 << numsSz];
    memset(valid_half_subsets,0,sizeof(valid_half_subsets));
    for (int subset = 0; subset <= all; ++subset) {
        int subset_sum = 0;
        for (int i = 0; i < numsSz; ++i) {
            if (subset & (1 << i)) {
                subset_sum += nums[i];
            }
        }
        if (subset_sum == side_len) {
            for (int i=0;i<usLen;i++){
                int used_subset=used_subsets[i];
                if ((used_subset & subset) == 0) {
                    int valid_half_subset = used_subset | subset;
                    valid_half_subsets[valid_half_subset] = true;
                    if (valid_half_subsets[all ^ valid_half_subset]) {
                        return true;
                    }
                }
            }
            used_subsets[usLen++]=subset;
        }
    }
    return false;
}


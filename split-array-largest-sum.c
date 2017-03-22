inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

bool canSplit(int*nums,int sz, int m, int sum){
    int cnt = 1, curr_sum = 0;
    for(int i=0;i<sz;i++){
        int num=nums[i];
        curr_sum += num;
        if (curr_sum > sum) {
            curr_sum = num;
            ++cnt;
        }
    }
    return cnt <= m;
}
int splitArray(int*nums,int numsSz, int m){
    int left = 0, right = 0;
    for(int i=0;i<numsSz;i++){
        int num=nums[i];
        left = max(left, num);
        right += num;
    }
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canSplit(nums,numsSz, m, mid)) {
            right = mid - 1;
        } 
        else {
            left = mid + 1;
        }
    }
    return left;
}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

int*addNegabinary(int*arr1, int arr1sz, int*arr2, int arr2sz, int*rsz){
    reverse(arr1, 0, arr1sz-1);
    reverse(arr2, 0, arr2sz-1);
    int anssz=2000;
    int*ans = calloc(anssz, sizeof(int));
    for(int i=0, i_len=(arr1sz); i<i_len; ++i)
        ans[i] += arr1[i];
    for(int i=0, i_len=(arr2sz); i<i_len; ++i)
        ans[i] += arr2[i];
    for(int i=0, i_len=(anssz-2u); i<i_len; ++i){
        while (ans[i] >= 2){
            ans[i] -= 2;
            if (ans[i+1])
                ans[i+1]--;
            else {
                ans[i+1]++;
                ans[i+2]++;
            }
        }
    }
    while(anssz>0 && ans[anssz-1] == 0)
        anssz--;
    if(anssz)
      reverse(ans, 0, anssz-1);
    if(anssz==0){
        ans[0]=0;
        anssz=1;
    }
   *rsz = anssz;
    return ans;
}

int findNumbers(int*nums, int numsSz){
    int ans=0;
    for(int z=0;z<numsSz;z++){int i=nums[z];
        int cnt=0;
        while(i){
            i/=10;
            cnt++;
        }
        if(cnt%2==0)
            ans++;
    }
    return ans;
}

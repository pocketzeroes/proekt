int minStartValue(int*nums, int numsSz){
    int s,ans;
    s=0;
    ans=0;
    for(int i=0; i<numsSz; i++){
        s = s+nums[i];
        ans = fmin(ans, s);
    }
    if(ans<=0)
        return abs(ans)+1;
    return 1; 
}

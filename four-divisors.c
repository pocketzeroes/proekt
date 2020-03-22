int sumFourDivisors(int*nums, int numsSz){
    int ans=0;
    for(int z=0; z<numsSz; z++){int v = nums[z];
        int num = 0;
        int s = 0;
        for(int d = 1; d*d <= v; d++){
            if(v % d == 0){
                if(d*d < v){
                    num += 2;
                    s += d;
                    s += v/d;
                }
                else
                    num++;
            }
        }
        if(num == 4)
            ans += s;
    }
    return ans;
}

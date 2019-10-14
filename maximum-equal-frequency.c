#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int ca[100005];
int cb[100005];

int maxEqualFreq(int*nums, int numsSz){
    clr(ca);
    clr(cb);
    int ans = 1,
        hv  = 0,
        ma  = 0;
    for(int i=0; i<numsSz; i++){
        int tmp = nums[i];
        cb[++ca[tmp]]++;
        ma = fmax(ma, ca[tmp]);
        if(ca[tmp] == 1)
            hv++;
        else
            cb[ca[tmp] - 1]--;
        if(ma == 1 || (cb[1] == 1 && cb[ma] == hv - 1) || (cb[ma] == 1 && cb[ma - 1] == hv - 1))
            ans = i + 1;
    }
    return ans;
}

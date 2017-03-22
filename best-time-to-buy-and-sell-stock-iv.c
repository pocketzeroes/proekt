#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int maxProfit(int k, int*prices,int pricesSz) {
    int len = pricesSz;
    if (len<2) return 0;
    if (k>len/2){ 
        int ans = 0;
        for (int i=1; i<len; ++i){
            ans += MAX(prices[i] - prices[i-1],0);
        }
        return ans;
    }
    int hold[k+1];
    int rele[k+1];
    for (int i=0;i<=k;++i){
        hold[i] = INT_MIN;
        rele[i] = 0;
    }
    int cur;
    for (int i=0; i<len; ++i){
        cur = prices[i];
        for(int j=k; j>0; --j){
            rele[j] = MAX(rele[j],hold[j] + cur);
            hold[j] = MAX(hold[j],rele[j-1] - cur);
        }
    }
    return rele[k];
}

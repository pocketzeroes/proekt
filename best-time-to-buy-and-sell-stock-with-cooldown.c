inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize==0)
        return 0;
    int buy     [2]={0};
    int sell    [2]={0};
    int coolDown[2]={0};
    buy[0] = -prices[0];
    for (int i = 1; i < pricesSize; ++i){
        buy     [i % 2] = max(buy[(i - 1) % 2], coolDown[(i - 1) % 2] - prices[i]);
        sell    [i % 2] = buy[(i - 1) % 2] + prices[i];
        coolDown[i % 2] = max(coolDown[(i - 1) % 2], sell[(i - 1) % 2]);
    }
    return max(coolDown[(pricesSize - 1) % 2], sell[(pricesSize - 1) % 2]);
}

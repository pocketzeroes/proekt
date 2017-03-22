#define MAX(a,b) (((a)>(b))?(a):(b))

int maxProfit(int* prices, int pricesSize) {
    int ret = 0;
    for (size_t p = 1; p < pricesSize; ++p) 
      ret += MAX(prices[p] - prices[p - 1], 0);    
    return ret;
}
#define MAX(a,b) (((a)>(b))?(a):(b))

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize==0) 
        return 0;
    int hold1    = INT_MIN;
    int release1 = INT_MIN;
    for (int i=0;i<pricesSize;i++){
        int p    = prices[i];
        hold1    = MAX(hold1, -p);
        release1 = MAX(release1, hold1 + p);
    }
    return release1;
}

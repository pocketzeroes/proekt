#define MAX(a,b) (((a)>(b))?(a):(b))

int maxProfit(int* prices, int pricesSize) {
    int states[2][4] = {INT_MIN, 0, INT_MIN, 0};
    int len = pricesSize, i, cur = 0, next =1;
    for(i=0; i<len; ++i)
    {
        states[next][0] = MAX(states[cur][0], -prices[i]);
        states[next][1] = MAX(states[cur][1], states[cur][0]+prices[i]);
        states[next][2] = MAX(states[cur][2], states[cur][1]-prices[i]);
        states[next][3] = MAX(states[cur][3], states[cur][2]+prices[i]);
        int tmp=next;
        next=cur;
        cur=tmp;
    }
    return MAX(states[cur][1], states[cur][3]);
}

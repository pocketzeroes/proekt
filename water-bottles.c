int numWaterBottles(int numBottles, int numExchange){
    int ans=0, ne=0;
    while(numBottles||numBottles+ne>=numExchange){
        ans+=numBottles;
        int ne2=(numBottles+ne)%numExchange;
        numBottles=(numBottles+ne)/numExchange;
        ne=ne2;
    }
    return ans;
}

int minOperationsMaxProfit(int*customers, int customersSz, int boardingCost, int runningCost){
    int i,j,k,rem,cnt;
    int ans;
    int best,now;
    now=0;
    best=0;
    ans=-1;
    rem=0;
    cnt=0;
    for (i=0;i<customersSz;i++){
        cnt++;
        rem+=customers[i];
        if (rem>=4){
            rem-=4;
            now+=4*boardingCost;
        }
        else{
            now+=rem*boardingCost;
            rem=0;
        }
        now-=runningCost;
        if (now>best){
            best=now;
            ans=cnt;
        }
    }
    while (rem>0){
        if (rem>=4){
            rem-=4;
            now+=4*boardingCost;
        }
        else{
            now+=rem*boardingCost;
            rem=0;
        }
        now-=runningCost;
        cnt++;
        if (now>best){
            best=now;
            ans=cnt;
        }
    }
    return ans;
}

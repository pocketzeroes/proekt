int removeCoveredIntervals(int**intervals, int intervalsSz, int*intervals0sz){
    int n = intervalsSz;
    int ans = n;
    for(int i = 0; i < intervalsSz; ++i){
        for(int j = 0; j < intervalsSz; ++j){
            if(i != j && intervals[j][0] <= intervals[i][0] && intervals[i][1] <= intervals[j][1]){
                --ans;
                break;
            }
        }
    }
    return ans;
}

bool checkValidString(char*q){
    int dp[300]; memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for(int z=0;q[z];z++){char c = q[z];
        int ndp[300]; memset(ndp, 0, sizeof(ndp));
        if(c == '('){
            for(int i = 0;i < 299;i++){
                ndp[i+1] = dp[i];
            }
        }
        else if(c == ')'){
            for(int i = 1;i < 300;i++){
                ndp[i-1] = dp[i];
            }
        }
        else{
            for(int i = 0;i < 300;i++){
                if(i+1 < 300)
                    ndp[i+1] |= dp[i];
                ndp[i] |= dp[i];
                if(i-1 >= 0)
                    ndp[i-1] |= dp[i];
            }
        }
        memcpy(&dp, &ndp, sizeof(dp));
    }
    return dp[0] == 1;
}

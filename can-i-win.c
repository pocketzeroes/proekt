int dfs(int*dp, int s, int desiredTotal, int maxChoosableInteger)
{
    if(dp[s] != -1)
        return dp[s];
    if(desiredTotal <= 0)
        return dp[s] = 0;
    dp[s] = 0;
    for(int i = 0; i < maxChoosableInteger; ++i)
        if((1 << i & s) == 0)
            dp[s] |= !dfs(dp, 1 << i | s, desiredTotal - i - 1, maxChoosableInteger);
    return dp[s];
}
bool canIWin(int maxChoosableInteger, int desiredTotal)
{
    if(desiredTotal <= 0)
        return true;
    if(maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal)
        return false;
    int dp[1 << maxChoosableInteger];memset(dp,-1,sizeof(dp));
    if(dfs(dp, 0, desiredTotal, maxChoosableInteger))
        return true;
    return false;
}

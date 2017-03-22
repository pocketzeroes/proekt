int helper(int n, int*steps ){
    if (n < 0) 
        return 0;
    if( n == 0 )
        return 1;
    if( steps[n] != 0 )
        return steps[n];
    steps[n] = helper(n - 1, steps) + helper(n - 2, steps);
    return steps[n];
}
int climbStairs(int n){
    int steps[n+1];
    memset(steps,0,sizeof(steps));
    return helper(n, steps);
}


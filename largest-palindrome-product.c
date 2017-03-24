private int reverse(int n, int dig){
    int x   = n;
    int res = 0;
    int ten = (int)pow(10,dig-1);
    while(x != 0 ){
        int d = x%10;
        res+=ten*d;
        ten/=10;
        x/=10;
    }
    return res;
}
int largestPalindrome(int n){
    if(n == 1) 
        return 9;
    int m   = 1337;
    int mod = (int) pow(10, n);
    int max = (int) pow(10, n)-1;
    long pro = (long)max*(long)max;
    int right = (int)(pro%mod);
    int left = (int)(pro/mod);
    if(left == reverse(right,n)) 
        return (int)(pro%m);
    if(left > right)
        left--;
    pro = (long)left*(long)mod+(long)reverse(left,n);
    while(left != mod/10){
        for(int i = max;i>pro/i;i--){
            if(pro%i == 0 ) 
                return (int)(pro%m);
        }
        left--;
        pro = (long)left*(long)mod+(long)reverse(left,n);
    }
    return (int)(pro%m);
}


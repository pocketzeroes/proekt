int numTrees(int n) {
    long long ans =1;
    for(int i=n+1;i<=2*n;i++)
        ans = ans*i/(i-n);
    return ans/(n+1);
}

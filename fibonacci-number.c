int fib(int N){
    int old = 0;
    int ans = 1;
    for(int i=0; i<N-1; ++i){
        int tmp = old;
        old = ans;
        ans = tmp + ans;
    }
    return N ? ans : 0;
}

int kthGrammar(int N, int K) {
    return __builtin_popcount(K-1)%2;    
}

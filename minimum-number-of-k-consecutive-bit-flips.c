int minKBitFlips(int*A, int Asz, int K){
    int N = Asz;
    bool flip[N]; memset(flip, 0, sizeof(flip));
    bool current = false;
    int flips = 0;
    for (int i = 0; i < N; i++) {
        if (i >= K && flip[i - K])
            current = !current;
        bool bad = (A[i] == 0) ^ current;
        if (bad && i > N - K)
            return -1;
        if (bad) {
            flips++;
            flip[i] = true;
            current = !current;
        }
    }
    return flips;
}

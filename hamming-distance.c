int hammingDistance(int x, int y) {
    int xor = x ^ y;
    int ret = 0;
    while ( xor ) {
        ret ++;
        xor &= xor - 1;
    }
    return ret;
}

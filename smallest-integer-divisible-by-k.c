int smallestRepunitDivByK(int K) {
    int value = 0, length = 0;
    for (int i = 0; i < 1e6; i++) {
        value = (10 * value + 1) % K;
        length++;
        if (value == 0)
            return length;
    }
    return -1;
}

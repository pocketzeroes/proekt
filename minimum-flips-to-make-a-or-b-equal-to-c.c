int minFlips(int a, int b, int c) {
    int ans = 0;
    for (int i = 0; i <= 30; i++) {
        int aa = a & (1 << i);
        int bb = b & (1 << i);
        int cc = c & (1 << i);
        int dd = 1 << i;
        if ((aa | bb) != cc) {
            if (((aa ^ dd) | bb) == cc)
                ans++;
            else if ((aa | (bb ^ dd)) == cc)
                ans++;
            else
                ans += 2;
        }
    }
    return ans;
}

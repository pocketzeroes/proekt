int countDigitOne(int n) {
    int k   = 1;
    int cnt = 0, multiplier = 1, left_part = n;
    while (left_part > 0) {
        int curr = left_part % 10;
        int right_part = n % multiplier;
        cnt += (left_part / 10 + (k < curr)) * multiplier;
        if (k == 0 && multiplier > 1) {
            cnt -= multiplier;
        }
        if (curr == k) {
            cnt += right_part + 1;
        }
        left_part /= 10;
        multiplier *= 10;
    }
    return cnt;
}

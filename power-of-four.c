bool isPowerOfFour(int num) {
    return num > 0 && (num & (num - 1)) == 0 &&
           ((num & 0b01010101010101010101010101010101) == num);
}


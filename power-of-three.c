bool isPowerOfThree(int n) {
  int max_log3 = log(INT_MAX) / log(3);
  int max_pow3 = pow(3, max_log3);
  return n > 0 && max_pow3 % n == 0;
}

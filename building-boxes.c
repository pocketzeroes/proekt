int minimumBoxes(int n){
  int ans = 0;
  for (int i = 1; i < 10000; ++i) {
    for (int j = 1; j <= i; ++j) {
      if (n<=0)
        break;
      ++ans;
      n -= j;
    }
  }
  return ans;
}

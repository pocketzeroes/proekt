int DP[20001];
int subarraySum(int*N, int Nsize, int k){
  int n = Nsize;
  if (n == 0) {
    return 0;
  }
  DP[0] = 0;
  for (int i = 0; i < n; i++) {
    DP[i + 1] = DP[i] + N[i];
  }
  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (DP[j + 1] - DP[i] == k) {
        count++;
      }
    }
  }
  return count;
}

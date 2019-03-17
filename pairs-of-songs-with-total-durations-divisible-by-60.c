int numPairsDivisibleBy60(int*time, int timeSz){
  int n = timeSz;
  int cnt[60]={0};
  int ans = 0;
  for(int i = 0; i < n; ++i){
    int t = time[i] % 60;
    ans += cnt[(60 - t) % 60];
    ++cnt[time[i] % 60];
  }
  return ans;
}

double minmaxGasDist(int*stations, int stationsSz, int K){
  if (stationsSz <= 1){
    return 0;
  }
  double s = 0, e = 1e9;
  bool ck(double x){
    long long used = 0;
    for (int i = 1; i < stationsSz; ++i) {
      int dis = stations[i] - stations[i - 1];
      used += (int)ceil(dis / x) - 1;
    }
    return used <= K;
  }
  while (e - s > 1e-9) {
    double mid = 0.5 * (s + e);
    if (ck(mid)) {
      e = mid;
    } 
    else {
      s = mid;
    }
  }
  return e;
}

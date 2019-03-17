int n;
int dis;
typedef long long ll;
void go(ll val, int bs) {
  if (val <= n) 
    ++dis;
  if (val * 10 > n) 
    return;
  for (int i = 0; i <= 9; ++i) {
    if (!bs && i == 0)
      continue;
    if (bs & (1 << i))
      continue;
    go(val * 10 + i, bs | (1 << i));
  }
}
int numDupDigitsAtMostN(int N){
  dis = 0;
  n = N;
  go(0, 0);
  return N + 1 - dis;
}

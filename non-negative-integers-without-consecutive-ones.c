int ans, up;
int f[40];

void dfs(int dep, int now, int last) {
  if (dep == -1) {
    ++ans;
    return;
  }
  dfs(dep - 1, now, 0);
  if ((now | ((1ll << (dep + 1)) - 1) ) < up) {
    ans += f[dep];
    return ;
  }
  if ((now | (1 << dep)) <= up && !last) {
    dfs(dep - 1, now | (1 << dep), 1);
  }
}
int findIntegers(int num) {
  f[0] = 1;
  for (int i = 1; i <= 30; ++i) {
    f[i] = f[i - 1];
    if (i > 1) {
      f[i] += f[i - 2];
    }
  }
  up = num;
  ans = 0;
  dfs(30, 0, 0);
  return ans;
}
